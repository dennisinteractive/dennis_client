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
 * Helper to migrate and delete field sponsored.
 */
function _dennis_client_migrate_field_sponsored() {
  /**
   * Migrate from existing sponsored fields.
   * - field_sponsored and delete field
   * - sponsored article_type and delete term.
   */
  $tables = array();

  // Get the tid for Sponsored.
  $partnerships_tid = NULL;
  $name = 'content_partnerships';
  $vocabulary = taxonomy_vocabulary_machine_name_load($name);
  $tree = taxonomy_get_tree($vocabulary->vid);
  foreach ($tree as $term) {
    if ($term->name == 'Sponsored') {
      $partnerships_tid = $term->tid;
      // Migrate legacy data.
      $tables['field_sponsored'] = array(
        'condition' => "legacy.field_sponsored_value != '0'",
      );
    }
  }

  // Get the tid of the sponsored article type term.
  $article_type_term = taxonomy_get_term_by_name('sponsored', 'article_type');
  $article_type_term = array_shift($article_type_term);
  if (isset($article_type_term)) {
    // Migrate from "Sponsored" article type if it exists.
    $article_type_tid = $article_type_term->tid;
    $tables['field_article_type'] = array(
      'condition' => "legacy.field_article_type_tid = $article_type_tid",
    );
  }

  if (isset($partnerships_tid) && !empty($tables)) {
    foreach ($tables as $source_field => $dest_config) {

      foreach (array('data', 'revision') as $type) {
        $dest_table = "field_" . $type . "_field_content_partnerships";
        $source_table = "field_" . $type . "_" . $source_field;

        // Skip if source table doesn't exist.
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
          '$partnerships_tid'
        FROM " . $source_table . " legacy
        LEFT JOIN field_" . $type . "_field_content_partnerships new ON new.entity_id = legacy.entity_id
        WHERE new.entity_id IS NULL";

        // Add any destination specific conditions.
        if (!empty($dest_config['condition'])) {
          $sql .= ' AND ' . $dest_config['condition'];
        }

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
  }

  // Delete field_sponsored if it exists.
  if (field_info_field('field_sponsored')) {
    field_delete_field('field_sponsored');
    field_purge_batch(1);
  }

  /**
   * Remove sponsored term from article type.
   */
  if (isset($article_type_tid)) {
    taxonomy_term_delete($article_type_tid);
  }
}
