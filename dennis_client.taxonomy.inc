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
  if ($sponsored_var_tid = variable_get('dennis_client_sponsored_tid')) {
    $sponsored_term = taxonomy_term_load($sponsored_var_tid);
    drupal_set_message(t('Found sponsored term %name (tid:%tid) using dennis_client_sponsored_tid variable.', array(
      '%name' => $sponsored_term->name,
      '%tid' => $sponsored_term->tid,
    )));
  }
  // Get the term by name if the variable isn't available.
  if (empty($sponsored_term)) {
    $sponsored_terms = taxonomy_get_term_by_name('sponsored', 'article_type');
    $sponsored_term = array_shift($sponsored_terms);
    if (!empty($sponsored_term)) {
      drupal_set_message(t('Found sponsored term %name (tid:%tid) by name.', array(
        '%name' => $sponsored_term->name,
        '%tid' => $sponsored_term->tid,
      )));
    }
  }
  // Add to tables to migrate from.
  if (!empty($sponsored_term)) {
    $sponsored_term_tid = $sponsored_term->tid;
    $sponsored_field_names = array(
      'article_type' => 'field_article_type',
      'category' => 'field_category_primary',
    );
    if (isset($sponsored_field_names[$sponsored_term->vocabulary_machine_name])) {
      $sponsored_field_name = $sponsored_field_names[$sponsored_term->vocabulary_machine_name];
      $tables[$sponsored_field_name] = array(
        'condition' => "legacy." . $sponsored_field_name . "_tid = " . $sponsored_term_tid,
      );
    }
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

    // Update taxonomy index table.
    $term_index_sql = "INSERT INTO taxonomy_index (
        nid,
        tid,
        sticky,
        created
      ) SELECT
        n.nid,
        cp.field_content_partnerships_tid,
        0,
        UNIX_TIMESTAMP(NOW())
      FROM field_data_field_content_partnerships cp
      LEFT JOIN node n ON n.nid = cp.entity_id AND cp.entity_type = 'node'
      WHERE n.status = 1";

    $term_index_result = db_query($term_index_sql);

    if ($term_index_result->rowCount() > 0) {
      drupal_set_message(t('Inserted %rows rows into taxonomy_index table.', array(
        '%rows' => $term_index_result->rowCount(),
      )));
    }
  }

  // Delete field_sponsored if it exists.
  if (field_info_field('field_sponsored')) {
    field_delete_field('field_sponsored');
  }
}
