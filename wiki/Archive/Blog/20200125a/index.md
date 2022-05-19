# 25/01/2020: This week in KISS (#8)

More fun stuff this week.

## Index

-   [Website redesign](#website-redesign)
-   [Packages page](#packages-page)
-   [Eudev can now be replaced](#eudev-can-now-be-replaced)
-   [Repology now tracks KISS maintainers](#repology-now-tracks-kiss-maintainers)
-   [Merchandise](#merchandise)
-   [sowm 1.2 released](#sowm-12-released)
-   [Official Repositories](#official-repositories)
-   [Community](#community)

## Website redesign

The first thing you will have noticed is that the website has had a
redesign. The idea behind it was to mimic a markdown/txt file while
keeping nice features like clickable links and images around.

-   Code blocks now feature a scroll bar if wider than the screen
    (*instead of wrapping into an unintelligible mess*).
-   The text width is now wider (*80 characters*) and the awful skinny
    column is gone.
-   The website still features a lightweight size, with no ads,
    tracking, js or cookies. Here's a speed test! [Pingdom results](https://tools.pingdom.com/#5bf78e6f4e400000)

## Packages page

Another new addition to the website is the [packages page](/packages).
This is a full listing of each package in the repositories with version
and maintainer information.

The page is updated automatically with changes to the repositories. The
raw repository data is also available as a simple `tsv` file.

-   Package listings: <https://getkiss.org/packages>
-   Raw data: <https://getkiss.org/packages/db.tsv>

## Eudev can now be replaced

This week I worked on making it possible to replace `eudev` with the
device manager of your choosing.

I am now happy to announce that I now run my system using busybox `mdev`
as my device manager. What's really neat is that I also managed to make
my system work without a device manager.

There are caveats to replacing udev, however. Xorg loses its ability to
automatically discover devices and libinput loses access to its
"Quirks" database.

If these don't bother you, I have written a Wiki page which explains
the process and includes all of the information you'll need.

-   Wiki: [Replacing eudev with mdev (or another device manager)](https://getkiss.org/wiki/replacing-eudev-with-mdev-(or-another-device-manager))

I'd like to thank [Michael Forney](https://github.com/michaelforney)
who maintains a [fork of libinput](https://github.com/oasislinux/libinput/tree/no-udev) which
makes udev an optional dependency.

## Repology now tracks KISS maintainers

The packaging hub [Repology.org](https://repology.org/) has tracked
KISS' repositories for a long while now. This week, support was added
to also track who maintains each package.

Each maintainer of a KISS package now has their own page on Repology
with additional feeds they are able to subscribe to. This eases the
[burden on myself to notify maintainers](https://github.com/kiss-community/community/issues?q=is%3Aissue+out+of+date+is%3Aclosed)
when their packages are out of date!

As an example, here is my Repology maintainer page:
[link](https://repology.org/maintainer/dylan.araps%40gmail.com)

I'd like to thank [Dmitry Marakasov](https://github.com/AMDmi3) for
providing this invaluable service and for his continued support of KISS.

## Merchandise

I have now included an additional method of showing your support to
KISS. One in which you receive something physical in return!

T-shirts and stickers are available in the following link and
feature... I'll let you decipher this puzzle.

-   [teespring](https://teespring.com/kiss0?pid=389)

Thanks for supporting KISS!

## sowm 1.2 released

The "Simple Opinionated Window Manager" received an update this week
to fix a widespread issue of keybindings not working on some systems.

This is a simple Window Manager I started working on a while ago which
sees a lot of use by users of KISS.

You can find the new release on GitHub in the link below.

-   <https://github.com/dylanaraps/sowm>

## Official Repositories

-   **Dylan Araps**:
    -   [`8b5f266`](https://github.com/kiss-community/repo/commit/8b5f266)
        libass: Remove fribidi dependency
    -   [`ee0f44e`](https://github.com/kiss-community/repo/commit/ee0f44e)
        qt5: Remove udev dependency
    -   [`b6494a9`](https://github.com/kiss-community/repo/commit/b6494a9)
        xorg-server: Make udev dependency optional
    -   [`1973da2`](https://github.com/kiss-community/repo/commit/1973da2)
        libinput: optional udev
    -   [`7b9d38a`](https://github.com/kiss-community/repo/commit/7b9d38a)
        libxkbcommon: move from community
    -   [`5086edb`](https://github.com/kiss-community/repo/commit/5086edb)
        qt5-webengine: Fix udev removal
    -   [`269b5ac`](https://github.com/kiss-community/repo/commit/269b5ac)
        bison: bump to 3.5.1
    -   [`de5f9f2`](https://github.com/kiss-community/repo/commit/de5f9f2)
        make: bump to 4.3
    -   [`0592cc4`](https://github.com/kiss-community/repo/commit/0592cc4)
        busybox: Add initial mdev
    -   [`41b37a9`](https://github.com/kiss-community/repo/commit/41b37a9)
        busybox: mdev support
    -   [`e33b642`](https://github.com/kiss-community/repo/commit/e33b642)
        busybox: Remove broken mdev rule
    -   [`ab39775`](https://github.com/kiss-community/repo/commit/ab39775)
        nss: Fix depends
    -   [`19829ea`](https://github.com/kiss-community/repo/commit/19829ea)
        baseinit: bump to 0.2.2
    -   [`906e3e7`](https://github.com/kiss-community/repo/commit/906e3e7)
        busybox: mdev: Fix /dev/snd
    -   [`d73defb`](https://github.com/kiss-community/repo/commit/d73defb)
        xf86-video-intel: Make eudev optional
    -   [`5edc08f`](https://github.com/kiss-community/repo/commit/5edc08f)
        sowm: bump to 1.1
    -   [`e12510b`](https://github.com/kiss-community/repo/commit/e12510b)
        libva: new package at 2.6.0
    -   [`1b6cee8`](https://github.com/kiss-community/repo/commit/1b6cee8)
        libva-utils: new package at 2.6.0
    -   [`96c0241`](https://github.com/kiss-community/repo/commit/96c0241)
        intel-vaapi-driver: new package at 2.4.0
    -   [`7b518cc`](https://github.com/kiss-community/repo/commit/7b518cc)
        intel-media-driver: new package at 19.4.0r
    -   [`3bc5d51`](https://github.com/kiss-community/repo/commit/3bc5d51)
        curl: Don't link to icu
    -   [`db94c86`](https://github.com/kiss-community/repo/commit/db94c86)
        kiss: bump to 0.70.0
    -   [`3dc27c4`](https://github.com/kiss-community/repo/commit/3dc27c4)
        kiss-utils: bump to 0.70.0
    -   [`45f92eb`](https://github.com/kiss-community/repo/commit/45f92eb)
        curl: don't link to libpsl
    -   [`8acef1f`](https://github.com/kiss-community/repo/commit/8acef1f)
        libva: bump to 2.6.1
    -   [`249a5fa`](https://github.com/kiss-community/repo/commit/249a5fa)
        python-mako: bump to 1.1.1
    -   [`0ce3c16`](https://github.com/kiss-community/repo/commit/0ce3c16)
        qt5: Fix libexec error
    -   [`9933167`](https://github.com/kiss-community/repo/commit/9933167)
        util-linux: bump to 2.35
    -   [`390d2f0`](https://github.com/kiss-community/repo/commit/390d2f0)
        qt5: Don't link against execinfo.h take two
    -   [`8c01495`](https://github.com/kiss-community/repo/commit/8c01495)
        cmake: bump to 3.16.3
    -   [`207b4c5`](https://github.com/kiss-community/repo/commit/207b4c5)
        dosfstools: new package at 4.1
    -   [`f3a6a38`](https://github.com/kiss-community/repo/commit/f3a6a38)
        mandoc: Fix build with new gnumake
    -   [`a870165`](https://github.com/kiss-community/repo/commit/a870165)
        nodejs: bump to 13.7.0
    -   [`ee8f593`](https://github.com/kiss-community/repo/commit/ee8f593)
        glib: bump to 2.63.4
    -   [`7f6c33c`](https://github.com/kiss-community/repo/commit/7f6c33c)
        git: Build with perl if available
    -   [`c64afb1`](https://github.com/kiss-community/repo/commit/c64afb1)
        mandoc: Simplify package and fix pointless error
    -   [`d7a4e9f`](https://github.com/kiss-community/repo/commit/d7a4e9f)
        gcc: fix libgomp relocation. Patch applied from @ioraff
    -   [`b257d85`](https://github.com/kiss-community/repo/commit/b257d85)
        sqlite: bump to 3.31.0
    -   [`ffcad57`](https://github.com/kiss-community/repo/commit/ffcad57)
        kiss: Track maintainers through CI
    -   [`1e33ac8`](https://github.com/kiss-community/repo/commit/1e33ac8)
        kiss: Track maintainers through CI
    -   [`818abe2`](https://github.com/kiss-community/repo/commit/818abe2)
        repo: Revert CI changes
    -   [`b690ba2`](https://github.com/kiss-community/repo/commit/b690ba2)
        nss: bump to 3.49.2
    -   [`f2aab2d`](https://github.com/kiss-community/repo/commit/f2aab2d)
        meson: bump to 0.53.1
    -   [`86d283c`](https://github.com/kiss-community/repo/commit/86d283c)
        docs: update
    -   [`65bd6ad`](https://github.com/kiss-community/repo/commit/65bd6ad)
        libevent: move to extra
    -   [`72be609`](https://github.com/kiss-community/repo/commit/72be609)
        falkon: Added optional open-in-mpv extension

## Community

-   **Aaron G**:
    -   [`d26891b`](https://github.com/kiss-community/community/commit/d26891b)
        neatvi: update to latest git (#238)
-   **Adam Schaefers**:
    -   [`863972b`](https://github.com/kiss-community/community/commit/863972b)
        new package: youtube-dl 2020.01.15
    -   [`bf615f9`](https://github.com/kiss-community/community/commit/bf615f9)
        new package dosfstools 4.1 (#239)
    -   [`5f38736`](https://github.com/kiss-community/community/commit/5f38736)
        new package: strace 4.1
    -   [`92e55a6`](https://github.com/kiss-community/community/commit/92e55a6)
        use git source
    -   [`0b0ca02`](https://github.com/kiss-community/community/commit/0b0ca02)
        rename to youtube-dl-git
    -   [`6b6f4f8`](https://github.com/kiss-community/community/commit/6b6f4f8)
        remove gawk dep from strace
    -   [`88f223e`](https://github.com/kiss-community/community/commit/88f223e)
        fix deps
    -   [`eb41e4b`](https://github.com/kiss-community/community/commit/eb41e4b)
        use "git" version, drop .git suffix
    -   [`25e3d86`](https://github.com/kiss-community/community/commit/25e3d86)
        remove unneccesary
    -   [`7beaa36`](https://github.com/kiss-community/community/commit/7beaa36)
        update chksm and build
    -   [`b28870a`](https://github.com/kiss-community/community/commit/b28870a)
        fix #257
    -   [`92b55df`](https://github.com/kiss-community/community/commit/92b55df)
        pkcs11-helper: bump to 1.26
-   **Cem Keylan**:
    -   [`d927e17`](https://github.com/kiss-community/community/commit/d927e17)
        sic-git: new package at git (#233)
    -   [`5f18842`](https://github.com/kiss-community/community/commit/5f18842)
        gnupatch: new package at 2.7.6
    -   [`70d390a`](https://github.com/kiss-community/community/commit/70d390a)
        vimb: new package at 3.6.0 (#244)
    -   [`c1ee5f2`](https://github.com/kiss-community/community/commit/c1ee5f2)
        fix https
    -   [`d8ed06d`](https://github.com/kiss-community/community/commit/d8ed06d)
        gnupatch: remove duplicate package
    -   [`1b4c1d3`](https://github.com/kiss-community/community/commit/1b4c1d3)
        pinentry-dmenu: new package at 0.1.1
    -   [`77febc9`](https://github.com/kiss-community/community/commit/77febc9)
        webkit2gtk: bump to 2.26.3
    -   [`bc94b84`](https://github.com/kiss-community/community/commit/bc94b84)
        vimb: run make with /usr prefix
    -   [`981b224`](https://github.com/kiss-community/community/commit/981b224)
        sic-git: change source
    -   [`921b818`](https://github.com/kiss-community/community/commit/921b818)
        parted: new package at 3.3 (#249)
-   **Cédric**:
    -   [`2ba8232`](https://github.com/kiss-community/community/commit/2ba8232)
        New package: tdb at 1.4.3
-   **Dylan Araps**:
    -   [`6b19de7`](https://github.com/kiss-community/community/commit/6b19de7)
        imagemagick: bump to 7.0.9-17
    -   [`206c82a`](https://github.com/kiss-community/community/commit/206c82a)
        libxkbcommon: move to official repositories
    -   [`9f43304`](https://github.com/kiss-community/community/commit/9f43304)
        sxiv: bump to 26
    -   [`acf4e65`](https://github.com/kiss-community/community/commit/acf4e65)
        tree: Fix mandir
    -   [`2056a5a`](https://github.com/kiss-community/community/commit/2056a5a)
        dosfstools: move to official repos
    -   [`dd3950a`](https://github.com/kiss-community/community/commit/dd3950a)
        docs: update
    -   [`9c4393a`](https://github.com/kiss-community/community/commit/9c4393a)
        pcre: Fix by @ioraff
    -   [`db8c71c`](https://github.com/kiss-community/community/commit/db8c71c)
        docs: update
    -   [`dc5b2c3`](https://github.com/kiss-community/community/commit/dc5b2c3)
        libevent: move to official repositories.
-   **Jonathan Dahan**:
    -   [`fea6437`](https://github.com/kiss-community/community/commit/fea6437)
        osh: bump to 0.7.pre11
-   **ioraff**:
    -   [`fb14a6a`](https://github.com/kiss-community/community/commit/fb14a6a)
        doas: fix kiss env (#237)
    -   [`5e9655a`](https://github.com/kiss-community/community/commit/5e9655a)
        doas: fix env and checksums (#240)
-   **tristelune1**:
    -   [`a1d1d4e`](https://github.com/kiss-community/community/commit/a1d1d4e)
        New package: fdm at 2.0 (#262)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
