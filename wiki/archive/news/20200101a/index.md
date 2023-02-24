# 01/01/2020: Firefox privacy changes moved to firefox-privacy

The `vendor.js` and `policies.json` files KISS uses to harden and
prevent Firefox from phoning home are now opt-in and optional.

The changes have been moved to a new package called `firefox-privacy`.
Which can be installed alongside Firefox.

This change was made to avoid potential breakage of websites and to
enable users to make the choice for themselves in an easier way.
