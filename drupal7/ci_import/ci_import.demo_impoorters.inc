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
function ci_import_import_faq($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('faq');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'faq_categories', 'field_faq_categories');

  $node->body[$language->language][0] = ci_import_body_value($source);

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a advert node
 *
 * @param object $source
 */
function ci_import_import_advert($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('advert');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'advert_blocks', 'field_advert_blocks');

  $node->field_advert_pages[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_advert_pages
  );
  $node->field_replacement_embed[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_replacement_embed
  );
  $node->field_advert_embedding_html[LANGUAGE_NONE][0]['value'] = $source->body;

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a characters node
 *
 * @param object $source
 */
function ci_import_import_characters($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('characters');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'show', 'field_show');

  ci_import_files($node, $source, 'field_character_main_image', 'field_characters_main_image');
  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');

  $node->field_character_main_text[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_characters_main_text
  );
  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_shared_promo_text
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a pictures_wallpapers node
 *
 * @param object $source
 */
function ci_import_import_pictures_wallpapers($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('pictures_wallpapers');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'show', 'field_show');

  $node->body[$language->language][0] = ci_import_body_value($source);

  ci_import_files($node, $source, 'field_pictures_main', 'field_pictures_main');
  ci_import_files($node, $source, 'field_pictures_files', 'field_pictures_files');
  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');

  $node->field_pictures_description[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_pictures_description
  );
  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_shared_promo_text
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a print colour node
 *
 * @param object $source
 */
function ci_import_import_print_colour($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('print_colour');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'show', 'field_show');

  $node->body[$language->language][0] = ci_import_body_value($source);

  ci_import_files($node, $source, 'field_shared_dl_preview', 'field_shared_dl_preview');
  ci_import_files($node, $source, 'field_shared_dl_file', 'field_shared_dl_file');
  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');

  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_shared_promo_text
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a print make node
 *
 * @param object $source
 */
function ci_import_import_print_make($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('print_make');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'show', 'field_show');

  $node->body[$language->language][0] = ci_import_body_value($source);

  ci_import_files($node, $source, 'field_shared_dl_preview', 'field_shared_dl_preview');
  ci_import_files($node, $source, 'field_shared_dl_file', 'field_shared_dl_file');
  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');

  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_shared_promo_text
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a show node
 *
 * @param object $source
 */
function ci_import_import_show_brand($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('show_brand');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'show', 'field_show');

  ci_import_files($node, $source, 'field_show_body_background', 'field_show_body_background');
  ci_import_files($node, $source, 'field_show_menu_image', 'field_show_menu_image');
  ci_import_files($node, $source, 'field_show_background_image', 'field_show_background_image');
  ci_import_files($node, $source, 'field_show_promo_border', 'field_show_promo_border');
  ci_import_files($node, $source, 'field_show_promo_label', 'field_show_promo_label');
  ci_import_files($node, $source, 'field_show_teaser_image', 'field_show_teaser_image');
  ci_import_files($node, $source, 'field_show_feature_swf', 'field_show_feature_swf');
  ci_import_files($node, $source, 'field_show_foreground_image', 'field_show_foreground_image');
  ci_import_files($node, $source, 'field_show_icon_image', 'field_show_icon_image');
  ci_import_files($node, $source, 'field_show_main_image', 'field_show_main_image');
  ci_import_files($node, $source, 'field_show_promo_image', 'field_show_promo_image');
  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');
  ci_import_files($node, $source, 'field_show_generic_image', 'field_show_generic_image');
  ci_import_files($node, $source, 'field_show_picture_image', 'field_show_picture_image');

  $node->field_show_premium_show[LANGUAGE_NONE][0]['value']  = ci_import_field_value(
    $source->field_show_premium_show, 'value', 0
  );
  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value']  = ci_import_field_value(
    $source->field_shared_promo_text
  );
  $node->field_show_bottom_teaser[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_show_bottom_teaser
  );
  $node->field_show_seo_text[LANGUAGE_NONE][0]['value']      = ci_import_field_value(
    $source->field_show_seo_text
  );
  $node->field_show_generic_text[LANGUAGE_NONE][0]['value']  = ci_import_field_value(
    $source->field_show_generic_text
  );
  $node->field_show_picture_text[LANGUAGE_NONE][0]['value']  = ci_import_field_value(
    $source->field_show_picture_text
  );

  // field_show_promo_link
  $node->field_show_promo_link[LANGUAGE_NONE] = ci_import_link_field_value($source->field_show_promo_link);

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a video or a song node
 *
 * @param object $source
 */
