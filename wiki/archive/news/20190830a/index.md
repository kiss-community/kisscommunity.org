# 30/08/2019: Removal of fakeroot

The `fakeroot` package is no longer used by the package manager. Instead
each package is built and archived with the ownership of whatever user
ran the package manager.

On installation of a package the files are then installed with the
ownership set to `root:root` achieving the same behavior in the end as
`fakeroot`.

`fakeroot` is a nasty hack and adds quite a lot of overhead to builds. I
am now able to rebuild GCC in only 10 minutes!

Steps for removal of `fakeroot`.

-   Update `kiss` to `0.10.0`.
-   Remove `fakeroot` (`kiss remove fakeroot`).
