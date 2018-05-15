<?php

/**
 * Check if the node is sponsored.
 */
class context_condition_is_sponsored extends context_condition {
  function condition_values() {
    return array(1 => t('True'));
  }

  function editor_form($context = NULL) {
    $form = parent::editor_form($context);
    $form[1]['#title'] = t('Node is sponsored');
    $form['#weight'] = -10;
    return $form;
  }

  function execute($node) {
    foreach ($this->get_contexts() as $context) {
      if (current_path() == 'node/' . $node->nid) {
        if (dennis_client_node_is_sponsored($node)) {
          $this->condition_met($context);
        }
      }
    }
  }
}
