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
  $items['rules_decrease_fraud_count_for_women'] = entity_import('rules_config', '{ "rules_decrease_fraud_count_for_women" : {
      "LABEL" : "Decrease fraud count for women",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "rules", "commerce_fraud", "entity" ],
      "ON" : { "commerce_customer_profile_presave" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "commerce-customer-profile" ], "field" : "field_gender" } },
        { "data_is" : { "data" : [ "commerce-customer-profile:field-gender" ], "value" : "73" } }
      ],
      "DO" : [
        { "commerce_fraud_decrease_fraud_count" : { "commerce_order" : [ "site:current-cart-order" ] } }
      ]
    }
  }');
  $items['rules_increase_fraud_count_for_men'] = entity_import('rules_config', '{ "rules_increase_fraud_count_for_men" : {
      "LABEL" : "Increase fraud count for men",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "rules", "commerce_fraud", "entity" ],
      "ON" : { "commerce_customer_profile_presave" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "commerce-customer-profile" ], "field" : "field_gender" } },
        { "data_is" : { "data" : [ "commerce-customer-profile:field-gender" ], "value" : "72" } }
      ],
      "DO" : [
        { "commerce_fraud_increase_fraud_count" : { "commerce_order" : [ "site:current-cart-order" ] } }
      ]
    }
  }');
  $items['rules_decrease_fraud_count_if_order_less_than_250'] = entity_import('rules_decrease_fraud_count_if_order_less_than_250', '{ "rules_decrease_fraud_count_if_order_less_than_250" : {
      "LABEL" : "Decrease fraud count if order less than 250",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "rules", "commerce_fraud", "entity" ],
      "ON" : { "commerce_order_presave" : [] },
      "IF" : [
        { "data_is" : {
            "data" : [ "commerce-order:commerce-order-total:amount" ],
            "op" : "\u003C",
            "value" : "250"
          }
        }
      ],
      "DO" : [
        { "commerce_fraud_decrease_fraud_count" : { "commerce_order" : [ "commerce_order" ], "counter" : "10" } }
      ]
    }
  }');
  $items['rules_decrease_fraud_count_if_last_order_2_months_or_1st_order'] = entity_import('rules_decrease_fraud_count_if_last_order_2_months_or_1st_order', '{ "rules_decrease_fraud_count_if_last_order_2_months_or_1st_order" : {
      "LABEL" : "Decrease fraud count if last order \u003E 2 months or 1st order",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "commerce_fraud_examples", "commerce_fraud", "entity" ],
      "ON" : { "commerce_order_presave" : [] },
      "IF" : [
        { "OR" : [
            { "commerce_fraud_examples_has_less_than_x_orders" : { "user" : [ "commerce-order:owner" ], "number" : "1" } },
            { "commerce_fraud_examples_last_order" : { "user" : [ "commerce-order:owner" ], "date" : "60" } }
          ]
        }
      ],
      "DO" : [
        { "commerce_fraud_decrease_fraud_count" : { "commerce_order" : [ "commerce_order" ], "counter" : "10" } }
      ]
    }
  }');
  $items['rules_increase_fraud_count_if_badword_in_address'] = entity_import('rules_increase_fraud_count_if_badword_in_address', '{ "rules_increase_fraud_count_if_badword_in_address" : {
      "LABEL" : "Increase fraud count if badword in address",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "commerce_fraud" ],
      "REQUIRES" : [ "rules", "commerce_fraud", "entity" ],
      "ON" : { "commerce_customer_profile_presave" : [] },
      "IF" : [
        { "entity_has_field" : {
            "entity" : [ "commerce-customer-profile" ],
            "field" : "commerce_customer_address"
          }
        },
        { "text_matches" : {
            "text" : [ "commerce-customer-profile:commerce-customer-address:thoroughfare" ],
            "match" : "hopital|hotel|clinique",
            "operation" : "regex"
          }
        }
      ],
      "DO" : [
        { "commerce_fraud_increase_fraud_count" : { "commerce_order" : [ "site:current-cart-order" ], "counter" : "10" } }
      ]
    }
  }');
  return $items;
}
