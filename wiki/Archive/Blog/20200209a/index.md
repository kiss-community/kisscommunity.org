# 09/02/2020: This week in KISS (#10)

More package manager goodies this week.

## Package Manager build hooks

It is now possible to hook into specific "events" in the package
manager with a script. Right now only `pre-build` and `post-build` are
supported though I expect to see this list expand as users need them.

The `KISS_HOOK` environment variable takes the path to a shellscript
which is then executed with three additional environment variables
defined. Rather than needing a separate script per event, a single
script is all that is required.

The following three environment variables are defined:

-   `$PKG`: The name of the package.
-   `$TYPE`: The event type (valid: pre-build, post-build).
-   `$DEST`: The path to where 'make install', etc will put the
    package.

A simple script to set different `CFLAGS` for specific flags could look
as follows.

    #!/bin/sh

    case $TYPE in
        pre-build)
            case $PKG in
               zlib) export CFLAGS="-Os -static" ;;
               curl) export CFLAGS="-O3" ;;
            esac
        ;;

        post-build)
            # post-build code here.
        ;;
    esac

This paves the way for finer tuning of compilation settings for LTO and
more aggressive compiler options. See: [/r/kisslinux
post](https://old.reddit.com/r/kisslinux/comments/f09c9k/aggressive_compiler_optimizations_under_kiss_linux/)

## Smarter `/etc/` handling

The package manager now performs a 3-way "handshake" to determine how
it should handle the installation of files in `/etc`. In short, when a
file cannot be overwritten due to user modifications it is installed as
`$file.new`.

This is very similar to how Arch Linux handles `/etc` and it's a really
nice way of doing things.

## KISS_AUDIT

A new opt-in feature has been added which will open a scrollable `diff`
of every modified file for a system update. This was implemented to
allow users to *easily* get a deeper insight as to what will happen
during updates.

The repositories themselves *are* `git` repositories so this is simply a
`git diff` call post-fetch.

To enable this feature set `KISS_AUDIT` to `1`.

## GCC static-pie fix

Our GCC builds enable
[PIE](https://en.wikipedia.org/wiki/Position-independent_code) by
default though this wasn't applied when compiling statically. A patch
was submitted by [Owen Rafferty](https://github.com/ioraff) which fixes
this issue.

To revert to the previous behavior the following `$CFLAGS` can be used
`-fno-pie -no-pie`.

## Changes to non-root Xorg

Our default non-root Xorg configuration required the user be in the
`input` group to function correctly. This is no longer a requirement and
you may now remove yourself from the group.

Instead, our Xorg is now `setgid input` which limits the permissions to
`/dev/input` solely to Xorg. Any applications spawned under Xorg will
not be able to read `/dev/input`.

This is a nicer and more secure default configuration.

## GNU tar and BSD tar (libarchive) support added to the package manager

These two `tar` implementations are now supported in the package manager
further reducing the dependence on `busybox`. I have found these to be
faster than busybox's `tar` for those large source tarballs.

## Official Repositories

-   **Dylan Araps**:
    -   [`f1db1cf`](https://github.com/kiss-community/repo/commit/f1db1cf)
        cryptsetup: bump to 5.67.0
    -   [`a9b34e1`](https://github.com/kiss-community/repo/commit/a9b34e1)
        libinput: bump to 1.15.1
    -   [`f86714c`](https://github.com/kiss-community/repo/commit/f86714c)
        busybox: Fix mdev.run. Closes #140
    -   [`eb4160f`](https://github.com/kiss-community/repo/commit/eb4160f)
        opendoas: bump to 6.6.1
    -   [`0751732`](https://github.com/kiss-community/repo/commit/0751732)
        glib: bump to 2.63.5
    -   [`2679adc`](https://github.com/kiss-community/repo/commit/2679adc)
        libarchive: new package at 3.4.1
    -   [`87629a8`](https://github.com/kiss-community/repo/commit/87629a8)
        busybox: fix checksums
    -   [`2a1127c`](https://github.com/kiss-community/repo/commit/2a1127c)
        kiss: bump to 1.2.0
    -   [`b9df4fa`](https://github.com/kiss-community/repo/commit/b9df4fa)
        kiss-utils: bump to 1.2.0
    -   [`6447193`](https://github.com/kiss-community/repo/commit/6447193)
        baseinit: bump to 0.4
    -   [`696613a`](https://github.com/kiss-community/repo/commit/696613a)
        cmake: bump to 3.16.4
    -   [`287bee5`](https://github.com/kiss-community/repo/commit/287bee5)
        kiss: bump to 1.2.1
    -   [`b476d52`](https://github.com/kiss-community/repo/commit/b476d52)
        kiss-utils: bump to 1.2.1
    -   [`2969c8c`](https://github.com/kiss-community/repo/commit/2969c8c)
        kiss: bump to 1.2.2
    -   [`dc2ee5c`](https://github.com/kiss-community/repo/commit/dc2ee5c)
        kiss-utils: bump to 1.2.2
    -   [`e486531`](https://github.com/kiss-community/repo/commit/e486531)
        nodejs: bump to 13.8.0
    -   [`ba246df`](https://github.com/kiss-community/repo/commit/ba246df)
        xorg-server: Run setgid. input group no longer needed per-user.
    -   [`ef7f7fc`](https://github.com/kiss-community/repo/commit/ef7f7fc)
        libinput: Remove post-install message
    -   [`e951a27`](https://github.com/kiss-community/repo/commit/e951a27)
        vim: don't link to util-linux
    -   [`662f59d`](https://github.com/kiss-community/repo/commit/662f59d)
        kiss: bump to 1.3.0
    -   [`891344b`](https://github.com/kiss-community/repo/commit/891344b)
        kiss-utils: bump to 1.3.0
    -   [`5611459`](https://github.com/kiss-community/repo/commit/5611459)
        baseinit: bump to 0.4.1
    -   [`1316592`](https://github.com/kiss-community/repo/commit/1316592)
        libSM: Remove util-linux dependency
    -   [`1fa3519`](https://github.com/kiss-community/repo/commit/1fa3519)
        vim: remove unused flag
    -   [`d4c1ea6`](https://github.com/kiss-community/repo/commit/d4c1ea6)
        glib: Remove util-linux dependency
    -   [`ccf9ffb`](https://github.com/kiss-community/repo/commit/ccf9ffb)
        gdk-pixbuf: Don't build tests
    -   [`84e7d60`](https://github.com/kiss-community/repo/commit/84e7d60)
        gtk+3: Don't install tests
    -   [`5901fbf`](https://github.com/kiss-community/repo/commit/5901fbf)
        python: remove util-linux dependency
    -   [`bbec1d1`](https://github.com/kiss-community/repo/commit/bbec1d1)
        kiss: bump to 1.3.1
    -   [`5ea31f6`](https://github.com/kiss-community/repo/commit/5ea31f6)
        kiss-utils: bump to 1.3.1
    -   [`3a38408`](https://github.com/kiss-community/repo/commit/3a38408)
        nss: bump to 3.50
    -   [`66c8f14`](https://github.com/kiss-community/repo/commit/66c8f14)
        meta: Move non-xorg related packages out of xorg/
    -   [`3d47a77`](https://github.com/kiss-community/repo/commit/3d47a77)
        xorg: Drop www. from sources
    -   [`99d840e`](https://github.com/kiss-community/repo/commit/99d840e)
        eiwd: move to extra
    -   [`5ea359f`](https://github.com/kiss-community/repo/commit/5ea359f)
        gdk-pixbuf: Remove shared-mime-info dependency
    -   [`dcacfe9`](https://github.com/kiss-community/repo/commit/dcacfe9)
        gtk+3: Remove shared-mime-info dependency
    -   [`7621366`](https://github.com/kiss-community/repo/commit/7621366)
        gtk+2: remove shared-mime-info dependency
    -   [`8c7acc6`](https://github.com/kiss-community/repo/commit/8c7acc6)
        e2fsprogs: Remove util-linux dependency
    -   [`96ad6fb`](https://github.com/kiss-community/repo/commit/96ad6fb)
        gcc: bump version for libgomp and static-pie fixes.
    -   [`cbbbf9b`](https://github.com/kiss-community/repo/commit/cbbbf9b)
        kiss: bump to 1.4.0
    -   [`1dc1377`](https://github.com/kiss-community/repo/commit/1dc1377)
        kiss-utils: bump to 1.4.0
    -   [`b2a5d52`](https://github.com/kiss-community/repo/commit/b2a5d52)
        json-c: fix depends. Closes #143 by @artemkobets
    -   [`0cbdf32`](https://github.com/kiss-community/repo/commit/0cbdf32)
        xf86-video-ati: Fix rootless xorg
    -   [`e67a209`](https://github.com/kiss-community/repo/commit/e67a209)
        extra-cmake-modules: bump to 5.67.0
    -   [`6e64fb7`](https://github.com/kiss-community/repo/commit/6e64fb7)
        kiss: bump to 1.4.1
    -   [`cfbe193`](https://github.com/kiss-community/repo/commit/cfbe193)
        kiss-utils: bump to 1.4.1
    -   [`1a9ada8`](https://github.com/kiss-community/repo/commit/1a9ada8)
        opendoas: added new doas.conf for latest kiss
    -   [`eecc3f2`](https://github.com/kiss-community/repo/commit/eecc3f2)
        grub: Fix build after GCC changes

## Community

-   **Adam Schaefers**:
    -   [`0483840`](https://github.com/kiss-community/community/commit/0483840)
        strace: bump to 5.5 (#319)
    -   [`2edfb7b`](https://github.com/kiss-community/community/commit/2edfb7b)
        gawk: bump to 5.0.1 (#318)
-   **Anirudh**:
    -   [`a915d2d`](https://github.com/kiss-community/community/commit/a915d2d)
        gdb: new package at 8.3.1 (#300)
-   **Artem Kobets**:
    -   [`8f9db40`](https://github.com/kiss-community/community/commit/8f9db40)
        slmenu: new package at 0.1 (#310)
    -   [`59ce0e6`](https://github.com/kiss-community/community/commit/59ce0e6)
        xmlsec1: new package at 1.2.29 (#316)
    -   [`f38228e`](https://github.com/kiss-community/community/commit/f38228e)
        oath-toolkit: new package at 2.6.2 (#317)
-   **Bridouz**:
    -   [`90ba99a`](https://github.com/kiss-community/community/commit/90ba99a)
        fff: fix depends (#305)
    -   [`b512ccf`](https://github.com/kiss-community/community/commit/b512ccf)
        ntfs-3g: new packages at 2017.3.23 (#306)
    -   [`11dd377`](https://github.com/kiss-community/community/commit/11dd377)
        syncthing: new package at 1.3.4 (#308)
-   **Cem Keylan**:
    -   [`7488c6a`](https://github.com/kiss-community/community/commit/7488c6a)
        lazygit: bump to 0.14 (#309)
    -   [`f687a7a`](https://github.com/kiss-community/community/commit/f687a7a)
        sinit: build without depending on ubase (#276)
-   **Cédric**:
    -   [`5ef22f8`](https://github.com/kiss-community/community/commit/5ef22f8)
        Update poppler-glib to 0.85.0 (#301)
    -   [`bf05708`](https://github.com/kiss-community/community/commit/bf05708)
        New package: poppler at 0.85.0 and removal of poppler-glib
        (#314)
-   **Dylan Araps**:
    -   [`2907091`](https://github.com/kiss-community/community/commit/2907091)
        weechat: Fix depends. Closes #302
    -   [`e65c6c0`](https://github.com/kiss-community/community/commit/e65c6c0)
        sbase: Nitpicks
    -   [`6cbd09a`](https://github.com/kiss-community/community/commit/6cbd09a)
        ubase: Nitpicks
    -   [`8b4b029`](https://github.com/kiss-community/community/commit/8b4b029)
        nano: bump to 4.8
    -   [`0865af5`](https://github.com/kiss-community/community/commit/0865af5)
        bash: bump to 5.0.p16
    -   [`28eb81c`](https://github.com/kiss-community/community/commit/28eb81c)
        libgpg-error: bump to 1.37
    -   [`0782430`](https://github.com/kiss-community/community/commit/0782430)
        imagemagick: bump to 7.0.9-22
-   **M. Herdiansyah**:
    -   [`795969a`](https://github.com/kiss-community/community/commit/795969a)
        mawk: new package at 1.3.4-20200120 (#313)
-   **Owen Rafferty**:
    -   [`61f1da0`](https://github.com/kiss-community/community/commit/61f1da0)
        sbase: respect environmental vars, fix static linking (#303)
    -   [`fd16383`](https://github.com/kiss-community/community/commit/fd16383)
        ubase: respect LDFLAGS (#304)
-   **Will Eccles**:
    -   [`fb4d26b`](https://github.com/kiss-community/community/commit/fb4d26b)
        cfm: update to 0.4.4 (#295)
    -   [`f4f6290`](https://github.com/kiss-community/community/commit/f4f6290)
        cfm: update to 0.4.5 (#312)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
