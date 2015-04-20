<?php

/**
 * @file
 * Defines the events rules.
 */

/**
 * Implements hook_rules_event_info().
 */
function commerce_fraud_rules_event_info() {
  return array(
    'commerce_fraud_count_changed' => array(
      'label' => t('Fraud count changed'),
      'group' => t('Commerce Fraud'),
      'variables' => array(
        'commerce_order' => array(
          'label' => t('The commerce order'),
          'type' => 'commerce_order',
        ),
      ),
    ),
  );
}
