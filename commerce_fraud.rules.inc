<?php

/**
 * @file
 * commerce_fraud custom rules.
 */

define('COMMERCE_FRAUD_KEY', 'commerce_fraud_count');

require_once(__DIR__ . '/includes/commerce_fraud.rules.events.inc');
require_once(__DIR__ . '/includes/commerce_fraud.rules.conditions.inc');
require_once(__DIR__ . '/includes/commerce_fraud.rules.actions.inc');