function ci_import_import_video_song($source) {

  global $user, $language;
  $user = user_load(1);
  $is_song = (int) $source->field_video_video_or_song[0]->value;
  // This function does songs and videos as they were the same in the old site
  if ($is_song === 1) {
      $node = ci_import_get_empty_node('song');
  }
  else {
      $node = ci_import_get_empty_node('video');
  }
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'show', 'field_show');

  $node->field_brightcove_id[LANGUAGE_NONE][0]['value']      = ci_import_field_value(
    $source->field_bc_brightcove_vid
  );
  $node->field_shared_promo_text [LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_shared_promo_text
  );
  $node->field_video_short_description [LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_bc_short_desc
  );
  $node->field_kaltura_id[LANGUAGE_NONE][0]['value']               = '1_ofgx3wps';

  if ($is_song === 1) {
    ci_import_attach_file_from_url($node, 'field_song_thumbnail', $source->field_bc_thumbnail_url[0]->value);

    $node->field_song_lyrics [LANGUAGE_NONE][0]['value'] = ci_import_field_value(
            $source->field_video_lyrics
    );
  }
  else {
    ci_import_attach_file_from_url($node, 'field_video_thumbnail', $source->field_bc_thumbnail_url[0]->value);
  }

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a game node
 *
 * @param object $source
 */
function ci_import_import_game($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('game');
  ci_import_defaults($node, $source);
  ci_import_term_mapper($node, $source, 'show', 'field_show');

  $node->body[$language->language][0] = ci_import_body_value($source);

  // The games int he old site can be iframe or flash
  if ($source->field_game_format[0]->value === 'flash') {
    ci_import_files($node, $source, 'field_game_zipfile', 'field_game_zipfile');
  }
  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');
  ci_import_files($node, $source, 'field_game_placeholder', 'field_game_placeholder');

  $node->field_game_format[LANGUAGE_NONE][0]['value']        = ci_import_field_value(
    $source->field_game_format
  );
  $node->field_page_flash_height[LANGUAGE_NONE][0]['value']  = ci_import_field_value(
    $source->field_game_height_full_page, 'value', 0
  );
  $node->field_page_flash_width[LANGUAGE_NONE][0]['value']   = ci_import_field_value(
    $source->field_game_width_full_page, 'value', 0
  );
  $node->field_page_swf_filename[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_game_swf_filename
  );
  $node->field_game_flashvars[LANGUAGE_NONE][0]['value']     = ci_import_field_value(
    $source->field_game_flashvars
  );
  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value']  = ci_import_field_value(
    $source->field_shared_promo_text
  );
  $node->field_order_on_show_page[LANGUAGE_NONE][0]['value'] = 0;

  if ($source->field_game_format[0]->value === 'flash') {
    $form_state['values']['field_game_zipfile'][LANGUAGE_NONE][0]['fid'] = $node->field_game_zipfile[LANGUAGE_NONE][0]['fid'];
    flash_game_upload(array(), $form_state);
  }

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a custom_background node
 *
 * @param object $source
 */
