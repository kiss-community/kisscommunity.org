# 31/08/2019: python-setuptools now a part of python

Steps for removal of `python-setuptools`.

-   If `meson` is installed: `kiss remove meson`.
-   If `python-mako` is installed: `kiss remove python-mako`.
-   `kiss remove python-setuptools`.
-   `kiss build python`
-   `kiss install python`
-   `kiss update`
-   If `meson` was installed: `kiss build meson && kiss install meson`.
-   If `python-mako` was installed:
    `kiss build python-mako && kiss install python-mako`.
