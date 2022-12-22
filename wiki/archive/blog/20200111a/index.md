# 11/01/2020: This week in KISS (#6)

The focus this week was on increasing the portability of the boot
scripts. This involved adding new "generic" hooks and removing any
non-portable flags.

The boot scripts now include a pure shell implementation of `killall5`
as well. This maintains the functionality while keeping it 100% portable
across coreutils.

The package manager also saw a move from `busybox wget` to `curl` for
downloading sources. This satisfies the download tool requirement for
coreutils which don't provide `wget` and `curl` was already in `core`
(for `git`).

Thanks to everyone using and contributing to KISS.

## Index

-   [Official Repositories](#official-repositories)
-   [Community](#community)

## Official Repositories

-   **Dylan Araps**:
    -   [`1776ca7`](https://github.com/kiss-community/repo/commit/1776ca7)
        libinput: bump to 1.15.0
    -   [`9a82e4b`](https://github.com/kiss-community/repo/commit/9a82e4b)
        dhcpcd: bump to 8.1.5
    -   [`09411fb`](https://github.com/kiss-community/repo/commit/09411fb)
        vim: bump to 8.2.0086
    -   [`5df7ad3`](https://github.com/kiss-community/repo/commit/5df7ad3)
        ccache: bump to 3.7.7
    -   [`d26ce48`](https://github.com/kiss-community/repo/commit/d26ce48)
        vim: bump to 8.2.0090
    -   [`3beb97d`](https://github.com/kiss-community/repo/commit/3beb97d)
        kiss: bump to 0.54.0
    -   [`f9d2d1f`](https://github.com/kiss-community/repo/commit/f9d2d1f)
        linux-headers: bump to 5.4.8
    -   [`8bcfbe0`](https://github.com/kiss-community/repo/commit/8bcfbe0)
        libwebp: bump to 1.1.0
    -   [`d66eda9`](https://github.com/kiss-community/repo/commit/d66eda9)
        vim: bump to 8.2.0096
    -   [`8a19b60`](https://github.com/kiss-community/repo/commit/8a19b60)
        firefox (beta): bump to 73.0b1
    -   [`e36d67f`](https://github.com/kiss-community/repo/commit/e36d67f)
        efibootmgr: Fix verbose
    -   [`c82efdc`](https://github.com/kiss-community/repo/commit/c82efdc)
        curl: bump to 7.68.0
    -   [`1b91e94`](https://github.com/kiss-community/repo/commit/1b91e94)
        e2fsprogs: bump to 1.45.5
    -   [`fb0db77`](https://github.com/kiss-community/repo/commit/fb0db77)
        meson: bump to 0.53.0
    -   [`a7ecbd4`](https://github.com/kiss-community/repo/commit/a7ecbd4)
        efibootmgr: Revert patch
    -   [`64362b8`](https://github.com/kiss-community/repo/commit/64362b8)
        efivar: Pull patches from upstream to fix verbose issues in efibootmgr
    -   [`398e63a`](https://github.com/kiss-community/repo/commit/398e63a)
        nodejs: bump to 13.6.0
    -   [`ff30eae`](https://github.com/kiss-community/repo/commit/ff30eae)
        firefox: bump to 73.0b2
    -   [`018bf47`](https://github.com/kiss-community/repo/commit/018bf47)
        vim: bump to 8.2.0100
    -   [`1699e03`](https://github.com/kiss-community/repo/commit/1699e03)
        baseinit: Fix source
    -   [`bcdeddc`](https://github.com/kiss-community/repo/commit/bcdeddc)
        curl: Fix sources
    -   [`29c2558`](https://github.com/kiss-community/repo/commit/29c2558)
        firefox: bump to 72.0.1
    -   [`c465871`](https://github.com/kiss-community/repo/commit/c465871)
        baseinit: fix checksums
    -   [`df95fba`](https://github.com/kiss-community/repo/commit/df95fba)
        vim: bump to 8.2.0106
    -   [`05bfdd8`](https://github.com/kiss-community/repo/commit/05bfdd8)
        eiwd: bump to 0.2.5
    -   [`47a7836`](https://github.com/kiss-community/repo/commit/47a7836)
        glib: fix source
    -   [`3f4184d`](https://github.com/kiss-community/repo/commit/3f4184d)
        LICENSE: Increment copyright year
    -   [`9af9985`](https://github.com/kiss-community/repo/commit/9af9985)
        kiss-utils: bump to 0.54.0
    -   [`4476c93`](https://github.com/kiss-community/repo/commit/4476c93)
        mesa: bump to 19.3.2
    -   [`248bc57`](https://github.com/kiss-community/repo/commit/248bc57)
        kiss: bump to 0.56.0
    -   [`09b6288`](https://github.com/kiss-community/repo/commit/09b6288)
        kiss-utils: bump to 0.56.0
    -   [`d04ddce`](https://github.com/kiss-community/repo/commit/d04ddce)
        vim: bump to 8.2.0109
    -   [`fb88ed6`](https://github.com/kiss-community/repo/commit/fb88ed6)
        linux-headers: bump to 5.4.10
    -   [`3753106`](https://github.com/kiss-community/repo/commit/3753106)
        firefox: bump to 73.0b3
    -   [`f39e3fc`](https://github.com/kiss-community/repo/commit/f39e3fc)
        cbindgen: bump to 0.12.2. Release made without tag
    -   [`19aa586`](https://github.com/kiss-community/repo/commit/19aa586)
        kiss: bump to 0.57.0
    -   [`26b3bbc`](https://github.com/kiss-community/repo/commit/26b3bbc)
        kiss-utils: bump to 0.57.0
    -   [`29fe61c`](https://github.com/kiss-community/repo/commit/29fe61c)
        libwebp: Fix source
    -   [`624c4fb`](https://github.com/kiss-community/repo/commit/624c4fb)
        curl: link statically
    -   [`10ee015`](https://github.com/kiss-community/repo/commit/10ee015)
        baseinit: bump to 0.2.0
    -   [`d9f135f`](https://github.com/kiss-community/repo/commit/d9f135f)
        eiwd: Fix make depends

## Community

-   **Aaron G**:
    -   [`3116232`](https://github.com/kiss-community/community/commit/3116232)
        socat: remove 'files'
    -   [`2aba150`](https://github.com/kiss-community/community/commit/2aba150)
        socat: update to 1.7.3.4
-   **Adam Schaefers**:
    -   [`a91dabf`](https://github.com/kiss-community/community/commit/a91dabf)
        gnugrep: bump to 3.4
    -   [`a2562db`](https://github.com/kiss-community/community/commit/a2562db)
        gnugrep: bump version file to 3.4
    -   [`eec4f26`](https://github.com/kiss-community/community/commit/eec4f26)
        emacs: update depends
    -   [`88771b7`](https://github.com/kiss-community/community/commit/88771b7)
        new package: gauche 0.9.9
    -   [`a7d5a41`](https://github.com/kiss-community/community/commit/a7d5a41)
        gawk: downngrade to 4.2.1 fixes #192
-   **Cem Keylan**:
    -   [`d735073`](https://github.com/kiss-community/community/commit/d735073)
        surfraw: new package 2.3.0
    -   [`1499109`](https://github.com/kiss-community/community/commit/1499109)
        surfraw: fix MKDIR_P
-   **Cédric**:
    -   [`bffe2d0`](https://github.com/kiss-community/community/commit/bffe2d0)
        update to girara 3.4
    -   [`040e8bf`](https://github.com/kiss-community/community/commit/040e8bf)
        update to zathura 0.4.5
    -   [`9711646`](https://github.com/kiss-community/community/commit/9711646)
        update to zathura-pdf-poppler 0.3.0
-   **Dylan Araps**:
    -   [`27b0196`](https://github.com/kiss-community/community/commit/27b0196)
        xorriso: bump to 1.5.3
    -   [`9b7f273`](https://github.com/kiss-community/community/commit/9b7f273)
        btrfs-progs: Remove zstd
    -   [`cd29cbd`](https://github.com/kiss-community/community/commit/cd29cbd)
        zstd: Drop from community
    -   [`84757d1`](https://github.com/kiss-community/community/commit/84757d1)
        pandoc-bin: bump to 2.9.1.1
    -   [`13bd9bd`](https://github.com/kiss-community/community/commit/13bd9bd)
        btrfs-progs: bump to 5.4.1
    -   [`1feecbc`](https://github.com/kiss-community/community/commit/1feecbc)
        go: bump to 1.13.6
-   **Kris Heck**:
    -   [`15f889f`](https://github.com/kiss-community/community/commit/15f889f)
        tor: new package at 0.4.2.5

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
