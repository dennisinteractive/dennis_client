<?php
/**
 * @file
 * dennis_client.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dennis_client_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
