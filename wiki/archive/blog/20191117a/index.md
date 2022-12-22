Published **17th Nov 2019** by [Dylan
Araps](https://github.com/dylanaraps).

# This week in KISS (#1)

Welcome to the first "This week in KISS"!

The aim of these posts will be to highlight the development of KISS week
by week to hopefully give a better look at the overall status of the
project.

A big thank you to all contributors and a big thank you to everyone
using KISS!

## Index

-   [Highlights](#highlights)
    -   [The Wiki is live](#the-wiki-is-live)
    -   [The subreddit is open](#the-subreddit-is-open)
    -   [KISS ported to ppc64le](#kiss-ported-to-ppc64le)
-   [Patch status](#patch-status)
-   [Official Repositories](#official-repositories)
-   [Community](#community)

## Highlights

### The Wiki is live

The KISS wiki is now live. The wiki is simply a regular GitHub wiki with
a sprinkle of magic to automatically update the website on
contributions.

-   [KISS Wiki](/wiki)
-   [Wiki source](https://github.com/kiss-community/wiki)

### The subreddit is open

The subreddit is now open as another means of communication related to
KISS. This new communication channel compliments the IRC and GitHub well
for discussion.

-   [/r/kisslinux](https://reddit.com/r/kisslinux)

### KISS ported to ppc64le

Work has started on a [ppc64le](https://en.wikipedia.org/wiki/Ppc64)
port of KISS. This is being worked on by
[jdavies-dev](https://github.com/jdavies-dev) and development can be
followed [here](https://github.com/jdavies-dev/repo).

Initial test tarballs can be found
[here](https://github.com/jdavies-dev/kiss-ppc64le-dist).

## Patch status

With the latest `dhcpcd` update, the number of patches in the `core`
repository is down to **one**!

I'm currently working on documenting each of our patches and
upstreaming as many of them as I can.

The current numbers are as follows:

-   **core**: 1
-   **extra**: 19 (*Firefox makes up 8*)
-   **xorg**: 1

You can follow the progress here: [repo #109](https://github.com/kiss-community/repo/issues/109)

## Official Repositories

-   **Dylan Araps**:
    -   [`1aa586e`](https://github.com/kiss-community/repo/commit/1aa586e)
        sowm: bump to 1.0
    -   [`f8c84af`](https://github.com/kiss-community/repo/commit/f8c84af)
        vim: bump to 8.1.2279
    -   [`d32c9c1`](https://github.com/kiss-community/repo/commit/d32c9c1)
        vim: bump to 8.1.2284
    -   [`4e706b4`](https://github.com/kiss-community/repo/commit/4e706b4)
        perl: bump to 5.30.1
    -   [`45412fd`](https://github.com/kiss-community/repo/commit/45412fd)
        vim: bump to 8.1.2291
    -   [`be557ff`](https://github.com/kiss-community/repo/commit/be557ff)
        linux-headers: bump to 5.3.10
    -   [`59d3c75`](https://github.com/kiss-community/repo/commit/59d3c75)
        firefox: better referer settings.
    -   [`cb38df7`](https://github.com/kiss-community/repo/commit/cb38df7)
        firefox (71): better referer settings.
    -   [`ed6d2f0`](https://github.com/kiss-community/repo/commit/ed6d2f0)
        firefox (beta): bump to 71.0b8
    -   [`f483bd5`](https://github.com/kiss-community/repo/commit/f483bd5)
        vim: bump to 8.1.2292
    -   [`9f6ae40`](https://github.com/kiss-community/repo/commit/9f6ae40)
        firefox: bump to 71.0b9
    -   [`71f3777`](https://github.com/kiss-community/repo/commit/71f3777)
        kiss: bump to 0.53.6
    -   [`b322506`](https://github.com/kiss-community/repo/commit/b322506)
        x265: cleaner build
    -   [`c8d801f`](https://github.com/kiss-community/repo/commit/c8d801f)
        libjpeg-turbo: cleaner build
    -   [`7605b5c`](https://github.com/kiss-community/repo/commit/7605b5c)
        vim: bump to 8.1.2297
    -   [`de032cb`](https://github.com/kiss-community/repo/commit/de032cb)
        firefox: fix checksums
    -   [`96cbae7`](https://github.com/kiss-community/repo/commit/96cbae7)
        dhcpcd: bump to 8.1.2
    -   [`3734fa8`](https://github.com/kiss-community/repo/commit/3734fa8)
        vim: bump to 8.1.2300
    -   [`8a95a1f`](https://github.com/kiss-community/repo/commit/8a95a1f)
        llvm: better build
    -   [`5469b31`](https://github.com/kiss-community/repo/commit/5469b31)
        clang: better build
    -   [`cea9d37`](https://github.com/kiss-community/repo/commit/cea9d37)
        mesa: bump to 19.2.4
    -   [`a67dd79`](https://github.com/kiss-community/repo/commit/a67dd79)
        libressl: Add post-install script
    -   [`6728a52`](https://github.com/kiss-community/repo/commit/6728a52)
        alsa-lib: bump to 1.2.1
    -   [`b09aaa7`](https://github.com/kiss-community/repo/commit/b09aaa7)
        alsa-utils: bump to 1.2.1
    -   [`520b023`](https://github.com/kiss-community/repo/commit/520b023)
        firefox (beta): bump to 71.0b10
    -   [`969bd38`](https://github.com/kiss-community/repo/commit/969bd38)
        vim: bump to 8.1.2301
    -   [`3a36ae2`](https://github.com/kiss-community/repo/commit/3a36ae2)
        cmake: build with cmake if available
    -   [`d63fa1a`](https://github.com/kiss-community/repo/commit/d63fa1a)
        cmake: use bundled libs
    -   [`8c3faba`](https://github.com/kiss-community/repo/commit/8c3faba)
        vim: bump to 8.1.2311

## Community

-   **Adam Laughlin**:
    -   [`209ec98`](https://github.com/kiss-community/community/commit/209ec98)
        spotifyd: new package at 0.2.20 (#76)
    -   [`ae3e1f0`](https://github.com/kiss-community/community/commit/ae3e1f0)
        cmus: new package at 2.8.0 (#77)
    -   [`17678ff`](https://github.com/kiss-community/community/commit/17678ff)
        libmad: new package at 0.15.1b (#78)
    -   [`7ef6e04`](https://github.com/kiss-community/community/commit/7ef6e04)
        xorriso: new package at 1.5.2 (#84)
    -   [`ad6f93a`](https://github.com/kiss-community/community/commit/ad6f93a)
        libxkbcommon: new package at 0.9.1 (#81)
    -   [`905f2f2`](https://github.com/kiss-community/community/commit/905f2f2)
        yajl: new package at 2.1.0 (#80)
    -   [`ca7f483`](https://github.com/kiss-community/community/commit/ca7f483)
        libpcre: new package at 8.43 (#79)
    -   [`7c2b7d2`](https://github.com/kiss-community/community/commit/7c2b7d2)
        xcb-util-xrm: new package at 1.3 (#82)
    -   [`f5e0fa3`](https://github.com/kiss-community/community/commit/f5e0fa3)
        sdl: new package at 1.2.15 (#86)
    -   [`b5e9d89`](https://github.com/kiss-community/community/commit/b5e9d89)
        sdl2: new package at 2.0.10 (#85)
-   **Dylan Araps**:
    -   [`0a5dd91`](https://github.com/kiss-community/community/commit/0a5dd91)
        bdftopcf: new package at 1.1
    -   [`56c74c8`](https://github.com/kiss-community/community/commit/56c74c8)
        terminus-font: new package at 4.48
    -   [`ca66764`](https://github.com/kiss-community/community/commit/ca66764)
        dmenu: fix depends
    -   [`e66799c`](https://github.com/kiss-community/community/commit/e66799c)
        luajit: new package at 2.0.5
    -   [`e9fdd27`](https://github.com/kiss-community/community/commit/e9fdd27)
        libpcre: rename to pcre
    -   [`2326366`](https://github.com/kiss-community/community/commit/2326366)
        libev: new package at 4.27
    -   [`2eea948`](https://github.com/kiss-community/community/commit/2eea948)
        libev: move into community
    -   [`248374d`](https://github.com/kiss-community/community/commit/248374d)
        i3-gaps: new package at 4.17.1
    -   [`05530f5`](https://github.com/kiss-community/community/commit/05530f5)
        i3-gaps: fix checksums
    -   [`775cb49`](https://github.com/kiss-community/community/commit/775cb49)
        neovim: bump to 0.4.3
    -   [`16ac4dc`](https://github.com/kiss-community/community/commit/16ac4dc)
        ripgrep: new package at 11.0.2. Closes #5
    -   [`ad00e01`](https://github.com/kiss-community/community/commit/ad00e01)
        fd: new package at 7.4.0. Closes #6
-   **Will Eccles**:
    -   [`ad5ba40`](https://github.com/kiss-community/community/commit/ad5ba40)
        neovim: new package at 0.4.2 (#49)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
