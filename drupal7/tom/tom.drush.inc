<?php

/**
 * Implements hook_drush_command().
 */
function tom_drush_command() {
  $items['tom'] = array(
    'description' => dt('Does a thing'),
  );
  return $items;
}

/**
 * Does a thing
 */
function drush_tom() {
  
}