<?php

/**
 * @file
 * Drush commands for  cron_downloader
 */
function cron_downloader_drush_command() {
  $items = array();

  $items['cron_downloader_download'] = array(
      'callback' => 'drush_cron_downloader_save_rss',
      'arguments' => array(
          'url' => 'The URL of the data you want to save.',
          'destination' => 'public private or temporary, defaults to public',
      ),
      'aliases' => array('cdd', 'cd_download', 'cd_get'),
  );

  return $items;
}

/**
 * Saves the data from the URL to the private file system in the rss directory
 *
 * @param type $url
 */
function drush_cron_downloader_save_rss($url = NULL, $destination = 'public') {
  if (empty($url)) {
    watchdog("cron_downloader", "No URL was supplied to cron_downloader_download");
    return drush_set_error(dt("No URL was supplied to cron_downloader_download"));
  }

  $basename = basename($url);
  $uri = "$destination://cron_downloader/$basename";

  cron_downloader_download_external_file($url, $uri, FILE_EXISTS_REPLACE, TRUE);
}
