<?php

/**
 * @file
 * Defines the actions rules.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_fraud_rules_action_info() {
  return array(
    'commerce_fraud_increase_fraud_count' => array(
      'label' => t('Increase the fraud count'),
      'group' => t('Commerce Fraud'),
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('The commerce order'),
        ),
        'counter' => array(
          'type' => 'integer',
          'label' => t('The counter'),
          'description' => t('Defines by how much the fraud count is increased.'),
          'optional' => TRUE,
          'default value' => 1,
        ),
      ),
      'access callback' => 'commerce_order_rules_access',
    ),
    'commerce_fraud_decrease_fraud_count' => array(
      'label' => t('Decrease the fraud count'),
      'group' => t('Commerce Fraud'),
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('The commerce order'),
        ),
        'counter' => array(
          'type' => 'integer',
          'label' => t('The counter'),
          'description' => t('Defines by how much the fraud count is increased.'),
          'optional' => TRUE,
          'default value' => 1,
        ),
      ),
      'access callback' => 'commerce_order_rules_access',
    ),
  );
}

/**
 * Implements the callback of the "Increase the fraud count" rule.
 *
 * @param stdClass $order
 *   The current commerce_order.
 * @param integer $counter
 *   By how much to increase the fraud count.
 */
function commerce_fraud_increase_fraud_count(stdClass $order, $counter) {
  if (!isset($order->data[COMMERCE_FRAUD_KEY])) {
    $order->data[COMMERCE_FRAUD_KEY] = 0;
  }
  $order->data[COMMERCE_FRAUD_KEY] = $order->data[COMMERCE_FRAUD_KEY] + $counter;
  rules_invoke_event('commerce_fraud_count_changed', $order);
}

/**
 * Implements the callback of the "Decrease the fraud count" rule.
 *
 * @param stdClass $order
 *   The current commerce_order.
 * @param integer $counter
 *   By how much to decrease the fraud count.
 */
function commerce_fraud_decrease_fraud_count(stdClass $order, $counter) {
  if (!isset($order->data[COMMERCE_FRAUD_KEY])) {
    $order->data[COMMERCE_FRAUD_KEY] = 0;
  }
  $order->data[COMMERCE_FRAUD_KEY] = $order->data[COMMERCE_FRAUD_KEY] - $counter;
  rules_invoke_event('commerce_fraud_count_changed', $order);
}
