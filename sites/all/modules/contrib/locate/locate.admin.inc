<?php

/**
 * @file
 * Admin page callbacks for the locate module.
 */

/**
 * Form constructor for the locate settings form.
 */
function locate_settings($form, $form_state) {
  $form['locate_search_drupal_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Drupal search path'),
    '#description' => t('Relative path for the search page. Do not include a trailing slash.'),
    '#default_value' => variable_get('locate_search_drupal_path', NULL),
  );
  $form['locate_search_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Search title'),
    '#description' => t('Friendly name of the search which is used for the search page title.'),
    '#default_value' => variable_get('locate_search_title', NULL),
  );
  $form['locate_search_root'] = array(
    '#type' => 'textfield',
    '#title' => t('Search root'),
    '#description' => t('Full path of the folder to be searched.'),
    '#default_value' => variable_get('locate_search_root', NULL),
  );

  return system_settings_form($form);
}
