<?php

/**
 * @file
 * Custom views handler definition.
 */

/**
 * Custom handler class.
 * @group views_field_handlers
 */
class views_handler_commerce_fraud_level extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  function query() {}

  /**
   * {@inheritdoc}
   */
  function render($values) {
    require_once __DIR__ . '/commerce_fraud.rules.conditions.inc';
    $order = commerce_order_load($values->order_id);
    if (commerce_fraud_is_whitelisted($order)) {
      return t('Whitelisted');
    }
    elseif (commerce_fraud_is_greylisted($order)) {
      return t('Greylisted');
    }
    elseif (commerce_fraud_is_blacklisted($order)) {
      return t('Blacklisted');
    }
  }

}
