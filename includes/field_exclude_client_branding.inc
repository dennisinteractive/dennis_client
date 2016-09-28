<?php

/**
 * Create field_exclude_client_branding programmatically if it doesn't exist.
 * @return string
 * @throws Exception
 * @throws FieldException
 */
function _dennis_client_create_field_exclude_client_branding() {
  if (!field_info_field('field_exclude_client_branding')) {
    // Create field_exclude_client_branding field.
    $field = array(
      'field_name' => 'field_exclude_client_branding',
      'type' => 'list_boolean',
      'settings' => array(
        'allowed_values' => array(
          array(
            '0' => '',
            '1' => '',
          ),
        ),
      ),
    );
    field_create_field($field);

    // Create field_exclude_client_branding instances.
    $content_types = array('article', 'review', 'gallery_adv');
    foreach ($content_types as $type) {
      $field_client_instance = field_info_instance('node', 'field_client', $type);
      $weight = $field_client_instance['widget']['weight'] + 0.2; // Get field_client weight.
      $instance = array(
        'field_name' => 'field_exclude_client_branding',
        'entity_type' => 'node',
        'label' => t('Exclude client branding on this node'),
        'description' => '',
        'bundle' => $type,
        'required' => false,
        'widget' => array(
          'active' => 1,
          'type' => 'options_onoff',
          'weight' => $weight,
          'settings' => array(
           'display_label' => 1,
          ),
        ),
        'settings' => array(
          'display_label' => 1,
        ),
      );
      field_create_instance($instance);
    }
    $message = 'Field "field_exclude_client_branding" created.';
  }
  else {
    $message = 'The field "field_exclude_client_branding" already exists.';
  }
  return $message;
}