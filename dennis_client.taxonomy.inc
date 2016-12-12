<?php
/**
 * @file Holds helper functions.
 *
 * NB: this is NOT used by features.
 */

/**
 * Helper to create terms.
 */
function _dennis_client_create_terms() {
  features_revert(
    array(
      'dennis_client' => array('taxonomy', 'field', 'variable'),
    )
  );
  $vocabulary = taxonomy_vocabulary_machine_name_load('content_partnerships');

  if ($vocabulary->vid) {
    $terms = array(
      'Sponsored' => 1,
      'Advertisement Feature' => 2,
    );

    foreach ($terms as $name => $id) {
      $term = new stdClass();
      $term->name = $name;
      $term->vid = $vocabulary->vid;
      $term->weight = $id - 1;
      $term->field_ga_custom_dimension[LANGUAGE_NONE][0]['value'] = $id;
      taxonomy_term_save($term);
    }
  }
}

/**
 * Helper to configure the taxonomy display.
 */
function _dennis_client_set_taxonomy_display() {
  taxonomy_display_save_taxonomy_display('clients', array(
    'term_display_plugin' => 'TaxonomyDisplayTermDisplayHandlerCore',
    'term_display_options' => NULL,
    'associated_display_plugin' => 'TaxonomyDisplayAssociatedDisplayHandlerViews',
    'associated_display_options' => array(
      'view' => 'category_hub',
      'display' => 'default',
    ),
    'breadcrumb_display_plugin' => 'TaxonomyDisplayBreadcrumbDisplayHandlerCore',
    'add_feed' => 1,
  ));
}

/**
 * Helper to migrate  field sponsored.
 */
function _dennis_client_migrate_field_sponsored() {
  /**
   * Migrate field_sponsored.
   */
  // Get the tid for Sponsored.
  $tid = NULL;
  $name = 'content_partnerships';
  $vocabulary = taxonomy_vocabulary_machine_name_load($name);
  $tree = taxonomy_get_tree($vocabulary->vid);
  foreach ($tree as $term) {
    if ($term->name == 'Sponsored') {
      $tid = $term->tid;
    }
  }
  
  if ($tid) {
    // Migrate legacy data.
    $tables = array(
      'field_data_field_sponsored' => 'field_data_field_content_partnerships',
      'field_revision_field_sponsored' => 'field_revision_field_content_partnerships',
    );
    foreach ($tables as $source_table => $dest_table) {
      if (!db_table_exists($source_table)) {
        continue;
      }

      $sql = "INSERT INTO " . $dest_table . " (
        entity_type,
        bundle,
        deleted,
        entity_id,
        revision_id,
        language,
        delta,
        field_content_partnerships_tid
      ) SELECT
        legacy.entity_type,
        legacy.bundle,
        legacy.deleted,
        legacy.entity_id,
        legacy.revision_id,
        legacy.language,
        legacy.delta,
        '$tid'
      FROM " . $source_table . " legacy
      LEFT JOIN " . $dest_table . " new ON new.entity_id = legacy.entity_id
      WHERE new.entity_id IS NULL
      AND legacy.field_sponsored_value != '0';";

      $result = db_query($sql);

      if ($result->rowCount() > 0) {
        drupal_set_message(
          t('Copied %rows from %source to %dest.',
            array(
              '%rows' => $result->rowCount(),
              '%source' => $source_table,
              '%dest' => $dest_table,
            )
          )
        );
      }
    }
  }

  /**
   * Remove sponsored term from article type.
   */
  $term = taxonomy_get_term_by_name('sponsored', 'article_type');
  $term = array_shift($term);
  if (isset($term)) {
    taxonomy_term_delete($term->tid);
  }
}
