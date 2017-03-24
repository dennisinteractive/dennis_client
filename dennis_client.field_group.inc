<?php
/**
 * @file
 * dennis_client.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function dennis_client_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content_partnerships|taxonomy_term|clients|form';
  $field_group->group_name = 'group_content_partnerships';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'clients';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content partnerships',
    'weight' => '8',
    'children' => array(
      0 => 'field_intro_text',
      1 => 'field_company_name',
      2 => 'field_client_logo',
      3 => 'field_client_link',
      4 => 'field_strap_line',
      5 => 'field_enable_branding_on_nodes',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content-partnerships field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_content_partnerships|taxonomy_term|clients|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content partnerships');

  return $field_groups;
}
