# 02/02/2020: This week in KISS (#9)

Alternatives!

## Index

-   [Alternatives system](#alternatives-system)
-   [Official Repositories](#official-repositories)
-   [Community](#community)

## Alternatives system

The package manager now includes an "alternatives system". This
feature allows you to change the provider of a specific file or set of
files.

For example, a user can now swap from busybox to the GNU coreutils by
running a simple command.

This works in an entirely dynamic way and required zero changes to the
package format or the repository files themselves! \[1\]

When a conflict is detected between another package during installation,
the conflicting files become "choices" in the alternatives system.

Running `kiss a` or `kiss alternatives` will list all available choices
that can be made.

    -> kiss a
    -> Alternatives:
    ncurses /usr/bin/clear
    ncurses /usr/bin/reset

The above command tells me that I have two available choices from the
`ncurses` package. To find out which package owns the current
"choice", the `kiss-owns` utility from `kiss-utils` can be used (a
simple `grep` in your installed db also works).

    -> kiss a ncurses /usr/bin/clear
    -> Swapping '/usr/bin/clear' from 'busybox' to 'ncurses'

My system now uses `/usr/bin/clear` from the `ncurses` package. Running
`kiss a` again will now show the following output.

    -> kiss a
    -> Alternatives:
    busybox /usr/bin/clear
    ncurses /usr/bin/reset

Here's a more complex example showing the swap between a large bulk of
choices.

    -> kiss a
    -> Alternatives:
    busybox /usr/bin/clear
    coreutils /usr/bin/[
    coreutils /usr/bin/base64
    coreutils /usr/bin/basename
    coreutils /usr/bin/cat
    coreutils /usr/bin/chgrp
    coreutils /usr/bin/chmod
    # Lots of 'coreutils *' lines here.
    coreutils /usr/bin/whoami
    coreutils /usr/bin/yes
    ncurses /usr/bin/reset

The output of `kiss a` can be directly used as input to `kiss a`. Each
line is a valid set of arguments! Here's how you'd swap to GNU
coreutils in a single command.

    # The package manager will read each line from stdin.
    kiss a | grep ^coreutils | kiss a -

    # Running 'kiss a' will show the inverse of the above listing,
    # a long output of 'busybox *'.

My system is now using the GNU coreutils!

This system works for any files across the entire filesystem and as it
is entirely dynamic (requiring no changes to the repositories or the
package format \[1\]) it is backwards compatible.

The feature allows the user to swap their `/bin/sh`, `coreutils` and
really anything they desire. Very complex setups are now easily possible
when this is paired with the repository system.

The package manager, init scripts and package files are written in POSIX
shell allowing any POSIX compatible shell or coreutils to be used in
place of the defaults (*one exception is made for `sed -i` which is too
useful to let go of* \[2\]).

**With this change, the user now has the choice between, init, device
manager, coreutils, shell and anything they desire!**

\[1\]: Some minor changes were made to *where* some packages install
their files. coreutils was installed to /usr/local/bin due to the
absence of this alternatives feature. This was still not a change to the
format of the package system itself though!

\[2\]: Utilities like `tar` which have no standard command-line
interface may be incompatible when swapped out. There's nothing that
can really be done about this.

## Official Repositories

-   **Dylan Araps**:
    -   [`72be609`](https://github.com/kiss-community/repo/commit/72be609)
        falkon: Added optional open-in-mpv extension
    -   [`15f1d9b`](https://github.com/kiss-community/repo/commit/15f1d9b)
        sowm: bump to 1.2
    -   [`8a25531`](https://github.com/kiss-community/repo/commit/8a25531)
        mpv: bump to 0.32.0
    -   [`f8658f1`](https://github.com/kiss-community/repo/commit/f8658f1)
        pkgconf: Swap to http source for now. Closes #139
    -   [`154f4a3`](https://github.com/kiss-community/repo/commit/154f4a3)
        qt5-\*: bump to 5.14.1
    -   [`6549391`](https://github.com/kiss-community/repo/commit/6549391)
        falkon: Remove unneeded sed calls
    -   [`6043ae3`](https://github.com/kiss-community/repo/commit/6043ae3)
        falkon: fix version
    -   [`0e47e11`](https://github.com/kiss-community/repo/commit/0e47e11)
        sqlite: bump to 3.31.1
    -   [`f961652`](https://github.com/kiss-community/repo/commit/f961652)
        dhcpcd: bump to 8.1.6
    -   [`37177ef`](https://github.com/kiss-community/repo/commit/37177ef)
        openresolv: bump to 3.10.0
    -   [`85b261c`](https://github.com/kiss-community/repo/commit/85b261c)
        libva-utils: Fix depends
    -   [`209bea7`](https://github.com/kiss-community/repo/commit/209bea7)
        mesa: bump to 19.3.3
    -   [`f1aa593`](https://github.com/kiss-community/repo/commit/f1aa593)
        kiss: bump to 1.0.0
    -   [`cf5a975`](https://github.com/kiss-community/repo/commit/cf5a975)
        kiss-utils: bump to 1.0.0
    -   [`796550e`](https://github.com/kiss-community/repo/commit/796550e)
        kiss: bump to 1.0.1
    -   [`6149f07`](https://github.com/kiss-community/repo/commit/6149f07)
        kiss-utils: bump to 1.0.1
    -   [`a42e25d`](https://github.com/kiss-community/repo/commit/a42e25d)
        ncurses: Allow conflicts
    -   [`e949836`](https://github.com/kiss-community/repo/commit/e949836)
        baseinit: bump to 0.3
    -   [`8004986`](https://github.com/kiss-community/repo/commit/8004986)
        kiss: bump to 1.0.2
    -   [`db53c47`](https://github.com/kiss-community/repo/commit/db53c47)
        kiss-utils: bump to 1.0.2
    -   [`2b52c35`](https://github.com/kiss-community/repo/commit/2b52c35)
        kiss: bump to 1.0.3
    -   [`eee548b`](https://github.com/kiss-community/repo/commit/eee548b)
        kiss-utils: bump to 1.0.3
    -   [`587f8ca`](https://github.com/kiss-community/repo/commit/587f8ca)
        kiss: bump to 1.0.4
    -   [`e30562c`](https://github.com/kiss-community/repo/commit/e30562c)
        kiss-utils: bump to 1.0.4
    -   [`c28cb6f`](https://github.com/kiss-community/repo/commit/c28cb6f)
        kiss: bump to 1.0.5
    -   [`876afd4`](https://github.com/kiss-community/repo/commit/876afd4)
        kiss-utils: bump to 1.0.5
    -   [`fa42f5e`](https://github.com/kiss-community/repo/commit/fa42f5e)
        kiss: bump to 1.0.6
    -   [`ff42d39`](https://github.com/kiss-community/repo/commit/ff42d39)
        kiss-utils: bump to 1.0.6
    -   [`bcf681b`](https://github.com/kiss-community/repo/commit/bcf681b)
        kiss-utils: Fix build with suckless install
    -   [`8a6f5ce`](https://github.com/kiss-community/repo/commit/8a6f5ce)
        xinit: remove sed -i
    -   [`d3ae5d1`](https://github.com/kiss-community/repo/commit/d3ae5d1)
        st: Remove sed -i
    -   [`b314878`](https://github.com/kiss-community/repo/commit/b314878)
        mesa: remove sed -i
    -   [`df36110`](https://github.com/kiss-community/repo/commit/df36110)
        libxcb: Remove sed -i
    -   [`2217317`](https://github.com/kiss-community/repo/commit/2217317)
        intel-media-driver: Remove sed -i
    -   [`d8efedb`](https://github.com/kiss-community/repo/commit/d8efedb)
        repo: Revert sed changes
    -   [`3dcf2e3`](https://github.com/kiss-community/repo/commit/3dcf2e3)
        mtdev: bump to 1.1.6
    -   [`33d6106`](https://github.com/kiss-community/repo/commit/33d6106)
        kiss: bump to 1.1.1
    -   [`877a99e`](https://github.com/kiss-community/repo/commit/877a99e)
        kiss-utils: bump to 1.1.1
    -   [`a8262d4`](https://github.com/kiss-community/repo/commit/a8262d4)
        kiss: bump to 1.1.2
    -   [`a07695a`](https://github.com/kiss-community/repo/commit/a07695a)
        kiss-utils: bump to 1.1.2
    -   [`6c693fd`](https://github.com/kiss-community/repo/commit/6c693fd)
        kiss: bump to 1.1.3
    -   [`b177fc8`](https://github.com/kiss-community/repo/commit/b177fc8)
        kiss-utils: bump to 1.1.3
    -   [`e2f5025`](https://github.com/kiss-community/repo/commit/e2f5025)
        kiss: bump to 1.1.4
    -   [`db27e9e`](https://github.com/kiss-community/repo/commit/db27e9e)
        kiss-utils: bump to 1.1.4
    -   [`04571c5`](https://github.com/kiss-community/repo/commit/04571c5)
        kiss: bump to 1.1.6
    -   [`f8b28be`](https://github.com/kiss-community/repo/commit/f8b28be)
        kiss-utils: bump to 1.1.6
    -   [`806c863`](https://github.com/kiss-community/repo/commit/806c863)
        opendoas: Move to extra
    -   [`aeaa1b3`](https://github.com/kiss-community/repo/commit/aeaa1b3)
        docs: update
    -   [`2dd7b91`](https://github.com/kiss-community/repo/commit/2dd7b91)
        kiss: bump to 1.1.7
    -   [`0e275d5`](https://github.com/kiss-community/repo/commit/0e275d5)
        kiss-utils: bump to 1.1.7
    -   [`5593f35`](https://github.com/kiss-community/repo/commit/5593f35)
        rust \[testing\]: Added rust 1.41.0
    -   [`0f3103f`](https://github.com/kiss-community/repo/commit/0f3103f)
        sudo: bump to 1.8.31
    -   [`f6e43e1`](https://github.com/kiss-community/repo/commit/f6e43e1)
        cbindgen \[testing\]: bump to 0.13.0
    -   [`24a5463`](https://github.com/kiss-community/repo/commit/24a5463)
        rust: Use xz
    -   [`6549c1e`](https://github.com/kiss-community/repo/commit/6549c1e)
        cbindgen: Bump to 0.13.0
    -   [`ebbb23b`](https://github.com/kiss-community/repo/commit/ebbb23b)
        rust: bump to 1.41.0
    -   [`1d4b4a8`](https://github.com/kiss-community/repo/commit/1d4b4a8)
        util-linux: bump to 2.35.1
    -   [`b3db27b`](https://github.com/kiss-community/repo/commit/b3db27b)
        xkeyboard-config: bump to 2.29
    -   [`b93e8ac`](https://github.com/kiss-community/repo/commit/b93e8ac)
        binutils: bump to 2.34

## Community

-   **Adam Schaefers**:
    -   [`f735f0e`](https://github.com/kiss-community/community/commit/f735f0e)
        New Package: sinit 1.1 (#200)
    -   [`96a061e`](https://github.com/kiss-community/community/commit/96a061e)
        sinit: revert to 1.0 (#270)
    -   [`c6029b2`](https://github.com/kiss-community/community/commit/c6029b2)
        sbase: use official git sources (#271)
    -   [`88278aa`](https://github.com/kiss-community/community/commit/88278aa)
        ubase: use official sources (#272)
    -   [`358a6b1`](https://github.com/kiss-community/community/commit/358a6b1)
        nawk: update build for alternatives (#288)
    -   [`57f66e4`](https://github.com/kiss-community/community/commit/57f66e4)
        patch: update build for alternatives (#286)
    -   [`6df5604`](https://github.com/kiss-community/community/commit/6df5604)
        gnugrep: update build for alternatives (#285)
    -   [`cf9d490`](https://github.com/kiss-community/community/commit/cf9d490)
        findutils: update build for alternatives (#283)
    -   [`66487d0`](https://github.com/kiss-community/community/commit/66487d0)
        diffutils: update build for alternatives (#282)
    -   [`9b4cc92`](https://github.com/kiss-community/community/commit/9b4cc92)
        dash: update build for alternatives (#281)
    -   [`5cb9a66`](https://github.com/kiss-community/community/commit/5cb9a66)
        gawk: update build for alternatives (#280)
    -   [`cb3b96f`](https://github.com/kiss-community/community/commit/cb3b96f)
        coreutils: remove 'g' prefix from build (#279)
    -   [`a02560b`](https://github.com/kiss-community/community/commit/a02560b)
        gtar: update build for alternatives (#287)
    -   [`766c1cc`](https://github.com/kiss-community/community/commit/766c1cc)
        new package: psproc-ng (#289)
    -   [`71ab4de`](https://github.com/kiss-community/community/commit/71ab4de)
        fix name: proccps-ng (#291)
    -   [`7ab9583`](https://github.com/kiss-community/community/commit/7ab9583)
        procps-ng: bump to latest (#293)
-   **Anirudh**:
    -   [`f107694`](https://github.com/kiss-community/community/commit/f107694)
        aerc: Track latest git instead (#266)
-   **Cem Keylan**:
    -   [`6df240b`](https://github.com/kiss-community/community/commit/6df240b)
        discount: new package at 2.2.6
    -   [`0d996db`](https://github.com/kiss-community/community/commit/0d996db)
        9base: new package at 63916da (#246)
    -   [`9769c2c`](https://github.com/kiss-community/community/commit/9769c2c)
        discount: fix indentation
    -   [`b931ae9`](https://github.com/kiss-community/community/commit/b931ae9)
        groff: new package at 1.22.4 (#245)
    -   [`badc409`](https://github.com/kiss-community/community/commit/badc409)
        webkit2gtk: fix depends (#297)
-   **Dylan Araps**:
    -   [`f008149`](https://github.com/kiss-community/community/commit/f008149)
        imagemagick: bump to 7.0.9-18
    -   [`2f9a3a8`](https://github.com/kiss-community/community/commit/2f9a3a8)
        imagemagick: bump to 7.0.9-19
    -   [`85b1197`](https://github.com/kiss-community/community/commit/85b1197)
        go: bump to 1.13.7
    -   [`185b79e`](https://github.com/kiss-community/community/commit/185b79e)
        imagemagick: bump to 7.0.9-20
    -   [`5b41b93`](https://github.com/kiss-community/community/commit/5b41b93)
        spotifyd: drop package
    -   [`96f8dba`](https://github.com/kiss-community/community/commit/96f8dba)
        ubase: Drop su
    -   [`8af78ef`](https://github.com/kiss-community/community/commit/8af78ef)
        sbase: Drop tar
    -   [`c32880f`](https://github.com/kiss-community/community/commit/c32880f)
        sbase: Use unlink
    -   [`abc34fb`](https://github.com/kiss-community/community/commit/abc34fb)
        ubase: Use unlink
    -   [`383d6d9`](https://github.com/kiss-community/community/commit/383d6d9)
        sbase: Remove sed
    -   [`42bfd0b`](https://github.com/kiss-community/community/commit/42bfd0b)
        opendoas: Move to extra
    -   [`f1d59d0`](https://github.com/kiss-community/community/commit/f1d59d0)
        mc: bump to 4.8.24
    -   [`f710b64`](https://github.com/kiss-community/community/commit/f710b64)
        psproc-ng: Drop package
    -   [`f14992e`](https://github.com/kiss-community/community/commit/f14992e)
        imagemagick: bump to 7.0.9-21
    -   [`fec9e16`](https://github.com/kiss-community/community/commit/fec9e16)
        pciutils: new package at 3.6.2. Closes #296
    -   [`3c335d8`](https://github.com/kiss-community/community/commit/3c335d8)
        nettle: bump to latest commit to fix gnutls build issues.
    -   [`5919df8`](https://github.com/kiss-community/community/commit/5919df8)
        gnutls: bump to 3.6.12
    -   [`94b8c8c`](https://github.com/kiss-community/community/commit/94b8c8c)
        pciutils: bump to 3.6.4
-   **Jonathan Dahan**:
    -   [`6ae6436`](https://github.com/kiss-community/community/commit/6ae6436)
        osh: bump to 0.7.0 (#269)
-   **Will Eccles**:
    -   [`8c2998f`](https://github.com/kiss-community/community/commit/8c2998f)
        cfm: new package at v0.1.2 (#274)
    -   [`49c9df5`](https://github.com/kiss-community/community/commit/49c9df5)
        cfm: update to 0.3.2 (#277)
    -   [`4a74379`](https://github.com/kiss-community/community/commit/4a74379)
        cfm: update to 0.4.1 (#278)
-   **dzove855**:
    -   [`a55704b`](https://github.com/kiss-community/community/commit/a55704b)
        \* Add xtrlock build (#268)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
