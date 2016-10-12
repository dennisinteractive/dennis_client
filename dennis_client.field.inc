<?php
/**
 * @file
 * dennis_client.field.inc
 *
 * NB: this is NOT used by features.
 * These functions get called by dennis_client_get_field_definition() and
 * dennis_client_get_field_instance_definition(). The returned arrays are copied
 * from a field export.
 */

/**
 * Definition of field_client.
 */
function dennis_client_field_client_config() {
  return array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_client',
    'foreign keys' => array(
      'tid' => array(
        'columns' => array(
          'tid' => 'tid',
        ),
        'table' => 'taxonomy_term_data',
      ),
    ),
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => '1',
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'clients',
          'parent' => '0',
        ),
      ),
    ),
    'translatable' => '0',
    'type' => 'taxonomy_term_reference',
  );
}

/**
 * The default to be used for instances of field_client.
 */
function dennis_client_field_client_instance($bundle) {
  return array(
    'bundle' => $bundle,
    'default_value' => NULL,
    'deleted' => '0',
    'description' => 'Changes the targeting of adverts to the selected client.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_client',
    'label' => 'Client',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => '2',
    ),
  );
}

/**
 * Definition of field_content_partnerships.
 */
function dennis_client_field_content_partnerships_config() {
  return array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_content_partnerships',
    'foreign keys' => array(
      'tid' => array(
        'columns' => array(
          'tid' => 'tid',
        ),
        'table' => 'taxonomy_term_data',
      ),
    ),
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => '1',
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'content_partnerships',
          'parent' => '0',
        ),
      ),
    ),
    'translatable' => '0',
    'type' => 'taxonomy_term_reference',
  );
}

/**
 * The default to be used for instances of field_content_partnerships.
 */
function dennis_client_field_content_partnerships_instance($bundle) {
  return array(
    'bundle' => $bundle,
    'default_value' => NULL,
    'deleted' => '0',
    'description' => 'When content is part of a Content Partnership you need to define how impartial the content is. Think about the level of editorial independence there was when the content was created.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_content_partnerships',
    'label' => 'This content is part of a Content Partnership. How impartial is it?',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => '3',
    ),
  );
}

/**
 * Definition of field_exclude_client_branding.
 */
function dennis_client_field_exclude_client_branding_config() {
  return array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_exclude_client_branding',
    'field_permissions' => array(
      'type' => '0',
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => '0',
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => '0',
    'type' => 'list_boolean',
  );
}

/**
 * The default to be used for instances of field_exclude_client_branding.
 */
function dennis_client_field_exclude_client_branding_instance($bundle) {
  return array(
    'bundle' => $bundle,
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_exclude_client_branding',
    'label' => 'Exclude client branding on this node',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => '4',
    ),
  );
}
