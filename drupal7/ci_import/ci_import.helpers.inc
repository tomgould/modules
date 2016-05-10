<?php
/**
 * @file
 *     Helper functions for the import jobs
 */

/**
 * Debug function
 *
 * @param any $var
 * @param bool $die
 */
function ci_import_debug($var, $die = FALSE) {

  print '<pre style="border:1px solid black; padding: 10px; margin:25px">' . var_export($var, TRUE) . '</pre>';

  if ($die) {
    die;
  }
}

/**
 * Prepares and empty node object
 *
 * @param string $type
 *    The machine name of the node to prepare
 *
 * @return \stdClass
 */
function ci_import_get_empty_node($type, $user) {
  global $language;
  $node           = new stdClass();
  $node->status   = 0;
  $node->promote  = 1;
  $node->language = LANGUAGE_NONE;
  if (!empty($user->uid)) {
    $node->uid  = $user->uid;
    $node->name = $user->name;
  }
  else {
    $node->uid  = 1;
    $node->name = 'admin';
  }

  $node->type = $type;

  node_object_prepare($node);

  return $node;

}

/**
 * Prepares a comment
 * 
 * @param type $node
 * @param type $source // the D6 comment
 * @param type $user   // D7 user loaded from the D6 comment mail
 * 
 * @return \stdClass
 */
function ci_import_get_empty_comment($node, $source, $user) {
  $comment                                           = new stdClass();
  $comment->nid                                      = $node->nid;
  $comment->cid                                      = NULL;
  $comment->pid                                      = 0;     // parent comment id, 0 if none
  $comment->uid                                      = $user->uid;
  $comment->mail                                     = $user->mail;
  $comment->name                                     = $user->name;
  $comment->thread                                   = $source->thread; // OPTIONAL. 01/ If you need comments to be threaded you can fill this value. Otherwise omit it.
  $comment->hostname                                 = $source->hostname;  // OPTIONAL. You can log poster's ip here
  $comment->created                                  = $source->timestamp;  // OPTIONAL. You can set any time you want here. Useful for backdated comments creation.
  $comment->is_anonymous                             = 0;     // leave it as is
  $comment->homepage                                 = $source->homepage;  // you can add homepage URL here
  $comment->status                                   = $source->status == 0 ? COMMENT_PUBLISHED : COMMENT_NOT_PUBLISHED;  // D6 sucks
  $comment->language                                 = LANGUAGE_NONE; // The same as for a node
  $comment->subject                                  = $source->subject;
  $comment->comment_body[LANGUAGE_NONE][0]['value']  = $source->comment; // Everything here is pretty much like with a node
  $comment->comment_body[LANGUAGE_NONE][0]['format'] = 'filtered_html';

  return $comment;

}

/**
 * creates the comments for a node
 * 
 * @param type $node
 * @param type $source
 */
function ci_import_comments($node, $source) {
  
  $previous_comment = NULL;
  if (!empty($source->old_comments[0])) {
    foreach ($source->old_comments[0] as $c) {
      if (!empty($c)) {
        $user_account = user_load_by_mail($c->mail);
        if (empty($user_account->name)) {
          $user_account = user_load(1);
        }
        $comment = ci_import_get_empty_comment($node, $c, $user_account);
        if (!empty($previous_comment)) {
          if ($c->pid > 0) {
            $comment->pid = $previous_comment->cid;
          }
        }

        comment_submit($comment);
        comment_save($comment);

        $previous_comment = $comment;
      }
    }
  }

}
/**
 * Saves the node and does some things
 * 
 * @param type $node
 * @param type $source
 */
function ci_import_save_the_node($node, $source) {
  node_submit($node);
  $node->created = $source->created;
  $node->source_changed = $source->changed;
  $node->status  = $source->status;
  node_save($node, $source);

  db_update('node')
    ->condition('nid', $node->nid)
    ->condition('vid', $node->vid)
    ->fields(array('created' => $source->created, 'changed' => $source->changed))
    ->execute();

  db_update('node_revision')
    ->condition('nid', $node->nid)
    ->condition('vid', $node->vid)
    ->fields(array('timestamp' => $source->changed))
    ->execute();

}

