<?php
/**
 * @file
 * dennis_client.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function dennis_client_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content_partnerships';
  $context->description = 'Show the content partnerships block in the content top region.';
  $context->tag = 'Client';
  $context->conditions = array(
    'context_condition_content_partnerships' => array(
      'values' => array(
        1 => 1,
      ),
    ),
    'node' => array(
      'values' => array(
        'article' => 'article',
        'gallery_adv' => 'gallery_adv',
        'review' => 'review',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'dennis_client-content_partnerships' => array(
          'module' => 'dennis_client',
          'delta' => 'content_partnerships',
          'region' => 'content_top',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Client');
  t('Show the content partnerships block in the content top region.');
  $export['content_partnerships'] = $context;

  return $export;
}
