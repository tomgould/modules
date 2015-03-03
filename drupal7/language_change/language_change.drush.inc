<?php
/**
 * @file
 * Programmatically change the language of content
 */

/**
 * Implements hook_drush_command().
 */
function language_change_drush_command() {
  $items['language-change'] = array(
    'description'         => "Programmatically change the language of content",
  );
  return $items;
}

/**
 * Programmatically change the language of all nodes and their fields
 */
function drush_language_change() {

  $lang_from = 'it';
  $lang_to   = 'es';

  $query  = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $result = $query->execute();
  $nids   = array_keys($result['node']);
  $n      = count($nids);

  foreach ($nids as $i => $nid) { // go through ALL nodes
    $node        = node_load($nid); // load the node
    $type        = $node->type; // get the content type
    $field_langs = field_language('node', $node); // get the language of each field
    foreach ($field_langs as $field => $lang) { // go through ALL field of this node
      if ($lang == $lang_from) { // if the field is in the wrong language
        $items = field_get_items('node', $node, $field, $lang); // get all field values
        if (!empty($items)) {
          $node->{$field}[$lang_to] = $items; // put it under language neutral
          unset($node->{$field}[$lang]); // remove the old language
        }
      }
    }
    if ($node->language == $lang_from) {
      $node->language = $lang_to; // set the node language to neutral
      node_save($node); // commit changes
    }

    echo ("$i/$n\tnid=$nid\t$type\n"); // progress report
  }
}
