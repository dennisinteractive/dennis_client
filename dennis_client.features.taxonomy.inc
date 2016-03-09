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
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
