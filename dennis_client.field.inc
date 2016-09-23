<?php
/**
 * @file
 * dennis_client.field.inc
 *
 * NB: this is NOT used by features.
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