/**
 * Implements hook_node_presave().
 */
function ci_import_node_presave($node) {
  if (!empty($node->source_changed)) {
    $node->changed = $node->source_changed;
  }

}

/**
 * Truncates a table
 *
 * @param type $table
 */
function ci_import_truncate($table) {
  echo "Truncating $table\n";

  db_query('TRUNCATE TABLE ' . $table);
}


/**
 * Returns a field value or an empty string if it's not there or empty
 *
 * @param type $table
 */
function ci_import_field_value($field, $element = 'value', $return = '#return#') {
  if (!empty($field[0]->$element)) {
    return $field[0]->$element;
  }
  else {
    return $return === '#return#' ? '' : $return;
  }
}

/**
 * Returns a link field array to match the D7 field form the old D6 field
 *
 * @param array $remote_links
 *   The D6 link field
 */
function ci_import_link_field_value($remote_links) {
  $return = array();
  $i      = 0;
  if (!empty($remote_links['url'])) {
    $return[$i] = array(
      'url'        => empty($remote_links['url']) ? NULL : $remote_links['url'],
      'title'      => empty($remote_links['title']) ? NULL : $remote_links['title'],
      'attributes' => empty($remote_links['attributes']) ? array() : $remote_links['attributes'],
    );
    $i++;
  }
  elseif (count($remote_links) > 0 && is_object($remote_links[0])) {

    if (is_array($remote_links)) {
      foreach ($remote_links as $link) {
        $return[$i] = array(
          'url'        => empty($link->url) ? NULL : $link->url,
          'title'      => empty($link->title) ? NULL : $link->title,
          'attributes' => empty($link->attributes) ? array() : $link->attributes,
        );
        $i++;
      }
    }
  }

  return $return;
}

/**
 * Returns body value or NULL if it's not there or empty
 *
 * @param type $table
 */
function ci_import_body_value($node) {
  if (!empty($node->body)) {
    try {
      $body = str_replace('&agrave;', 'à', $node->body);
      $body = str_replace('&Agrave;', 'À', $body);
      $body = str_replace('&nbsp;', ' ', $body);
      $body = @html_entity_decode($body);
      $body = @htmlspecialchars_decode($body);
    } catch (Exception $e) {
      $body = $node->body;
    }

    $return = array(
      'value'  => $body,
      'format' => 'full_html',
    );

    return $return;
  }
  else {
    return array('value' => '');
  }
}

/**
 * Returns body value or NULL if it's not there or empty
 *
 * @param type $table
 */
function ci_import_defaults(&$node, $source) {
  // Node title
  if (!empty($source->title)) {
    $node->title = $source->title;
  }
  else {
    $node->title = '';
  }

  // Node status
  if (!empty($source->status)) {
    $node->status = $source->status;
  }
  else {
    $node->status = 0;
  }
}

/**
 * Sets the premium status of the node
 */
function ci_import_premium(&$node, $source) {
  if (!empty($source->premium_level)) {
    $node->field_premium_content[LANGUAGE_NONE][0]['value'] = $source->premium_level->level_name;
  }

}

/**
 * Populates or unsets the role field on the user based on the lookup
 * Role names in the new DB must match names of roles in the old DB
 *
 * @staticvar type $local_roles
 * 
 * @param array $fields
 * @param object $source
 */
function ci_import_role_mapper(&$fields, $source) {
  static $local_roles;
  if (empty($local_roles)) {
    $query  = db_select('role', 'r');
    $query->fields('r', array('rid', 'name'));
    $result = $query->orderBy('r.rid')->execute();

    foreach ($result as $row) {
      $local_roles[$row->name] = $row->rid;
    }
  }
  if (!empty($source->roles)) {
    foreach ($source->roles as $rid => $name) {
      if ($name != 'Group Manager') {
        $fields['roles'][$local_roles[$name]] = $name;
      }
    }
  }
}

