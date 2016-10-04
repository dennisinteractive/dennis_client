<?php
/**
 * @file
 * dennis_client.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function dennis_client_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_taxonomy_term__clients';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'smart_paging' => array(
          'teaser' => array(
            'settings' => array(
              'smart_paging_settings_context' => 'content_type',
              'smart_paging_method' => 0,
              'smart_paging_pagebreak' => '<!--pagebreak-->',
              'smart_paging_character_count' => 3072,
              'smart_paging_word_count' => 512,
              'smart_paging_title_display_suffix' => 1,
              'smart_paging_title_suffix' => ': Page ',
            ),
            'weight' => '5',
            'visible' => FALSE,
          ),
          'content_partnership' => array(
            'settings' => array(
              'smart_paging_settings_context' => 'content_type',
              'smart_paging_method' => 0,
              'smart_paging_pagebreak' => '<!--pagebreak-->',
              'smart_paging_character_count' => 3072,
              'smart_paging_word_count' => 512,
              'smart_paging_title_display_suffix' => 1,
              'smart_paging_title_suffix' => ': Page ',
            ),
            'weight' => '6',
            'visible' => FALSE,
          ),
        ),
        'description' => array(
          'teaser' => array(
            'weight' => '4',
            'visible' => FALSE,
          ),
          'content_partnership' => array(
            'weight' => '5',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_taxonomy_term__clients'] = $strongarm;

  return $export;
}
