# 31/08/2019: Removal of ca-certificates

KISS now uses the certificates bundled with `libressl`.

Steps for removal of `ca-certificates`.

-   `kiss build libressl`
-   `kiss remove ca-certificates`
-   `rm -rf /etc/ssl`
-   `kiss install libressl`

**Update**: A script is also provided in `/etc/ssl` to update the
certificate bundle independently of the package manager.
