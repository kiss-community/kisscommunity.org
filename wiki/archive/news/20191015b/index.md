# 15/10/2019: New python release (3.8.0), manual intervention needed

A new **major** version of `python` has been released which requires a
rebuild of the following packages.

-   python-mako
-   meson

Steps:

-   `kiss update` (*update Python first*).
-   `kiss b python-mako meson`
-   Press **Return** afterwards to install the rebuilt packages.

Note:

-   I am looking into automating this, stay tuned.