/**
 * Populates or unsets the taxonomy field on the node based on the lookup
 * by name of the tid from the source node.
 *
 * @param object $node
 * @param object $source
 * @param string $vocab (local vocabulary name)
 * @param string $field (local field name)
 */
function ci_import_term_mapper(&$node, $source, $vocab, $field) {
  $taxonomy = (array) $source->taxonomy;
  foreach ($taxonomy as $term) {
    $name = empty($term->name) ? NULL : $term->name;
    if (!empty($name)) {
      $new_term = taxonomy_get_term_by_name($name, $vocab);
      $tid      = empty($new_term) ? NULL : key($new_term);
      if (!empty($tid)) {
        $node->{$field}[LANGUAGE_NONE][]['tid'] = $tid;
      }
    }
  }

}

/**
 * Downloads and attaches the remote files to the local node
 *
 * @param object $node
 * @param object $source
 * @param string $local_name
 * @param string $source_name
 */
function ci_import_files(&$node, $source, $local_name, $source_name) {
  $info = field_info_instance('node', $local_name, $node->type);
  $i    = 0;
  if (!empty($source->{$source_name}) && is_object($source->{$source_name})) {
    $source->{$source_name} = (array) $source->{$source_name};
  }

  if (is_array($source->{$source_name})) {
    foreach ($source->{$source_name} as $id => $item) {

      if (empty($item->filename)) {
        continue;
      }

      $bits = explode('.', $item->filename);
      $bit  = end($bits);
      $mime = strtolower($bit);
      if (strpos('?', $mime) !== FALSE) {
        $mime = ci_import_left($mime, strpos($mime, '?'));
      }
      $images = array(
        'png',
        'jpg',
        'jpeg',
        'gif',
      );

      if (in_array($mime, $images)) {
        $schema = 'public';
      }
      else {
        $schema = 'private';
      }

      if (!empty($item)) {
        if (strlen(trim($info['settings']['file_directory'])) > 0) {
          $final_path = $schema . '://' . $info['settings']['file_directory'] . '/' . $item->filename;
        }
        else {
          $final_path = $schema . '://' . $item->filename;
        }
        $node->{$local_name}[LANGUAGE_NONE][$i] = ci_import_download_external_file(
          ci_import_remote_url() . $item->filepath, $final_path);
      }
      else {
        $node->{$local_name}[LANGUAGE_NONE] = array();
      }
      $i++;
    }
  }
}

/**
 * Downloads and attaches the remote files to the local node
 *
 * @param object $node
 * @param object $source
 * @param string $local_name
 * @param string $source_name
 */
function ci_import_attach_file_from_url(&$node, $local_name, $url) {
  $info = field_info_instance('node', $local_name, $node->type);
  if (!empty($url)) {

    $ary      = explode('/', $url);
    $filename = end($ary);
    if (mb_strpos($filename, '?') !== FALSE) {
      $filename = mb_substr($filename, 0, mb_strpos($filename, '?'));
    }

    if (strlen(trim($info['settings']['file_directory'])) > 0) {
      $final_path = 'public://' . $info['settings']['file_directory'] . '/' . $filename;
    }
    else {
      $final_path = 'public://' . $filename;
    }

    $node->{$local_name}[LANGUAGE_NONE][0] = ci_import_download_external_file(
      $url, $final_path);
  }
  else {
    $node->{$local_name}[LANGUAGE_NONE] = array();
  }
}

/**
 * Returns the uids from the old CI site.
 *
 * @return boolean|object
 */
function ci_import_get_uids() {
  return json_decode(
    file_get_contents(
      ci_import_remote_url() . 'node-json/users/'
    )
  );
}

/**
 * Returns the nids of a given type from the old CI site.
 *
 * @global object $language
 *
 * @param string $type
 *
 * @return boolean|object
 */
function ci_import_get_nids($type) {
  return json_decode(
    file_get_contents(
      ci_import_remote_url() . 'node-json/nodes/' . $type
    )
  );

}

/**
 * Returns a node by ID from the old CI site.
 *
 * @global object $language
 *
 * @param int $nid
 *
 * @return boolean|object
 */
