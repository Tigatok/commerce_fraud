<?php

/**
 * @file
 * The admin settings form.
 */

/**
 * Administration form for commerce_fraud.
 */
function commerce_fraud_admin_settings() {
  $form = array();

  $form['commerce_fraud_whitelist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Whitelist caps'),
  );

  $form['commerce_fraud_whitelist']['commerce_fraud_whitelist_upper_cap'] = array(
    '#type' => 'textfield',
    '#title' => t('Whitelist upper cap'),
    '#description' => t('The upper cap (exclusive) for an order to be considered whitelisted.'),
    '#default_value' => variable_get('commerce_fraud_whitelist_upper_cap', 10),
    '#element_validate' => array('element_validate_integer'),
  );

  $form['commerce_fraud_greylist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Greylist caps'),
  );

  $form['commerce_fraud_greylist']['commerce_fraud_greylist_lower_cap'] = array(
    '#type' => 'textfield',
    '#title' => t('Greylist lower cap'),
    '#description' => t('The lower cap (inclusive) for an order to be considered greylisted.'),
    '#default_value' => variable_get('commerce_fraud_greylist_lower_cap', 10),
    '#element_validate' => array('element_validate_integer'),
  );

  $form['commerce_fraud_greylist']['commerce_fraud_greylist_upper_cap'] = array(
    '#type' => 'textfield',
    '#title' => t('Greylist upper cap'),
    '#description' => t('The upper cap (exclusive) for an order to be considered greylisted.'),
    '#default_value' => variable_get('commerce_fraud_greylist_upper_cap', 20),
    '#element_validate' => array('element_validate_integer'),
  );

  $form['commerce_fraud_blacklist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blacklist caps'),
  );

  $form['commerce_fraud_blacklist']['commerce_fraud_blacklist_lower_cap'] = array(
    '#type' => 'textfield',
    '#title' => t('Blacklist lower cap'),
    '#description' => t('The lower cap (inclusive) for an order to be considered blacklisted.'),
    '#default_value' => variable_get('commerce_fraud_blacklist_lower_cap', 20),
    '#element_validate' => array('element_validate_integer'),
  );

  return system_settings_form($form);
}