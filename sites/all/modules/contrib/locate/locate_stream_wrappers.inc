<?php

/**
 * @file
 * Locate module stream wrapper extension.
 */

/**
 * Locate module (locate://) stream wrapper class
 *
 * Provides support for using the Drupal File API with locate module search
 * files.
 *
 * Extends DrupalPrivateStreamWrapper.
 */
class LocateStreamWrapper extends DrupalPrivateStreamWrapper {
  /**
   * Return the absolute path of the locate folder.
   */
  public function getDirectoryPath() {
    return variable_get(locate_search_root, NULL);
  }
}
