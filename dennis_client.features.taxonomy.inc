<?php
/**
 * @file
 * dennis_client.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function dennis_client_taxonomy_default_vocabularies() {
  return array(
    'clients' => array(
      'name' => 'Clients',
      'machine_name' => 'clients',
      'description' => 'Names of advertising clients',
      'hierarchy' => '1',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(),
    ),
    'content_partnerships' => array(
      'name' => 'Content Partnerships',
      'machine_name' => 'content_partnerships',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(),
    ),
  );
}
