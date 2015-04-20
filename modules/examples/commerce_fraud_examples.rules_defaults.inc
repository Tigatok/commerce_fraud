<?php

/**
 * @file
 * Default rules of the example rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_fraud_examples_default_rules_configuration() {
  $items = array();
  $items['rules_automatically_accept_if_whitelisted'] = entity_import('rules_config', '{ "rules_automatically_accept_if_whitelisted" : {
      "LABEL" : "Automatically accept if whitelisted",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "commerce_fraud", "rules", "commerce_checkout" ],
      "ON" : { "commerce_checkout_complete" : [] },
      "IF" : [
        { "commerce_fraud_is_whitelisted" : { "commerce_order" : [ "commerce_order" ] } }
      ],
      "DO" : [
        { "component_rules_commerce_order_status_completed" : { "order" : [ "commerce-order" ] } }
      ]
    }
  }');
  $items['rules_automatically_decline_if_blacklisted'] = entity_import('rules_config', '{ "rules_automatically_decline_if_blacklisted" : {
      "LABEL" : "Automatically decline if blacklisted",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "commerce_fraud", "rules", "commerce_checkout" ],
      "ON" : { "commerce_checkout_complete" : [] },
      "IF" : [
        { "commerce_fraud_is_blacklisted" : { "commerce_order" : [ "commerce_order" ] } }
      ],
      "DO" : [
        { "component_rules_commerce_order_status_canceled" : { "order" : [ "commerce-order" ] } }
      ]
    }
  }');
  $items['rules_decrease_fraud_count_for_female'] = entity_import('rules_config', '{ "rules_decrease_fraud_count_for_female" : {
      "LABEL" : "Decrease fraud count for female",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "rules", "commerce_fraud", "entity" ],
      "ON" : { "commerce_customer_profile_presave" : [] },
      "IF" : [
        { "entity_has_field" : {
            "entity" : [ "commerce-customer-profile" ],
            "field" : "field_gender"
          }
        },
        { "data_is" : {
            "data" : [ "commerce-customer-profile:field-gender" ],
            "value" : "Female"
          }
        }
      ],
      "DO" : [
        { "commerce_fraud_decrease_fraud_count" : { "commerce_order" : [ "site:current-cart-order" ] } }
      ]
    }
  }');
  $items['rules_increase_fraud_count_for_male'] = entity_import('rules_config', '{ "rules_increase_fraud_count_for_male" : {
      "LABEL" : "Increase fraud count for male",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "rules", "commerce_fraud", "entity" ],
      "ON" : { "commerce_customer_profile_presave" : [] },
      "IF" : [
        { "entity_has_field" : {
            "entity" : [ "commerce-customer-profile" ],
            "field" : "field_gender"
          }
        },
        { "data_is" : {
            "data" : [ "commerce-customer-profile:field-gender" ],
            "value" : "Male"
          }
        }
      ],
      "DO" : [
        { "commerce_fraud_increase_fraud_count" : { "commerce_order" : [ "site:current-cart-order" ] } }
      ]
    }
  }');
  return $items;
}
