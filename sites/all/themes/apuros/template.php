<?php
/**
 * @file
 * The primary PHP file for this theme.
 */

function apuros_preprocess(&$variables, $hook) {
  if (drupal_is_front_page()) {
    drupal_goto('/index.html');
  }
}