function ci_import_import_custom_background($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('custom_background');
  ci_import_defaults($node, $source);

  ci_import_files($node, $source, 'field_custom_background_bg', 'field_custom_background_bg');

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a recipe node
 *
 * @param object $source
 */
function ci_import_import_recipe($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('recipe');
  ci_import_defaults($node, $source);

  ci_import_files($node, $source, 'field_recipe_finished_image', 'field_recipe_finished_image');
  ci_import_files($node, $source, 'field_recipe_in_progress', 'field_recipe_in_progress');
  ci_import_files($node, $source, 'field_shared_dl_file', 'field_shared_dl_file');
  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');

  $node->body[$language->language][0] = ci_import_body_value($source);

  $node->field_recipe_ingredients_list[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_recipe_ingredients_list
  );
  $node->field_recipe_method[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_recipe_method
  );
  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value']       = ci_import_field_value(
    $source->field_shared_promo_text
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a page node
 *
 * @param object $source
 */
function ci_import_import_page($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('page');
  ci_import_defaults($node, $source);

  $node->body[$language->language][0] = ci_import_body_value($source);

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a grown ups node
 *
 * @param object $source
 */
function ci_import_import_grown_ups($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('grown_ups');
  ci_import_defaults($node, $source);

  $node->body[$language->language][0] = ci_import_body_value($source);

  ci_import_files($node, $source, 'field_grown_ups_image', 'field_grown_ups_image');
  ci_import_files($node, $source, 'field_grown_ups_attachment', 'field_grown_ups_attachment');

  // field_show_promo_link
  $node->field_grown_ups_links[LANGUAGE_NONE] = ci_import_link_field_value(
    $source->field_grown_ups_links
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a grown ups node
 *
 * @param object $source
 */
function ci_import_import_iframe_page($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('iframe_page');
  ci_import_defaults($node, $source);

  $node->body[$language->language][0] = ci_import_body_value($source);

  ci_import_files($node, $source, 'field_shared_promo_image', 'field_shared_promo_image');

  $node->field_shared_promo_text[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_shared_promo_text
  );
  $node->field_page_iframe_src[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_page_iframe_src
  );
  $node->field_page_iframe_width[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_page_iframe_width, 'value', 0
  );
  $node->field_page_iframe_height[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
          $source->field_page_iframe_height, 'value', 0
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a grown ups node
 *
 * @param object $source
 */
function ci_import_import_birthday_app_assets($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('birthday_app_assets');
  ci_import_defaults($node, $source);

  $node->body[$language->language][0] = ci_import_body_value($source);

  ci_import_files($node, $source, 'field_bday_app_logo', 'field_bday_app_logo');
  ci_import_files($node, $source, 'field_bday_app_main_bg', 'field_bday_app_main_bg');
  ci_import_files($node, $source, 'field_bday_app_bg', 'field_bday_app_bg');
  ci_import_files($node, $source, 'field_bday_app_sticker', 'field_bday_app_sticker');

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}

/**
 * Creates a bday entry node
 * 
 * @param object $source
 */
function ci_import_import_birthday_app_entry($source) {

  global $user, $language;
  $user = user_load(1);
  $node = ci_import_get_empty_node('birthday_app_entry');
  ci_import_defaults($node, $source);

  $node->body[$language->language][0] = ci_import_body_value($source);

  ci_import_files($node, $source, 'field_bday_app_entry_pic', 'field_bday_app_entry_pic');

  $node->field_bday_app_child_bday[LANGUAGE_NONE][0] = (array) $source->field_bday_app_child_bday[0];

  $node->field_bday_app_moderate[LANGUAGE_NONE][0]['value'] = (int) $source->moderate;

  $node->field_bday_app_age[LANGUAGE_NONE][0]['value']           = ci_import_field_value(
    $source->field_bday_app_age, 'value', 1
  );
  $node->field_bday_app_child_bday_md[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
    $source->field_bday_app_child_bday_md
  );
  $node->field_bday_app_child_name[LANGUAGE_NONE][0]['value']    = ci_import_field_value(
    $source->field_bday_app_child_name
  );
  $node->field_bday_app_fav_show[LANGUAGE_NONE][0]['value']      = ci_import_field_value(
    $source->field_bday_app_fav_show
  );
  $node->field_bday_app_grownup_email[LANGUAGE_NONE][0]['value'] = ci_import_field_value(
    $source->field_bday_app_grownup_email, 'email'
  );
  $node->field_bday_app_msg[LANGUAGE_NONE][0]['value']           = ci_import_field_value(
    $source->field_bday_app_msg
  );
  $node->field_bday_app_parent_name[LANGUAGE_NONE][0]['value']   = ci_import_field_value(
    $source->field_bday_app_parent_name
  );
  $node->field_bday_app_tv_opt_in[LANGUAGE_NONE][0]['value']     = ci_import_field_value(
    $source->field_bday_app_tv_opt_in, 'value', 0
  );

  node_save($node);

  $node->remote_nid = $source->nid;

  return $node;
}
