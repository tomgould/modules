<?php

/**
 * Implements hook_drush_command().
 */
function ines_report_drush_command() {
  $items['report'] = array(
      'description' => dt('Does a thing'),
  );
  return $items;
}

/**
 * Does a thing
 */
function drush_ines_report_report() {
  drush_ines_report();
}
