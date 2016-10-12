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
 * Definition of field_sponsored.
 */
function dennis_client_field_sponsored_config() {
  return array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_sponsored',
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
        0 => '0',
        1 => '1',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => '0',
    'type' => 'list_boolean',
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
 * The default to be used for instances of field_sponsored.
 */
function dennis_client_field_sponsored_instance($bundle) {
  return array(
    'bundle' => $bundle,
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => '0',
    'description' => 'Check this if the node is to be sponsored by the client. This usually means changing the page layout according to the sponsors request.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_sponsored',
    'label' => 'Sponsored',
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
      'weight' => '11',
    ),
  );
}
