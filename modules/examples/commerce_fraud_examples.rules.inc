<?php

/**
 * @file
 * Custom rules for the examples.
 */

/**
 * Implements hook_rules_condition_info().
 */
function commerce_fraud_examples_rules_condition_info() {
  return array(
    'commerce_fraud_examples_has_less_than_x_orders' => array(
      'label' => t('User has less than x orders'),
      'group' => t('Commerce Fraud Examples'),
      'parameter' => array(
        'user' => array(
          'label' => t('The user'),
          'type' => 'user',
        ),
        'number' => array(
          'label' => t('The number'),
          'type' => 'integer',
        ),
      ),
    ),
    'commerce_fraud_examples_last_order' => array(
      'label' => t('Last order is older than'),
      'group' => t('Commerce Fraud Examples'),
      'parameter' => array(
        'user' => array(
          'label' => t('The user'),
          'type' => 'user',
        ),
        'date' => array(
          'label' => t('Number of days'),
          'type' => 'integer',
        ),
      ),
    ),
    'commerce_fraud_examples_country_matches_ip' => array(
      'label' => t('The given country matches the IP address'),
      'group' => t('Commerce Fraud Examples'),
      'parameter' => array(
        'country' => array(
          'label' => t('The country'),
          'type' => 'addressfield',
        ),
      ),
    ),
  );
}

/**
 * Callback for the condition rule.
 */
function commerce_fraud_examples_has_less_than_x_orders(stdClass $user, $number) {
  $user_orders = commerce_order_load_multiple(array(), array('uid' => $user->uid));
  return count($user_orders) < $number;
}

/**
 * Callback for last order.
 */
function commerce_fraud_examples_last_order(stdClass $user, $days) {
  $user_orders = commerce_order_load_multiple(array(), array('uid' => $user->uid));
  if (count($user_orders) === 0) {
    return TRUE;
  }
  usort($user_orders, function($order, $other) {
    if ($order->changed === $other->changed) {
      return 0;
    }
    return ($order->changed > $other->changed) ? -1 : 1;
  });
  return $user_orders[0]->changed < commerce_fraud_examples_timestamp_from_days($days);
}

/**
 * Returns a timestamp matching x days before today.
 */
function commerce_fraud_examples_timestamp_from_days($days) {
  $date = new DateTimeImmutable();
  $date = $date->modify('- ' . $days . ' days');
  return $date->getTimestamp();
}

/**
 * Callback for the country matches ip condition.
 */
function commerce_fraud_examples_country_matches_ip($address) {
  $ip_address = ip_address();
  $guessed_country = ip2country_get_country($ip_address);
  if ($guessed_country === FALSE) {
    return TRUE;
  }

  return $address['country'] === $guessed_country;
}
