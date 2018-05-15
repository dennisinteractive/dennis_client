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
    $form[1]['#title'] = t('Entity is sponsored');
    $form['#weight'] = -10;
    return $form;
  }

  function execute($entity, $type) {
    foreach ($this->get_contexts() as $context) {
      if (dennis_client_entity_is_page($entity, $type)) {
        if (dennis_client_entity_is_sponsored($entity, $type)) {
          $this->condition_met($context);
        }
      }
    }
  }
}
