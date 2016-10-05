<?php

/**
 * Create field field_content_partnerships if it doesn't exist.
 * @return string
 * @throws Exception
 * @throws FieldException
 */
function _dennis_client_create_field_content_partnerships() {
  if (!field_info_field('field_content_partnerships')) {
    // Create field_content_partnerships field.
    $field = array(
      'field_name' => 'field_content_partnerships',
      'type' => 'taxonomy_term_reference',
      'settings' => array(
        'allowed_values' => array(
          array(
            'vocabulary' => 'content_partnerships',
            'parent' => 0
          ),
        ),
      ),
    );
    field_create_field($field);
    drupal_set_message(t('Field !name has been created.', array('!name' => 'field_content_partnerships')));

    // Create field_content_partnerships instances.
    $content_types = array('article', 'review', 'gallery_adv');
    foreach ($content_types as $type) {
      if ($field_client_instance = field_info_instance('node', 'field_client', $type)) {
        $weight = $field_client_instance['widget']['weight'] + 0.2; // Get field_client weight.
        $instance = array(
          'field_name' => 'field_content_partnerships',
          'entity_type' => 'node',
          'label' => t('This content is part of a Content Partnership. How impartial is it?'),
          'description' => t('When content is part of a Content Partnership you need to define how impartial the content is. Think about the level of editorial independence there was when the content was created.'),
          'bundle' => $type,
          'required' => FALSE,
          'widget' => array(
            'type' => 'options_select',
            'weight' => $weight,
          ),
        );
        field_create_instance($instance);
        drupal_set_message(t('Field instance for !type has been created.', array('!type' => $type)));
      }
    }
  }
  else {
    drupal_set_message(t('Field !name already exists.', array('!name' => 'field_content_partnerships')));

  }
}
