<?php

/**
 * @file
 *    Drsh commands for the import jobs
 */

/**
 * Implements hook_drush_command().
 */
function ci_import_drush_command() {
  // Helpers
  $items['ci-import-purge']       = array(
    'description' => dt('Purges all content'),
  );

  $items['ci-import-types']       = array(
    'description' => dt('Show the local content types'),
  );

  // Nodes
  $items['ci-import']             = array(
    'description' => dt('Import all iframe_page nodes'),
    'arguments'   => array(
      'importer_function' => dt('The name of the importer to use with the remote content type (without leading "ci_import_import_")'),
      'remote_type'       => dt('The remote machine name of the content type to import.'),
    ),
  );
  $items['ci-import-delete']      = array(
    'description' => dt('Import all iframe_page nodes'),
    'arguments'   => array(
      'type' => dt('The content type to delete all nodes of")'),
    ),
  );

  // Users
  $items['ci-import-purge-users'] = array(
    'description' => dt('Purges all Users'),
  );
  $items['ci-import-users']        = array(
    'description' => dt('Import all Users'),
  );

  // Terms
  $items['ci-import-terms']       = array(
    'description' => dt('Import all Users'),
  );

  return $items;

}

/**
 * imports content
 */
function drush_ci_import($importer_function = FALSE, $remote_type = FALSE) {
  if (!$importer_function || !$remote_type) {
    echo "Please supply the local and remote node types\n";
    return FALSE;
  }
  else {
    ci_import_import_content($importer_function, $remote_type);
  }

}

/**
 * Purges all content
 */
function drush_ci_import_purge() {

  // Dont want to do this on this site
  // 
  // ci_import_purge_all_content();

}

/**
 * Purges all content
 */
function drush_ci_import_delete($type) {
  $query  = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->condition('n.type', $type);
  $result = $query->execute();

  foreach ($result as $row) {
    node_delete($row->nid);
  }

}

/**
 * Purges all content
 */
function drush_ci_import_purge_users() {
  ci_import_purge_all_users();

}

/**
 * Show the local content types
 */
function drush_ci_import_types() {
  $query  = db_select('node_type', 't');
  $query->fields('t', array('type'));
  $result = $query->orderBy('t.type')->execute();

  foreach ($result as $type) {
    echo $type->type . "\n";
  }

}
