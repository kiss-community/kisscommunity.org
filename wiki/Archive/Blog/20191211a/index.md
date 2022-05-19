Published **11th Dec 2019** by [Dylan
Araps](https://github.com/dylanaraps).

# This week in KISS (#4)

Apologies for the late post, I'll be on time from now on. :)

This week I wrote a simple (*and temporary*) client for
[eiwd](https://github.com/dylanaraps/eiwd/) called
[iwc](https://github.com/dylanaraps/eiwd/blob/master/iwc). More about
this below.

I've also been working on something unrelated to Linux and friends
which I hope to talk about when it is complete.

A big thank you to everyone using, contributing and donating to KISS!

## Index

-   [iwc](#iwc)
-   [Official Repositories](#official-repositories)
-   [Community](#community)

## iwc

This client is based around the fact that the `iwd` daemon watches the
network files in its configuration directory.

    iwc 0.2.1 - simple eiwd client.

    => [au]th       [ssid] - Create network config.
    => [co]nnect    [ssid] - Connect to an SSID.
    => [de]lete     [ssid] - Delete a configured network.
    => [di]sconnect        - Disconnect from the current network.
    => [ed]it       [ssid] - Edit an SSID's network config.
    => [li]st              - List all known networks.
    => [sc]an              - Display periodic scan results.
    => [ss]id              - Display the current SSID.

Disconnecting from a network simply moves the file into a subdirectory
and connecting to a network is really just making `iwd` temporarily
forget about a network.

    mv ssid.psk ssid.psk.bak
    sleep 1
    mv ssid.psk.bak ssid.psk

Connection works as the "removal" of the network file causes `iwd` to
"forget" about the network and the addition of the file wakes `iwd` to
connect to it.

To add further typical features like viewing scan results and getting
the current connected network I made some tiny additions to `iwd`'s
source.

This is overly simple and of course doesn't offer a full and real
client, however until I get around to writing a proper client, *it's
something*!

The latest release of `eiwd` can be found here:
<https://github.com/dylanaraps/eiwd/releases/tag/0.2.1>

## Official Repositories

-   **Dylan Araps**:
    -   [`47dec02`](https://github.com/kiss-community/repo/commit/47dec02)
        baseinit: bump to 0.1.5
    -   [`87df875`](https://github.com/kiss-community/repo/commit/87df875)
        cbindgen: bump to 0.10.1
    -   [`32b7279`](https://github.com/kiss-community/repo/commit/32b7279)
        vim: bump to 8.1.2383
    -   [`c7c7de4`](https://github.com/kiss-community/repo/commit/c7c7de4)
        firefox: update source
    -   [`b0dde4c`](https://github.com/kiss-community/repo/commit/b0dde4c)
        curl: remove unneeded dependency
    -   [`1b141f3`](https://github.com/kiss-community/repo/commit/1b141f3)
        firefox (beta): Added 72.0b1
    -   [`b535550`](https://github.com/kiss-community/repo/commit/b535550)
        cbindgen: bump to 0.11.0
    -   [`92e995f`](https://github.com/kiss-community/repo/commit/92e995f)
        firefox (beta): bump to 72.0b2
    -   [`a7d5245`](https://github.com/kiss-community/repo/commit/a7d5245)
        vim: bump to 8.1.2384
    -   [`a4ef7e0`](https://github.com/kiss-community/repo/commit/a4ef7e0)
        nodejs: bump to 13.3.0
    -   [`cf8086a`](https://github.com/kiss-community/repo/commit/cf8086a)
        eiwd: bump to 0.2.0
    -   [`775c747`](https://github.com/kiss-community/repo/commit/775c747)
        xvidcore: bump to 1.3.6
    -   [`812b7d3`](https://github.com/kiss-community/repo/commit/812b7d3)
        eiwd: bump to 0.2.1
    -   [`35f0638`](https://github.com/kiss-community/repo/commit/35f0638)
        mesa: bump to 19.2.7
    -   [`5c1b71c`](https://github.com/kiss-community/repo/commit/5c1b71c)
        vim: bump to 8.1.2389
    -   [`f555f32`](https://github.com/kiss-community/repo/commit/f555f32)
        linux-headers: bump to 5.4.2
    -   [`a95c898`](https://github.com/kiss-community/repo/commit/a95c898)
        vim: bump to 8.1.2397
    -   [`76f91fd`](https://github.com/kiss-community/repo/commit/76f91fd)
        firefox (beta): bump to 72.0b3
    -   [`fe23209`](https://github.com/kiss-community/repo/commit/fe23209)
        vim: bump to 8.1.2402
    -   [`2e98176`](https://github.com/kiss-community/repo/commit/2e98176)
        firefox: update comment
    -   [`535f2de`](https://github.com/kiss-community/repo/commit/535f2de)
        vim: bump to 8.1.2410
    -   [`c2301b5`](https://github.com/kiss-community/repo/commit/c2301b5)
        vim: bump to 8.1.2412
    -   [`7d4f45f`](https://github.com/kiss-community/repo/commit/7d4f45f)
        cbindgen: bump to 0.11.1
    -   [`87f0988`](https://github.com/kiss-community/repo/commit/87f0988)
        firefox (beta): bump to 72.0b4
    -   [`45d8cff`](https://github.com/kiss-community/repo/commit/45d8cff)
        vim: bump to 8.1.2414
    -   [`14572c2`](https://github.com/kiss-community/repo/commit/14572c2)
        cmake: bump to 3.16.1
    -   [`09bd41c`](https://github.com/kiss-community/repo/commit/09bd41c)
        git: bump to 2.24.1
    -   [`862fc01`](https://github.com/kiss-community/repo/commit/862fc01)
        vim: bump to 8.1.2421
    -   [`85767b0`](https://github.com/kiss-community/repo/commit/85767b0)
        firefox (beta): bump to 72.0b5
-   **Muhammad Herdiansyah**:
    -   [`59566ab`](https://github.com/kiss-community/repo/commit/59566ab)
        busybox: remove unneeded flag for acpid and add checks for
        directory files

## Community

-   **Cliford Sab**:
    -   [`4e106d8`](https://github.com/kiss-community/community/commit/4e106d8)
        xbacklight: new package at 1.2.3 (#94)
-   **Dylan Araps**:
    -   [`991ef70`](https://github.com/kiss-community/community/commit/991ef70)
        gnutls: bump to 3.6.11.1
    -   [`4a58f48`](https://github.com/kiss-community/community/commit/4a58f48)
        feh: bump to 3.3
    -   [`cb19f62`](https://github.com/kiss-community/community/commit/cb19f62)
        btrfs-progs: bump to 5.4
    -   [`4d6d033`](https://github.com/kiss-community/community/commit/4d6d033)
        go: bump to 1.13.5
    -   [`9360b07`](https://github.com/kiss-community/community/commit/9360b07)
        pandoc-bin: bump to 2.8.1
    -   [`6407a64`](https://github.com/kiss-community/community/commit/6407a64)
        weechat: bump to 2.7
-   **Jack Clarke**:
    -   [`9fc0328`](https://github.com/kiss-community/community/commit/9fc0328)
        kakoune: update to version 2019.12.10 (#97)
-   **James Davies**:
    -   [`3669446`](https://github.com/kiss-community/community/commit/3669446)
        Add qemu (#93)
-   **Sebastian Ertz**:
    -   [`889c36a`](https://github.com/kiss-community/community/commit/889c36a)
        bim: bump to 2.5.1 (#96)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
