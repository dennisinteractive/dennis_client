<?php

/**
 * Expose the field_content_partnerships field value as a context condition.
 */
class context_condition_content_partnerships extends context_condition {
  function condition_values() {
    return array(1 => t('Enabled'));
  }

  function editor_form($context = NULL) {
    $form = parent::editor_form($context);
    $form[1]['#title'] = t('Content partnerships');
    $form['#weight'] = -10;
    return $form;
  }

  function execute($node) {
    foreach ($this->get_contexts() as $context) {
      if (current_path() == 'node/' . $node->nid) {
        if (dennis_client_show_content_partnership($node)) {
          $this->condition_met($context);
        }
      }
    }
  }
}
