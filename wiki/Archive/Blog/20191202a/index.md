Published **2nd Dec 2019** by [Dylan
Araps](https://github.com/dylanaraps).

# This week in KISS (#3)

Another quiet week.

I spent time working on my password manager
[pash](https://github.com/dylanaraps/pash) rewriting it in POSIX shell.

I've also started work on a fork of
[iwd](https://git.kernel.org/pub/scm/network/wireless/iwd.git/about/)
(*called eiwd*) which works without `dbus`. You can read more about it
below.

A big thank you to everyone using and contributing to KISS!

## Index

-   [EIWD version 0.1.0 released](#eiwd-version-010-released)
-   [Rust and Firefox now build on powerpc64le](#rust-and-firefox-now-build-on-powerpc64le)
-   [Qt5 is now in testing](#qt5-is-now-in-testing)
-   [Official Repositories](#official-repositories)
-   [Community](#community)

## EIWD version 0.1.0 released

This is the first release of my fork of `iwd` with the `dbus` dependency
removed.

So far, all `dbus` code has been removed from the daemon and it is
functional solely through its network configuration files.

A simple utility has been added to aid in the creation of the network
config files called `iwd_passphrase`. This works similarly to
`wpa_passphrase`, automating the process.

The next steps are to write a client utilizing a different IPC
mechanism. I haven't yet decided what kind of IPC I'll implement, any
suggestions are welcome.

Until then, I'm really enjoying `iwd`. I'm using it additionally as my
DHCP client and it connects to networks a lot faster than
`wpa_supplicant`.

For KISS users, `eiwd` is available in the repositories and its current
usage is similar to that of `wpa_supplicant` (without `wpa_cli`).

Release: <https://github.com/dylanaraps/eiwd/releases/tag/0.1.0>

## Rust and Firefox now build on powerpc64le

Rust and Firefox now build on powerpc64le leaving only a small handful
of packages with issues.

This is thanks to the continued work by
[jdavies-dev](https://github.com/jdavies-dev)!

Source: <https://github.com/jdavies-dev/kiss-ppc64le>

## Qt5 is now in testing

The `qt5` base has been added to the testing repository.

I hope to soon tackle the beast that is `qtwebengine` and open up the
possibilities for additional browsers (other than Firefox) on KISS.

## Official Repositories

-   **Dylan Araps**:
    -   [`a37268b`](https://github.com/kiss-community/repo/commit/a37268b)
        libepoxy: bump to 1.5.4
    -   [`c7bbc8d`](https://github.com/kiss-community/repo/commit/c7bbc8d)
        vim: bump to 8.1.2342
    -   [`c1a443f`](https://github.com/kiss-community/repo/commit/c1a443f)
        rust: bump to 1.39.0
    -   [`dee30be`](https://github.com/kiss-community/repo/commit/dee30be)
        firefox: bump to 71.0
    -   [`8a075c4`](https://github.com/kiss-community/repo/commit/8a075c4)
        testing: move packages to extra
    -   [`95a398c`](https://github.com/kiss-community/repo/commit/95a398c)
        cmake: bump to 3.16.0
    -   [`8b30a22`](https://github.com/kiss-community/repo/commit/8b30a22)
        vim: bump to 8.1.2350
    -   [`b575151`](https://github.com/kiss-community/repo/commit/b575151)
        cmake: don't build tests
    -   [`74ef219`](https://github.com/kiss-community/repo/commit/74ef219)
        x265: remove stray slash
    -   [`06a80ca`](https://github.com/kiss-community/repo/commit/06a80ca)
        vim: bump to 8.1.2351
    -   [`02585c7`](https://github.com/kiss-community/repo/commit/02585c7)
        gtk+3: bump to 3.24.13
    -   [`cfb475d`](https://github.com/kiss-community/repo/commit/cfb475d)
        vim: bump to 8.1.2352
    -   [`9d52156`](https://github.com/kiss-community/repo/commit/9d52156)
        eudev: Add runit service.
    -   [`27cb2c8`](https://github.com/kiss-community/repo/commit/27cb2c8)
        baseinit: bump to 0.1.4
    -   [`df19703`](https://github.com/kiss-community/repo/commit/df19703)
        sqlite: enable option for qt5
    -   [`fa74e35`](https://github.com/kiss-community/repo/commit/fa74e35)
        qt5: new package at 5.13.2
    -   [`b0e49f6`](https://github.com/kiss-community/repo/commit/b0e49f6)
        qt5: full depends list
    -   [`6d9ee3d`](https://github.com/kiss-community/repo/commit/6d9ee3d)
        vim: bump to 8.1.2357
    -   [`46d75a2`](https://github.com/kiss-community/repo/commit/46d75a2)
        alsa-lib: bump to 1.2.1.2
    -   [`aa76a17`](https://github.com/kiss-community/repo/commit/aa76a17)
        meson: bump to 0.52.1
    -   [`358ddeb`](https://github.com/kiss-community/repo/commit/358ddeb)
        vim: bump to 8.1.2361
    -   [`9e1cf59`](https://github.com/kiss-community/repo/commit/9e1cf59)
        vim: bump to 8.1.2372
    -   [`326289e`](https://github.com/kiss-community/repo/commit/326289e)
        linux-headers: bump to 5.4.1
    -   [`442a413`](https://github.com/kiss-community/repo/commit/442a413)
        lvm2: bump to 2.03.07
    -   [`c722df7`](https://github.com/kiss-community/repo/commit/c722df7)
        vim: bump to 8.1.2380
    -   [`30ca54b`](https://github.com/kiss-community/repo/commit/30ca54b)
        openresolv: new package at 3.9.2
    -   [`d32dac1`](https://github.com/kiss-community/repo/commit/d32dac1)
        eiwd: new package at 0.1.0
    -   [`47dec02`](https://github.com/kiss-community/repo/commit/47dec02)
        baseinit: bump to 0.1.5

## Community

-   **Dylan Araps**:
    -   [`16458df`](https://github.com/kiss-community/community/commit/16458df)
        tmux: bump to 3.0
    -   [`10e920a`](https://github.com/kiss-community/community/commit/10e920a)
        pandoc-bin: bump to 2.8.0.1
    -   [`a011a72`](https://github.com/kiss-community/community/commit/a011a72)
        nano: bump to 4.6
    -   [`fc67806`](https://github.com/kiss-community/community/commit/fc67806)
        xsel: new package at 1.2.0
    -   [`d6256d7`](https://github.com/kiss-community/community/commit/d6256d7)
        tmux: bump to 3.0a
-   **Sebastian Ertz**:
    -   [`0773f85`](https://github.com/kiss-community/community/commit/0773f85)
        bim: bump to 2.5.0 (#88)
-   **penguin-ff**:
    -   [`05cb4c1`](https://github.com/kiss-community/community/commit/05cb4c1)
        mutt: update to 1.13.0 (#92)
-   **tristelune1**:
    -   [`a792398`](https://github.com/kiss-community/community/commit/a792398)
        poppler-glib: update to 0.83.0 (#91)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
