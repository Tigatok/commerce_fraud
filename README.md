# commerce_fraud

This module provides a framework to detect potentially fraudulous
orders and act on this.

This module provides:

- 1 rules event: "Fraud count changed"
- 3 rules conditions:
    - Order is whitelisted
    - Order is greylisted
    - Order is blacklisted
- 3 rules actions:
    - Increase the fraud count
    - Decrease the fraud count
    - Reset the fraud count

The rules actions will set a counter on the provided
`commerce_order`. This counter is an integer that the "Reset the fraud
count" action sets back to 0. The "Increase the fraud count" and
"Decrease the fraud count" actions will increase or decrease this
fraud count, by default by 1. (But this is customizable.)

The "Fraud count changed" event is fired every time one of the actions
is called.

The limits used by the 3 conditions are configurable in
/admin/commerce/config/fraud. By default, they are:

- An order is whitelisted if the fraud count is <10
- An order is greylisted if the fraud count is 10 <= x < 20
- An order is blacklisted if the fraud count is >=20

The `commerce_fraud_examples` module gives some examples on what kind
of rules can be used.

Sponsored by [Skilld.fr][0] and developed by [Commerce Guys][1].


  [0]: http://www.skilld.fr
  [1]: https://commerceguys.com
