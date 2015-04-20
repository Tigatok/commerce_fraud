<?php

/**
 * @file
 * Defines the conditions rules.
 */

/**
 * Implements hook_rules_condition_info().
 */
function commerce_fraud_rules_condition_info() {
  return array(
    'commerce_fraud_is_whitelisted' => array(
      'label' => t('Order is whitelisted'),
      'group' => t('Commerce Fraud'),
      'parameter' => array(
        'commerce_order' => array(
          'label' => t('The commerce order'),
          'type' => 'commerce_order',
        ),
      ),
    ),
    'commerce_fraud_is_greylisted' => array(
      'label' => t('Order is greylisted'),
      'group' => t('Commerce Fraud'),
      'parameter' => array(
        'commerce_order' => array(
          'label' => t('The commerce order'),
          'type' => 'commerce_order',
        ),
      ),
    ),
    'commerce_fraud_is_blacklisted' => array(
      'label' => t('Order is blacklisted'),
      'group' => t('Commerce Fraud'),
      'parameter' => array(
        'commerce_order' => array(
          'label' => t('The commerce order'),
          'type' => 'commerce_order',
        ),
      ),
    ),
  );
}

/**
 * Whitelist condition callback.
 */
function commerce_fraud_is_whitelisted(stdClass $order) {
  if (!isset($order->data[COMMERCE_FRAUD_KEY])) {
    return TRUE;
  }
  $whitelist_cap = variable_get('commerce_fraud_whitelist_upper_cap', 10);
  return $order->data[COMMERCE_FRAUD_KEY] < $whitelist_cap;
}

/**
 * Greylist condition callback.
 */
function commerce_fraud_is_greylisted(stdClass $order) {
  if (!isset($order->data[COMMERCE_FRAUD_KEY])) {
    return FALSE;
  }
  $greylist_lower_cap = variable_get('commerce_fraud_greylist_lower_cap', 10);
  $greylist_upper_cap = variable_get('commerce_fraud_greylist_upper_cap', 20);
  $count = $order->data[COMMERCE_FRAUD_KEY];
  return $count >= $greylist_lower_cap && $count < $greylist_upper_cap;
}

/**
 * Blacklist condition callback.
 */
function commerce_fraud_is_blacklisted(stdClass $order) {
  if (!isset($order->data[COMMERCE_FRAUD_KEY])) {
    return FALSE;
  }
  $blacklist_cap = variable_get('commerce_fraud_blacklist_lower_cap', 20);
  return $order->data[COMMERCE_FRAUD_KEY] >= $blacklist_cap;
}