function ci_import_get_user($uid) {
  return json_decode(
    file_get_contents(
      ci_import_remote_url() . 'node-json/user/' . $uid
    )
  );
}

/**
 * Returns a node by ID from the old CI site.
 *
 * @global object $language
 *
 * @param int $nid
 *
 * @return boolean|object
 */
function ci_import_get_node($nid) {
  return json_decode(
    file_get_contents(
      ci_import_remote_url() . 'node/' . $nid . '/json'
    )
  );

}

/**
 * Returns the URL of the old site or shows an error
 *
 * @return string|NULL
 */
function ci_import_remote_url() {
  $url = variable_get('ci_import_remote_url', NULL);

  if (empty($url)) {
    echo "You need to set the URL of the remote site eg: 'drush vset ci_import_remote_url http://example.com' \n";
    die;
  }

  if (mb_substr($url, -1) !== '/') {
    $url .= '/';
  }

  return $url;
}

/**
 * Returns the URL of the old site or shows an error
 *
 * @return string|NULL
 */
function ci_import_get_log_location() {
  $directory = variable_get('ci_import_log_location', NULL);

  if (empty($directory)) {
    echo "You need to set location to write the logs to eg: 'drush vset ci_import_log_location /home/user/logs' \n";
    die;
  }

  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    echo "Please create the $directory directory and make sure it is writable \n";
    die;
  }

  if (mb_substr($directory, -1) !== '/') {
    $directory .= '/';
  }

  return $directory;
}

/**
 * Saves a remote file to the DB and file system
 * 
 * param string $url
 *    Full url to file to download
 * param string $uri
 *    Drupal uri of where to save file private://archive/test.pdf
 * param int $save_mode
 *    File save mode from drupal core, ex FILE_EXISTS_REPLACE
 */
function ci_import_download_external_file($url, $uri, $save_mode = FILE_EXISTS_REPLACE, $manage_file = TRUE) {

  $url_info      = parse_url($url);
  $url_path_info = pathinfo($url_info['path']);

  // Dealing with hidden files
  if (strpos($url_path_info['dirname'], 'sites/all/files') !== FALSE) {
    return ci_import_copy_local_file($url, $uri, $save_mode   = FILE_EXISTS_REPLACE, $manage_file = TRUE);
  }

  //This helps with filenames with spaces
  $url = $url_info['scheme'] . '://' . $url_info['host'] . $url_path_info['dirname'] . '/' . rawurlencode($url_path_info['basename']);

  //Need to remove the filename from the uri
  $uri_target    = file_uri_target($uri);
  $uri_scheme    = file_uri_scheme($uri);
  $uri_path_info = pathinfo($uri_target);
  $directory     = file_stream_wrapper_uri_normalize($uri_scheme . "://" . $uri_path_info['dirname']);

  if (file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    $drupal_result = drupal_http_request($url);
    if (!empty($drupal_result->data)) {
      $path = file_stream_wrapper_uri_normalize($uri);
      if ($manage_file) {
        $new_file = file_save_data($drupal_result->data, $path, $save_mode);
      }
      else {
        return file_unmanaged_save_data($drupal_result->data, $path, $save_mode);
      }
    }
    else {
      drupal_set_message("Error downloading file, no data recieved for " . $url);
      return FALSE;
    }

    $new_file->display = 1;
    return (array) $new_file;
  }
  else {
    drupal_set_message("Could not create directory");
  }
}

