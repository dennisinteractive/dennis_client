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
        // Initialise variable to display the ad.
        $show = TRUE;

        // Check if the enable checkbox has been selected in the client term.
        if (isset($node->field_client[LANGUAGE_NONE][0]['tid'])) {
          $term = taxonomy_term_load($node->field_client[LANGUAGE_NONE][0]['tid']);
          if (
            isset($term->field_enable_branding_on_nodes[LANGUAGE_NONE][0]['value']) &&
            $term->field_enable_branding_on_nodes[LANGUAGE_NONE][0]['value'] == 0
          ) {
            $show = FALSE;
          }
          else {
            // Check if the exclude checkbox has been selected in the node.
            if (
              isset($node->field_exclude_client_branding[LANGUAGE_NONE][0]['value']) &&
              $node->field_exclude_client_branding[LANGUAGE_NONE][0]['value'] == 1
            ) {
              $show = FALSE;
            }
          }
        }

        if ($show) {
          $this->condition_met($context);
        }
      }
    }
  }
}
