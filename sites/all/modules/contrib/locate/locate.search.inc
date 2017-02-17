<?php

/**
 * @file
 * Search page callbacks for the locate module.
 */

/**
 * Search form page.
 */
function locate_search_form_page($path) {
  // Change page title if the setting exist.
  if (variable_get('locate_search_title', NULL) !== '') {
    drupal_set_title(variable_get('locate_search_title', NULL));
  }
  else {
    drupal_set_title(t('Locate search for: @path', array('@path' => $path)));
  }
  drupal_get_form('locate_search_form');
}

/**
 * Search form.
 */
function locate_search_form($form, $form_state, $path = NULL) {
  // Change page title if the setting exists.
  if (variable_get('locate_search_title', NULL) !== '') {
    drupal_set_title(variable_get('locate_search_title', NULL));
  }
  else {
    drupal_set_title(t('Locate search for: @path', array('@path' => $path)));
  }

  $form['search_query'] = array(
    '#type' => 'textfield',
    '#default_value' => check_plain($form_state['values']['search_query']),
    '#title' => t('Search for:'),
  );
  $form['search_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search for files',
    '#submit' => array('locate_search_form_submit'),
  );
  $form['ignore_case'] = array(
    '#type' => 'checkbox',
    '#title' => t('Ignore case?'),
  );
  $form['search_results'] = array(
    '#prefix' => '<div class="locate-search-results">',
    '#markup' => filter_xss($form_state['values']['search_results'], array('a', 'em', 'strong', 'cite', 'blockquote', 'ul', 'ol', 'li', 'dl', 'dt', 'dd', 'table', 'th', 'tr', 'td')),
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Submit handler for search.
 */
function locate_search_form_submit($form, &$form_state) {
  $search_query = $form_state['values']['search_query'];
  $ignore_case = $form_state['values']['ignore_case'];
  $form_state['values']['search_results'] = locate_search_results($search_query, $ignore_case);
  $form_state['rebuild'] = TRUE;
}

/**
 * Generate search results.
 *
 * @param string $search_query
 *   The search text entered on the search form.
 * @param bool $ignore_case
 *   A boolean indicating if the text case of the search query shoule be
 *   ignored.
 */
function locate_search_results($search_query, $ignore_case) {
  $header = array();
  $rows = array();

  $results = locate_call($search_query, $ignore_case);
  $count = 0;

  foreach ($results as $result) {
    $filename = str_replace(variable_get('locate_search_root', NULL) . '/', '', $result);
    $query = array('filename' => $filename, 'token' => drupal_get_token('download_locate_file' . $filename),
);
    $rows[] = array(array('data' => l($filename, 'locate/download', array('query' => $query))));
    ++$count;
  }

  $header[] = t('@count results found', array('@count' => $count));

  $table = theme('table', array('header' => $header, 'rows' => $rows));

  return $table;
}

/**
 * Call the locate command.
 *
 * @param string $search_query
 *   The search text entered on the search form.
 * @param bool $ignore_case
 *   A boolean indicating if the text case of the search query shoule be
 *   ignored.
 */
function locate_call($search_query, $ignore_case) {
  $results = array();

  if (variable_get('locate_search_root', NULL) !== '') {
    $search_query = variable_get('locate_search_root', NULL) . '/*' . $search_query . '*';
    $command = 'locate ' . ($ignore_case ? '-i ' : '') . escapeshellarg($search_query);
    exec($command, $results);
  }
  else {
    drupal_set_message(t('Please configure locate.'), 'error', TRUE);
  }

  return $results;
}
