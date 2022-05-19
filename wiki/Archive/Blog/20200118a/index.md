# 18/01/2020: This week in KISS (#7)

Lots of interesting changes this week. A big thank you to everyone
involved.

If you have any questions about this post, feel free to join the IRC
channel `#kisslinux` @ freenode.net.

## Index

-   [Git support in the package manager](#git-support-in-the-package-manager)
-   [GNU Grep support in the package manager](#gnu-grep-support-in-the-package-manager)
-   [Firefox ESR](#firefox-esr)
-   [Falkon (and qtwebengine)](#falkon-and-qtwebengine)
-   [webkit2gtk](#webkit2gtk)
-   [KISS ported to aarch64](#kiss-ported-to-aarch64)
-   [Official Repositories](#official-repositories)
-   [Community](#community)

## Git support in the package manager

The package manager now supports Git repositories as sources in the
package system. The syntax is rather simple and the pull request can be
seen here: <https://github.com/kiss-community/kiss/pull/85/files>

Source format:

    # git+URL
    git+https://github.com/dylanaraps/eiwd

    # git+URL#hash
    git+https://github.com/dylanaraps/eiwd#4a2d30bd1b053a9f1e4373d17c2ae6f3ccbc4148

Version:

    # Simply use git.
    git

    # Or use a hash if supplied to the source.
    4a2d30bd1b053a9f1e4373d17c2ae6f3ccbc4148

## GNU Grep support in the package manager

GNU Grep support has been added to the package manager as a simple means
of achieving performance gains.

Those who value performance over POSIX correctness now have the choice
to install `gnugrep` to speed up various operations in the package
manager.

GNU Grep is super quick compared to other Grep implementations. See this
post by the original author of GNU Grep:
<https://lists.freebsd.org/pipermail/freebsd-current/2010-August/019310.html>

## Firefox ESR

KISS now tracks Firefox ESR and in addition, binaries are now available
to users by installing the package `firefox-bin`.

The swap was made as Firefox builds (and updates) are monthly,
unpredictable and time consuming both for users and myself.

Rust is also another reason for the change as Firefox releases track the
latest Rust releases and they're a hard two packages to juggle.

Users now have the choice between building Firefox and Rust or
installing a binary provided by yours truly.

## Falkon (and qtwebengine)

The Falkon web browser and qtwebengine are now available in the
repositories as an alternative to Firefox.

I spent the last few days getting grabbing, porting and writing patches
to enable all of this to work on Musl.

And yes, KISS uses the latest Qt and Qtwebengine!

I have personally swapped to Falkon and everything works flawlessly. My
system is now free of GTK, glib and other GNOME software!

A big thank you to those in the IRC providing advice and a big thank you
to [meta-qt5](https://github.com/meta-qt5/meta-qt5) for a bulk of the
patches.

## webkit2gtk

Webkit2GTK is now available in the repositories thanks to the work of
the [Carbs Linux](https://carbslinux.org/) developer Cem Keylan and
myself.

Carbs Linux is a distribution based on KISS which aims to take a more
Suckless approach as an operating system.

This enables further browser choice by allowing the use of browsers like
luakit, suckless surf and others.

## KISS ported to aarch64

KISS has been ported to aarch64 by
[jedavies-dev](https://github.com/jedavies-dev) who is also the creator
and maintainer of the ppc64le port.

More information: <https://github.com/jedavies-dev/kiss-aarch64>

## Official Repositories

-   **Dylan Araps** :
    -   [`29fe61c`](https://github.com/kiss-community/repo/commit/29fe61c)
        libwebp: Fix source
    -   [`624c4fb`](https://github.com/kiss-community/repo/commit/624c4fb)
        curl: link statically
    -   [`10ee015`](https://github.com/kiss-community/repo/commit/10ee015)
        baseinit: bump to 0.2.0
    -   [`d9f135f`](https://github.com/kiss-community/repo/commit/d9f135f)
        eiwd: Fix make depends
    -   [`290b0d8`](https://github.com/kiss-community/repo/commit/290b0d8)
        gtk+3: Remove 4MB of stuff
    -   [`ae87866`](https://github.com/kiss-community/repo/commit/ae87866)
        liberation-fonts: new package at 2.00.5
    -   [`c17c092`](https://github.com/kiss-community/repo/commit/c17c092)
        xorg-server: Remove xinit dependency
    -   [`ca1baa3`](https://github.com/kiss-community/repo/commit/ca1baa3)
        busybox: Remove acpid
    -   [`0f7cba2`](https://github.com/kiss-community/repo/commit/0f7cba2)
        acpid: new package at 2.0.32
    -   [`f805600`](https://github.com/kiss-community/repo/commit/f805600)
        cbindgen: revert to 0.12.1
    -   [`0d5287b`](https://github.com/kiss-community/repo/commit/0d5287b)
        linux-headers: bump to 5.4.11
    -   [`2742025`](https://github.com/kiss-community/repo/commit/2742025)
        cbindgen: bump to 0.12.2
    -   [`f248581`](https://github.com/kiss-community/repo/commit/f248581)
        firefox: move to ESR
    -   [`6de518f`](https://github.com/kiss-community/repo/commit/6de518f)
        firefox-esr: Fix build
    -   [`d0c8db9`](https://github.com/kiss-community/repo/commit/d0c8db9)
        firefox-esr: Fix patch
    -   [`0736a31`](https://github.com/kiss-community/repo/commit/0736a31)
        firefox-bin: New package at 68.4.1esr
    -   [`574fc45`](https://github.com/kiss-community/repo/commit/574fc45)
        firefox-privacy: Remove unneeded dependency
    -   [`d94a903`](https://github.com/kiss-community/repo/commit/d94a903)
        cbindgen: Revert to 0.9.0
    -   [`9e2ea05`](https://github.com/kiss-community/repo/commit/9e2ea05)
        firefox/firefox-bin: Add to extra at 68.4.1esr
    -   [`36b74e5`](https://github.com/kiss-community/repo/commit/36b74e5)
        fontconfig: Add patch to fix gimp.
    -   [`6dbf671`](https://github.com/kiss-community/repo/commit/6dbf671)
        baseinit: bump to 0.2.1
    -   [`e1f53df`](https://github.com/kiss-community/repo/commit/e1f53df)
        git: bump to 2.25.0
    -   [`58799a9`](https://github.com/kiss-community/repo/commit/58799a9)
        linux-headers: Swap to LTS
    -   [`a508f50`](https://github.com/kiss-community/repo/commit/a508f50)
        kiss-utils: Simplify build. @lieuxnoir Closes #134
    -   [`c1f8a28`](https://github.com/kiss-community/repo/commit/c1f8a28)
        liberation-fonts: Simplify build @lieuxnoir
    -   [`47afecd`](https://github.com/kiss-community/repo/commit/47afecd)
        kiss-utils: fix syntax
    -   [`9f520ce`](https://github.com/kiss-community/repo/commit/9f520ce)
        xorg-server: bump to 1.20.7
    -   [`7594886`](https://github.com/kiss-community/repo/commit/7594886)
        baselayout: Mount tmpfs by default.
    -   [`dfffe23`](https://github.com/kiss-community/repo/commit/dfffe23)
        firefox: no spam builds
    -   [`eea6ce7`](https://github.com/kiss-community/repo/commit/eea6ce7)
        vim: bump to 8.2.0119
    -   [`96f1a0d`](https://github.com/kiss-community/repo/commit/96f1a0d)
        webkit2gtk: Add to testing
    -   [`604566b`](https://github.com/kiss-community/repo/commit/604566b)
        webkit2gtk: Add to testing
    -   [`6e8edeb`](https://github.com/kiss-community/repo/commit/6e8edeb)
        webkit2gtk: Add to testing
    -   [`f06e0c4`](https://github.com/kiss-community/repo/commit/f06e0c4)
        testing: move webkit2gtk and friends to community
    -   [`1fa0513`](https://github.com/kiss-community/repo/commit/1fa0513)
        qt5: Fix package
    -   [`7e544ea`](https://github.com/kiss-community/repo/commit/7e544ea)
        libXtst: new package at 1.2.3
    -   [`3280b89`](https://github.com/kiss-community/repo/commit/3280b89)
        qt5-qtwebengine: Add broken package to testing
    -   [`a0a19a9`](https://github.com/kiss-community/repo/commit/a0a19a9)
        qt5-qtwebengine: Progress
    -   [`417cfcf`](https://github.com/kiss-community/repo/commit/417cfcf)
        qt5-qtwebengine: Progress
    -   [`7201e01`](https://github.com/kiss-community/repo/commit/7201e01)
        qt5-qtwebengine: progress
    -   [`de2a203`](https://github.com/kiss-community/repo/commit/de2a203)
        qt5-qtwebengine: Working build
    -   [`d9a8c5f`](https://github.com/kiss-community/repo/commit/d9a8c5f)
        falkon: New package at 3.1.0
    -   [`4083864`](https://github.com/kiss-community/repo/commit/4083864)
        qt5-svg: New package at 5.14.10
    -   [`9d2efa5`](https://github.com/kiss-community/repo/commit/9d2efa5)
        falkon/qtwebengine: Fix media
    -   [`5bed147`](https://github.com/kiss-community/repo/commit/5bed147)
        qt5-: Fix versions
    -   [`844f55f`](https://github.com/kiss-community/repo/commit/844f55f)
        qt5: Fix version
    -   [`e6e39ce`](https://github.com/kiss-community/repo/commit/e6e39ce)
        falkon: Remove unused configure option
    -   [`fc39d99`](https://github.com/kiss-community/repo/commit/fc39d99)
        kiss: bump to 0.60.0
    -   [`b46d9cf`](https://github.com/kiss-community/repo/commit/b46d9cf)
        vim: swap to git
    -   [`c55ab3c`](https://github.com/kiss-community/repo/commit/c55ab3c)
        kiss: bump to 0.60.1
    -   [`064ed33`](https://github.com/kiss-community/repo/commit/064ed33)
        vim: Fix checksums
    -   [`0344ae7`](https://github.com/kiss-community/repo/commit/0344ae7)
        kiss-utils: bump to 0.60.1
    -   [`973c765`](https://github.com/kiss-community/repo/commit/973c765)
        falkon: Added falkon-privacy
    -   [`5f6c238`](https://github.com/kiss-community/repo/commit/5f6c238)
        falkon: Remove xcb-util dependency.
    -   [`e7abc98`](https://github.com/kiss-community/repo/commit/e7abc98)
        qt-: Don't use glib
    -   [`96ec3af`](https://github.com/kiss-community/repo/commit/96ec3af)
        nss: Move to extra
    -   [`f95cce0`](https://github.com/kiss-community/repo/commit/f95cce0)
        qt5: move to extra
    -   [`99579e5`](https://github.com/kiss-community/repo/commit/99579e5)
        extra-cmake-modules: move to extra
    -   [`89e9e57`](https://github.com/kiss-community/repo/commit/89e9e57)
        qt5-\*: move to extra
    -   [`97ec94c`](https://github.com/kiss-community/repo/commit/97ec94c)
        falkon: move to extra
    -   [`141a328`](https://github.com/kiss-community/repo/commit/141a328)
        firefox-bin: revert accidental commit
    -   [`42e62c6`](https://github.com/kiss-community/repo/commit/42e62c6)
        firefox-bin: Update source

## Community

-   **Aaron G**:
    -   [`5f7e096`](https://github.com/kiss-community/community/commit/5f7e096)
        oed: new package at 6.6
    -   [`1090d4d`](https://github.com/kiss-community/community/commit/1090d4d)
        neatvi: new package at 07
    -   [`0d09c9e`](https://github.com/kiss-community/community/commit/0d09c9e)
        neatvi: satisfy shellcheck
    -   [`69b0106`](https://github.com/kiss-community/community/commit/69b0106)
        neatvi: remove useless -- from install invokation
-   **Anirudh Oppiliappan**:
    -   [`f156d3c`](https://github.com/kiss-community/community/commit/f156d3c)
        aerc: new package at 0.3.0
    -   [`be65541`](https://github.com/kiss-community/community/commit/be65541)
        2bwm: new package at 0.3.0
    -   [`cf48650`](https://github.com/kiss-community/community/commit/cf48650)
        2bwm: fix version
-   **Cem Keylan**:
    -   [`947d820`](https://github.com/kiss-community/community/commit/947d820)
        lazygit: add package at v0.13
-   **Cliford Sab**:
    -   [`03046b1`](https://github.com/kiss-community/community/commit/03046b1)
        update: fix build
    -   [`5b8d43e`](https://github.com/kiss-community/community/commit/5b8d43e)
        nnn: bump to 2.9
-   **Dylan Araps** :
    -   [`2b1e66c`](https://github.com/kiss-community/community/commit/2b1e66c)
        imagemagick: new package at 7.0.9-14
    -   [`51b2db2`](https://github.com/kiss-community/community/commit/51b2db2)
        imagemagick: bump to 7.0.9-15
    -   [`6c22f14`](https://github.com/kiss-community/community/commit/6c22f14)
        imagemagick: bump to 7.0.9-16
    -   [`19c0e89`](https://github.com/kiss-community/community/commit/19c0e89)
        liberation-fonts-ttf: Moved to xorg
    -   [`eef14e6`](https://github.com/kiss-community/community/commit/eef14e6)
        libXslt: new package at 1.1.34
    -   [`8adc1b8`](https://github.com/kiss-community/community/commit/8adc1b8)
        libpsl: new package at 0.21.0
    -   [`432de51`](https://github.com/kiss-community/community/commit/432de51)
        icu: new package at 65.1
    -   [`23dd0cb`](https://github.com/kiss-community/community/commit/23dd0cb)
        harfbuzz-icu: new package at 2.6.4
    -   [`19e27e1`](https://github.com/kiss-community/community/commit/19e27e1)
        glib-networking: new package at 2.62.3
    -   [`44e22aa`](https://github.com/kiss-community/community/commit/44e22aa)
        libsoup: new package at 2.68.3
    -   [`719e0bd`](https://github.com/kiss-community/community/commit/719e0bd)
        webkit2gtk: new package at 2.26.2
    -   [`6ac3e6b`](https://github.com/kiss-community/community/commit/6ac3e6b)
        webkit2gtk: Fix whitespace
    -   [`1e2bb6b`](https://github.com/kiss-community/community/commit/1e2bb6b)
        webkit2gtk: Fix depends
    -   [`25afb65`](https://github.com/kiss-community/community/commit/25afb65)
        icu: use https for source
-   **James Davies**:
    -   [`bea9e76`](https://github.com/kiss-community/community/commit/bea9e76)
        Add libtorrent and rtorrent.
    -   [`87606e3`](https://github.com/kiss-community/community/commit/87606e3)
        Remove empty lines, use https
-   **Owen Rafferty**:
    -   [`d34dd2c`](https://github.com/kiss-community/community/commit/d34dd2c)
        pcre: add UTF-8 support
    -   [`ca875f6`](https://github.com/kiss-community/community/commit/ca875f6)
        opendoas: new package at 6.6
-   **ioraff**:
    -   [`7ce3b80`](https://github.com/kiss-community/community/commit/7ce3b80)
        opendoas: fix checksums, build (#226)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
