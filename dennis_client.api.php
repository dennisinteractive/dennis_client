<?php
/**
 * @file
 * Hooks provided by the Dennis Media module.
 */

/**
 * Set whether the node is sponsored.
 *
 * @param bool $sponsored
 *   Boolean whether the node is actually sponsored.
 * @param object $node
 *   The node object to act on.
 */
function hook_dennis_client_node_is_sponsored_alter(&$sponsored, $node) {
  // Set to TRUE if certain conditions are met...
  if ($node->type == 'foo') {
    $sponsored = TRUE;
  }
}
