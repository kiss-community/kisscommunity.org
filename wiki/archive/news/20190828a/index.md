# 28/08/2019: Removal of atk-bridge-fake

This package was used to patch out the `dbus` requirement from GTK2/3, I
have found a simpler way of accomplishing the same goal without the need
for a fake library!

Steps for removal of `atk-bridge-fake`.

-   Update `gtk+2` and `gtk+3`.
-   Remove `atk-bridge-fake` (`kiss remove atk-bridge-fake`).