function ci_import_fix_images_in_body($body) {

  global $base_url;

  preg_match_all('/<img[^>]+>/i', $body, $images);

  $img = array();
  foreach ($images[0] as $img_tag) {
    preg_match_all('/(alt|title|src)=("[^"]*")/i', $img_tag, $img[]);
  }


  foreach ($img as $key => $value) {
    $src_key = array_search('src', $value[1]);
    $old_src = trim($value[2][$src_key], '"');

    if (ci_import_left($old_src, 1) == '/') {
      $url = 'http://old.emptyhomenetwork/' . $old_src;
    }
    else {
      $url = $old_src;
    }

    $url = mb_str_replace('//', '/', $url);
    $url = mb_str_replace('http:', 'http:/', $url);
    $url = mb_str_replace('https:', 'https:/', $url);
    $url = mb_str_replace('system/files', 'sites/all/files_hidden_01', $url);
    $url = mb_str_replace('http://www.ehnetwork.org.uk/', 'http://old.emptyhomenetwork/', $url);
    $url = mb_str_replace('http://ehnetwork.org.uk/', 'http://old.emptyhomenetwork/', $url);

    $ary      = explode('/', $old_src);
    $filename = end($ary);
    if (mb_strpos($filename, '?') !== FALSE) {
      $filename = mb_substr($filename, 0, mb_strpos($filename, '?'));
    }

    $final_path = 'public://' . $filename;

    $drupal_result = ci_import_get($url);
    if (!empty($drupal_result)) {
      $path     = file_stream_wrapper_uri_normalize($uri);
      $new_file = file_save_data($drupal_result, $final_path, FILE_EXISTS_REPLACE);
      $new_url = file_create_url($new_file->uri);
      $new_url = mb_str_replace($base_url, '', $new_url);
      $body    = mb_str_replace($old_src, $new_url, $body);
    }
  }
  return $body;

}

/**
 * Multibyte str replace
 */
if (!function_exists('mb_str_replace')) {

  function mb_str_replace($search, $replace, $subject, &$count = 0) {
    if (!is_array($subject)) {
      $searches     = is_array($search) ? array_values($search) : array($search);
      $replacements = is_array($replace) ? array_values($replace) : array($replace);
      $replacements = array_pad($replacements, count($searches), '');
      foreach ($searches as $key => $search) {
        $parts   = mb_split(preg_quote($search), $subject);
        $count += count($parts) - 1;
        $subject = implode($replacements[$key], $parts);
      }
    }
    else {
      foreach ($subject as $key => $value) {
        $subject[$key] = mb_str_replace($search, $replace, $value, $count);
      }
    }
    return $subject;

  }

}

/**
 * Replacement for ASP left function
 *
 * @param str $str
 *   the string to cut
 * @param int $count
 *   the length to cut
 */
