<?php

/**
 * @file
 *    Drsh commands for the import jobs
 */

/**
 * Implements hook_drush_command().
 */
function ines_import_drush_command() {
  $items['ines-import-article'] = array(
    'description' => dt('imports an article from the old siote\'s DB on Amazon'),
    'arguments'   => array(
      'article_id' => dt('The old ID of the article'),
    ),
  );
  $items['ines-import-array']   = array(
    'description' => dt('imports many articles from the old siote\'s DB on Amazon'),
  );

  return $items;

}

/**
 * imports content
 */
function drush_ines_import_article($article_id = FALSE) {
  global $user;
  $user = user_load(1);

  if (!$article_id) {
    echo "Please supply tan article ID form the old site\n";
    return FALSE;
  }
  else {
    ines_import_import_content($article_id);
  }

}
/**
 * imports content
 */
function drush_ines_import_array() {
  global $user;
  $user = user_load(1);

  $array = array(
    "10433877",
    "10400291",
    "10385581",
    "10268646",
    "10203978",
    "10188207",
    "10188190",
    "10158336",
    "9956702",
    "9885652",
    "9796338",
    "9794696",
    "9567736",
    "9314088",
    "9078487",
    "9044984",
    "8958983",
    "8940971",
    "8900319",
    "8836700",
    "8834290",
    "8814929",
    "8792157",
    "8734361",
    "8706612",
    "8698198",
    "8663578",
    "8624316",
    "8616336",
    "8554407",
    "8547701",
  );

  foreach ($array as $article_id) {
    ines_import_import_content($article_id);
  }

}
