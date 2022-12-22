Published **24th Nov 2019** by [Dylan
Araps](https://github.com/dylanaraps).

# This week in KISS (#2)

This was a relatively quiet week. I took a much needed break and focused
solely on updating packages.

A big thank you to everyone using KISS!

## Index

-   [KISS is now 6 months old](#kiss-is-now-6-months-old)
-   [Patch status](#patch-status)
-   [Official Repositories](#official-repositories)
-   [Community](#community)

## KISS is now 6 months old

It has been a whole 6 months since I first started working on KISS!

    commit 0cda243d535f11e7c26b9182bc63e425deb5ba45
    Author: Dylan Araps <dylan.araps@gmail.com>
    Date:   Thu May 9 09:46:50 2019 +0300

        new package manager experiment

Assuming that I was the first user of KISS on hardware, Xorg, Firefox
and the distribution as a whole were in a "done" and usable state
early August!

    Filesystem created:  Mon Aug  5 16:32:37 2019

KISS was fully up and running in **only 3 months**! What a ride it has
been thus far. I can't wait to see what the future holds.

## Patch status

The `core` repository is now patch free!

The current numbers are as follows:

-   **core**: 0
-   **extra**: 19 (*Firefox makes up 8*)
-   **xorg**: 1

You can follow the progress here: [repo #109](https://github.com/kiss-community/repo/issues/109)

## Official Repositories

-   **Dylan Araps**:
    -   [`9b799b5`](https://github.com/kiss-community/repo/commit/9b799b5)
        libelf: remove patch
    -   [`0e44a45`](https://github.com/kiss-community/repo/commit/0e44a45)
        libelf: fix checksums
    -   [`485226a`](https://github.com/kiss-community/repo/commit/485226a)
        vim: bump to 8.1.2317
    -   [`5a7623c`](https://github.com/kiss-community/repo/commit/5a7623c)
        lvm2: Use only a single sed'
    -   [`4d1f9f1`](https://github.com/kiss-community/repo/commit/4d1f9f1)
        glib: remove useless quotes
    -   [`d6c59e1`](https://github.com/kiss-community/repo/commit/d6c59e1)
        sqlite: remove useless quotes
    -   [`d3fb1e8`](https://github.com/kiss-community/repo/commit/d3fb1e8)
        libffi: remove useless quotes
    -   [`6d8029c`](https://github.com/kiss-community/repo/commit/6d8029c)
        nodejs: remove useless flag
    -   [`33b3320`](https://github.com/kiss-community/repo/commit/33b3320)
        shared-mime-info: remove useless quotes
    -   [`4b808fc`](https://github.com/kiss-community/repo/commit/4b808fc)
        mandoc: remove useless quotes
    -   [`3dd0dff`](https://github.com/kiss-community/repo/commit/3dd0dff)
        libelf: remove useless quotes
    -   [`7ee4c90`](https://github.com/kiss-community/repo/commit/7ee4c90)
        lvm2: remove useless quotes
    -   [`b3eec64`](https://github.com/kiss-community/repo/commit/b3eec64)
        libxcb: remove useless quotes
    -   [`0cf8db6`](https://github.com/kiss-community/repo/commit/0cf8db6)
        xinit: remove useless quotes
    -   [`75a189f`](https://github.com/kiss-community/repo/commit/75a189f)
        cairo: remove useless quotes
    -   [`940110f`](https://github.com/kiss-community/repo/commit/940110f)
        gtk+3: clean up sed
    -   [`94ddf4e`](https://github.com/kiss-community/repo/commit/94ddf4e)
        ccache: bump to 3.7.6
    -   [`7de14f4`](https://github.com/kiss-community/repo/commit/7de14f4)
        vim: bump to 8.1.2318
    -   [`c60da28`](https://github.com/kiss-community/repo/commit/c60da28)
        linux-headers: bump to 5.3.11
    -   [`696d51d`](https://github.com/kiss-community/repo/commit/696d51d)
        xorg: Add note about multi-user systems
    -   [`ad01a1a`](https://github.com/kiss-community/repo/commit/ad01a1a)
        libinput: Add note about multi-user systems
    -   [`b2f656c`](https://github.com/kiss-community/repo/commit/b2f656c)
        vim: bump to 8.1.2321
    -   [`edc0cc5`](https://github.com/kiss-community/repo/commit/edc0cc5)
        firefox (beta): bump to 71.0b11
    -   [`56d51a4`](https://github.com/kiss-community/repo/commit/56d51a4)
        alsa-lib: bump to 1.2.1.1
    -   [`f2b4ced`](https://github.com/kiss-community/repo/commit/f2b4ced)
        cbindgen: bump to 0.10.0
    -   [`d7bde80`](https://github.com/kiss-community/repo/commit/d7bde80)
        glib: bump to 2.62.3
    -   [`0cb8726`](https://github.com/kiss-community/repo/commit/0cb8726)
        vim: bump to 8.1.2323
    -   [`77b6a5b`](https://github.com/kiss-community/repo/commit/77b6a5b)
        mesa: bump to 19.2.5
    -   [`4b5693f`](https://github.com/kiss-community/repo/commit/4b5693f)
        5.3.12
    -   [`2d69187`](https://github.com/kiss-community/repo/commit/2d69187)
        mesa: bump to 19.2.6
    -   [`f813fec`](https://github.com/kiss-community/repo/commit/f813fec)
        vim: bump to 8.1.2333
    -   [`3b9d975`](https://github.com/kiss-community/repo/commit/3b9d975)
        nodejs: bump to 13.2.0
    -   [`3ed362c`](https://github.com/kiss-community/repo/commit/3ed362c)
        firefox (beta): bump to 71.0b12
    -   [`16b0819`](https://github.com/kiss-community/repo/commit/16b0819)
        vim: bump to 8.1.2337
    -   [`535f4f0`](https://github.com/kiss-community/repo/commit/535f4f0)
        xorg-server: bump to 1.20.6
    -   [`6f84c9c`](https://github.com/kiss-community/repo/commit/6f84c9c)
        libffi: bump to 3.3
    -   [`d0aabe4`](https://github.com/kiss-community/repo/commit/d0aabe4)
        vim: bump to 8.1.2338
    -   [`62a78d0`](https://github.com/kiss-community/repo/commit/62a78d0)
        libffi: revert to 3.2.1
    -   [`6519e2d`](https://github.com/kiss-community/repo/commit/6519e2d)
        libffi: bump to 3.3
    -   [`df156c6`](https://github.com/kiss-community/repo/commit/df156c6)
        dhcpcd: use better mirror
    -   [`1c7ab1a`](https://github.com/kiss-community/repo/commit/1c7ab1a)
        libffi: Add rationale for symlink
    -   [`e6abad4`](https://github.com/kiss-community/repo/commit/e6abad4)
        imlib2: move to community

## Community

-   **Dylan Araps**:
    -   [`943664b`](https://github.com/kiss-community/community/commit/943664b)
        tig: bump to 2.5.0
    -   [`5758cf9`](https://github.com/kiss-community/community/commit/5758cf9)
        pandoc-bin: bump to 2.8
    -   [`19cf38d`](https://github.com/kiss-community/community/commit/19cf38d)
        imlib2: add to community and bump to 1.6.0

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