function ci_import_left($str, $count) {
  return mb_substr($str, 0, $count);

}

 /**
 * The cURL wrapper
 *
 * @param $urll
 *   The URL to get
 *
 * @param array $opts
 *   A keyed array containing any parameters that I may need
 *   - tmp             - (optional) The location of the temporary file to create to hold the response
 *   - cookie_jar      - (optional) The location of the cookies folder
 *   - headers         - (optional) The headers to send for the request
 *   - user_agent      - (optional) The user agent used for the request
 *   - encoding        - (optional) The encoding
 *   - time_out        - (optional) The connection time out limit in seconds
 *   - range           - (optional) The Byte range to get
 *   - low_speed_limit - (optional) See description in private function
 *   - low_speed_time  - (optional) See description in private function
 *
 * @return string
 *   Either the data or the location of the temporary file that is holding the data
 */
 function ci_import_get($url, $opts = array()) {
  // a new cURL instance
  $ch = curl_init();
  // set the URL to the cURL options
  curl_setopt($ch, CURLOPT_URL, $url);
  // The cookie jar
  if (!empty($opts['cookie_jar'])) {
    $cookie = tempnam($opts['cookie_jar'], "cookie");
  }
  else {
    $cookie = tempnam(sys_get_temp_dir(), "cookie");
  }
  curl_setopt($ch, CURLOPT_COOKIEFILE, $cookie);
  curl_setopt($ch, CURLOPT_COOKIEJAR, $cookie);
  // the headers
  if (!empty($opts['headers']) && is_array($opts['headers'])) {
    $headers = $opts['headers'];
  }
  else {
    $headers   = array();
    $headers[] = "Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5";
    $headers[] = "Connection: keep-alive";
    $headers[] = "Keep-Alive: 115";
    $headers[] = "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7";
    $headers[] = "Accept-Language: en-us,en;q=0.5";
    $headers[] = "Pragma: ";
  }
  curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
  // The user agent
  if (!empty($opts['user_agent'])) {
    $user_agent = $opts['user_agent'];
  }
  else {
    $user_agent = 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1025.162 Safari/535.19';
  }
  curl_setopt($ch, CURLOPT_USERAGENT, $user_agent);
  // The encoding
  if (!empty($opts['encoding'])) {
    $encoding = $opts['encoding'];
  }
  else {
    $encoding = 'gzip,deflate';
  }
  curl_setopt($ch, CURLOPT_ENCODING, $encoding);
  // The Connection time out in seconds
  if (!empty($opts['time_out'])) {
    $time_out = $opts['time_out'];
  }
  else {
    $time_out = 60;
  }
  curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $time_out);
  // Used with CURLOPT_LOW_SPEED_TIME. If the transfer speed falls below
  // this value in bytes per second for longer than CURLOPT_LOW_SPEED_TIME,
  // the transfer is aborted.
  if (!empty($opts['low_speed_limit'])) {
    $low_speed_limit = $opts['low_speed_limit'];
  }
  else {
    $low_speed_limit = 10240;
  }
  curl_setopt($ch, CURLOPT_LOW_SPEED_LIMIT, $low_speed_limit);
  // Used with CURLOPT_LOW_SPEED_LIMIT. If the transfer speed falls below the
  // value given with the CURLOPT_LOW_SPEED_LIMIT option for longer than the
  // number of seconds given with CURLOPT_LOW_SPEED_TIME, the transfer is aborted.
  if (!empty($opts['low_speed_time'])) {
    $low_speed_time = $opts['low_speed_time'];
  }
  else {
    $low_speed_time = 60;
  }
  curl_setopt($ch, CURLOPT_LOW_SPEED_TIME, $low_speed_time);
  // The range of bytes to get from the target
  if (!empty($opts['range'])) {
    curl_setopt($ch, CURLOPT_RANGE, $opts['range']);
  }
  // these are always the same for my purpose
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
  // if we are writing this to a temporary file then return the file location
  if (!empty($opts['tmp'])) {
    // open the temp file if necessary
    $fp   = fopen($opts['tmp'], 'w');
    curl_setopt($ch, CURLOPT_FILE, $fp);
    $data = curl_exec($ch);
    curl_close($ch);
    fclose($fp);
    return $opts['tmp'];
  }
  else {
    // or just return the data
    $data = curl_exec($ch);
    curl_close($ch);
    return $data;
  }

}

/**
 * Saves a remote file to the DB and file system
 *
 * param string $url
 *    Full url to file to download
 * param string $uri
 *    Drupal uri of where to save file private://archive/test.pdf
 * param int $save_mode
 *    File save mode from drupal core, ex FILE_EXISTS_REPLACE
 */
function ci_import_copy_local_file($url, $uri, $save_mode = FILE_EXISTS_REPLACE, $manage_file = TRUE) {

  $url_info      = parse_url($url);
  $url_path_info = pathinfo($url_info['path']);

  //This helps with filenames with spaces
  $url = '/home/tgould/www/emptyhomenetwork_old' . $url_path_info['dirname'] . '/' . rawurlencode($url_path_info['basename']);
  $url           = urldecode($url);
  //Need to remove the filename from the uri
  $uri_target    = file_uri_target($uri);
  $uri_scheme    = file_uri_scheme($uri);
  $uri_path_info = pathinfo($uri_target);
  $directory     = file_stream_wrapper_uri_normalize($uri_scheme . "://" . $uri_path_info['dirname']);

  if (file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    $drupal_result = file_get_contents($url);
    if (!empty($drupal_result)) {
      $path = file_stream_wrapper_uri_normalize($uri);
      if ($manage_file) {
        $new_file = file_save_data($drupal_result, $path, $save_mode);
      }
      else {
        return file_unmanaged_save_data($drupal_result, $path, $save_mode);
      }
    }
    else {
      drupal_set_message("Error downloading file, no data recieved for " . $url);
      return FALSE;
    }

    $new_file->display = 1;
    return (array) $new_file;
  }
  else {
    drupal_set_message("Could not create directory");
  }

}
