<?php

/**
 * @file
 *     Import functions for the import jobs
 */

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_page($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node = ci_import_get_empty_node('page');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  $node->body[LANGUAGE_NONE][0] = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_term_mapper($node, $source, 'issues', 'field_issues');
  ci_import_term_mapper($node, $source, 'practice', 'field_practice');

  ci_import_files($node, $source, 'field_file', 'files');

  $node->field_source_nid[LANGUAGE_NONE][0]['value'] = $source->nid;

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_casestudy($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node = ci_import_get_empty_node('casestudy');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  $node->body[LANGUAGE_NONE][0] = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_term_mapper($node, $source, 'issues', 'field_issues');
  ci_import_term_mapper($node, $source, 'places', 'field_places');
  ci_import_term_mapper($node, $source, 'organisation', 'field_organisation');
  ci_import_term_mapper($node, $source, 'status', 'field_status');
  ci_import_term_mapper($node, $source, 'practice', 'field_practice');

  ci_import_files($node, $source, 'field_file', 'files');

  $node->field_source_nid[LANGUAGE_NONE][0]['value'] = $source->nid;

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_blog($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node = ci_import_get_empty_node('blog');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  $node->body[LANGUAGE_NONE][0]          = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_term_mapper($node, $source, 'issues', 'field_issues');
  ci_import_term_mapper($node, $source, 'places', 'field_places');
  ci_import_term_mapper($node, $source, 'organisation', 'field_organisation');
  ci_import_term_mapper($node, $source, 'practice', 'field_practice');

  ci_import_files($node, $source, 'field_file', 'files');

  $node->field_source_nid[LANGUAGE_NONE][0]['value'] = $source->nid;

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_around_the_web($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node = ci_import_get_empty_node('around_the_web');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  $node->body[LANGUAGE_NONE][0]          = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_term_mapper($node, $source, 'issues', 'field_issues');
  ci_import_term_mapper($node, $source, 'places', 'field_places');

  $node->field_link[LANGUAGE_NONE] = ci_import_link_field_value($source->field_aroundweb_link);

  $node->field_source_nid[LANGUAGE_NONE][0]['value'] = $source->nid;

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a library_item node
 *
 * @param object $source
 */
function ci_import_import_library_item($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node = ci_import_get_empty_node('library_item');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  ci_import_term_mapper($node, $source, 'organisation', 'field_organisation');
  ci_import_term_mapper($node, $source, 'places', 'field_places');
  ci_import_term_mapper($node, $source, 'issues', 'field_issues');
  ci_import_term_mapper($node, $source, 'archive_issues', 'field_archived_issues');
  ci_import_term_mapper($node, $source, 'practice', 'field_practice');
  ci_import_term_mapper($node, $source, 'status', 'field_status');
  ci_import_term_mapper($node, $source, 'tags', 'field_tags');
  ci_import_term_mapper($node, $source, 'document_type', 'field_document_type');

  // field_show_promo_link
  $node->field_link[LANGUAGE_NONE] = ci_import_link_field_value($source->field_url);

  ci_import_files($node, $source, 'field_file', 'field_file');
  ci_import_files($node, $source, 'field_lib_images', 'field_lib_images');

  $node->body[LANGUAGE_NONE][0]['value']           = ci_import_field_value(
    $source->field_notes
  );
  $node->body[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  $node->body[LANGUAGE_NONE][0]['value']  = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  $node->field_infotype[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
    $source->field_typess
  );
  $node->field_year[LANGUAGE_NONE][0]['value']     = ci_import_field_value(
    $source->field_year
  );

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_story($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node          = ci_import_get_empty_node('story');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  ci_import_term_mapper($node, $source, 'news_type', 'field_news_type');
  ci_import_term_mapper($node, $source, 'organisation', 'field_organisation');
  ci_import_term_mapper($node, $source, 'places', 'field_places');
  ci_import_term_mapper($node, $source, 'issues', 'field_issues');
  ci_import_term_mapper($node, $source, 'archive_issues', 'field_archived_issues');
  ci_import_term_mapper($node, $source, 'practice', 'field_practice');
  ci_import_term_mapper($node, $source, 'status', 'field_status');
  ci_import_term_mapper($node, $source, 'tags', 'field_tags');
  ci_import_term_mapper($node, $source, 'document_type', 'field_document_type');

  ci_import_files($node, $source, 'field_image', 'field_main_image');

  $node->body[LANGUAGE_NONE][0] = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_image($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node          = ci_import_get_empty_node('image');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  ci_import_term_mapper($node, $source, 'organisation', 'field_organisation');
  ci_import_term_mapper($node, $source, 'places', 'field_places');
  ci_import_term_mapper($node, $source, 'issues', 'field_issues');
  ci_import_term_mapper($node, $source, 'archive_issues', 'field_archived_issues');
  ci_import_term_mapper($node, $source, 'practice', 'field_practice');
  ci_import_term_mapper($node, $source, 'status', 'field_status');
  ci_import_term_mapper($node, $source, 'tags', 'field_tags');
  ci_import_term_mapper($node, $source, 'document_type', 'field_document_type');


  $url = 'http://www.ehnetwork.org.uk/' . $source->images->_original;
  ci_import_attach_file_from_url($node, 'field_image', $url);

  $node->body[LANGUAGE_NONE][0] = ci_import_body_value($source);

  $node->field_source_nid[LANGUAGE_NONE][0]['value'] = $source->nid;

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_simplenews($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node          = ci_import_get_empty_node('simplenews');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  ci_import_term_mapper($node, $source, 'newsletter', 'field_simplenews_term');

  $node->body[LANGUAGE_NONE][0]          = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_files($node, $source, 'field_file', 'files');

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_event($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node          = ci_import_get_empty_node('event');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  ci_import_term_mapper($node, $source, 'issues', 'field_issues');

  $node->body[LANGUAGE_NONE][0]          = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_files($node, $source, 'field_file', 'files');

  // field_show_promo_link
  $node->field_link[LANGUAGE_NONE] = ci_import_link_field_value($source->field_event_link);

  $node->field_contact_details[LANGUAGE_NONE][0]['value']  = ci_import_field_value(
    $source->field_contact_details
  );
  $node->field_contact_details[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  $node->field_contact_details[LANGUAGE_NONE][0]['value']  = ci_import_fix_images_in_body($node->field_contact_details[LANGUAGE_NONE][0]['value']);

  $node->field_event_description[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
    $source->field_event_description
  );
  $node->field_event_description[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  $node->field_event_description[LANGUAGE_NONE][0]['value']  = ci_import_fix_images_in_body($node->field_event_description[LANGUAGE_NONE][0]['value']);

  $node->field_event_type[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
    $source->field_event_type
  );
  $node->field_location[LANGUAGE_NONE][0]['value']   = ci_import_field_value(
    $source->field_location
  );
  $node->field_region[LANGUAGE_NONE][0]['value']     = ci_import_field_value(
    $source->field_region
  );

  $node->field_event_date[LANGUAGE_NONE][0]['value']  = $source->event->start_utc;
  $node->field_event_date[LANGUAGE_NONE][0]['value2'] = $source->event->end_utc;

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_forum($source) {

  global $user;
  $user = user_load_by_mail($source->user_account->mail);
  $node          = ci_import_get_empty_node('forum');

  ci_import_defaults($node, $source);
  ci_import_premium($node, $source);

  ci_import_term_mapper($node, $source, 'forums', 'taxonomy_forums');

  $node->body[LANGUAGE_NONE][0]          = ci_import_body_value($source);
  $node->body[LANGUAGE_NONE][0]['value'] = ci_import_fix_images_in_body($node->body[LANGUAGE_NONE][0]['value']);

  ci_import_save_the_node($node, $source);
  ci_import_comments($node, $source);

  $node->remote_nid = $source->nid;

  return $node;

}

/**
 * Purges all content
 */
function drush_ci_import_terms() {
  $organisation_vid = db_query("SELECT vid FROM taxonomy_vocabulary WHERE name = 'organisation'")->fetchField();
  $places_vid       = db_query("SELECT vid FROM taxonomy_vocabulary WHERE name = 'places'")->fetchField();
  $issues_vid       = db_query("SELECT vid FROM taxonomy_vocabulary WHERE name = 'issues'")->fetchField();



  if (($handle = fopen(__DIR__ . "/taxonomy_csvs/organisation.csv", "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
      $term              = new stdClass();
      $term->name        = trim($data[2]);
      $term->vid         = $organisation_vid;
      $term->description = empty(trim($data[3])) ? '' : trim($data[3]);
      if (!empty($term->name)) {
        taxonomy_term_save($term);
      }
    }
    fclose($handle);
  }
  if (($handle = fopen(__DIR__ . "/taxonomy_csvs/places.csv", "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
      $term              = new stdClass();
      $term->name        = trim($data[2]);
      $term->vid         = $places_vid;
      $term->description = empty(trim($data[3])) ? '' : trim($data[3]);
      if (!empty($term->name)) {
        taxonomy_term_save($term);
      }
    }
    fclose($handle);
  }
  if (($handle = fopen(__DIR__ . "/taxonomy_csvs/issues.csv", "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
      $term              = new stdClass();
      $term->name        = trim($data[2]);
      $term->vid         = $issues_vid;
      $term->description = empty(trim($data[3])) ? '' : trim($data[3]);
      if (!empty($term->name)) {
        taxonomy_term_save($term);
      }
    }
    fclose($handle);
  }

}

/**
 * Imports all the users
 */
function drush_ci_import_users() {
  $log_location = ci_import_get_log_location();
  $fp           = fopen($log_location . '/ci_import_log_users.csv', 'w');

  $columns = array(
    'Name',
    'Mail',
    'Password',
    'Created',
    'Access',
    'Status',
    'Init',
    'Roles',
    'Newsletter',
  );

  fputcsv($fp, $columns, ',', '"');

  $uids = ci_import_get_uids();
  foreach ($uids as $uid) {
    $source = ci_import_get_user($uid);

    if ($source->name == 'admin') {
      $source->name = 'EHNAdmin';
    }

    $password = user_password(8);

    //set up the user fields
    $fields = array(
      'name'    => $source->name,
      'mail'    => $source->mail,
      'pass'    => $password,
      'created' => $source->created,
      'access'  => $source->access,
      'status'  => $source->status,
      'init'    => 'email address',
      'roles'   => array(), // This is empty as we'll pass it to the role mapper
    );

    ci_import_role_mapper($fields, $source);

    $account = user_save('', $fields);
    $profile = profile2_create(array('type' => 'main', 'uid' => $account->uid));

    $profile->field_profile_status[LANGUAGE_NONE][0]['value']       = $source->profile_status;
    $profile->field_type[LANGUAGE_NONE][0]['value']                 = $source->profile_membertype;
    $profile->field_lead_member[LANGUAGE_NONE][0]['value']          = $source->profile_Lead_Member;
    $profile->field_first_name[LANGUAGE_NONE][0]['value']           = $source->profile_firstname;
    $profile->field_surname[LANGUAGE_NONE][0]['value']              = $source->profile_surname;
    $profile->field_job_title[LANGUAGE_NONE][0]['value']            = $source->profile_JobTitle;
    $profile->field_profile_organisation[LANGUAGE_NONE][0]['value'] = $source->profile_organisation;
    $profile->field_telno_1[LANGUAGE_NONE][0]['value']              = $source->profile_telno1;
    $profile->field_telno_2[LANGUAGE_NONE][0]['value']              = $source->profile_telno2;


    profile2_save($profile);

    if ($source->newsletter_subscrbed) {
      simplenews_subscribe_user($account->mail, 2536, FALSE, 'website');
    }
    else {
      simplenews_unsubscribe_user($account->mail, 2536, FALSE, 'website');
    }

    echo "Imported User: " . $source->name . "\n";

    $csv_row          = $fields;
    $csv_row['roles'] = array();
    foreach ($fields['roles'] as $rid => $name) {
      $csv_row['roles'][] = $name;
    }
    $csv_row['roles']      = implode(', ', $csv_row['roles']);
    $csv_row['Newsletter'] = $source->newsletter_subscrbed;

    fputcsv($fp, $csv_row, ',', '"');
  }
  fclose($fp);

}
