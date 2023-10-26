# Frequently Asked Questions

Many people who install KISS come across similar problems and misunderstandings
in the process. Almost all of these have solutions documented somewhere in the
KISS documentation, but it can be spread out, hard to find, and easy to miss.
Therefore, this page collects solutions to some of the most common problems.

**This is not a substitute for a thorough reading of the
[install guide](https://kisslinux.org/install) and the appropriate
[wiki](https://kisslinux.org/wiki/) page.**

This page does not answer questions about the philosophy of KISS, or why KISS
is designed in any certain way. For those questions, refer to <https://kisslinux.org/answers>.

## [%[000]] General tips for identifying build errors

If you use parallel make (`make -jN`), the actual error probably isn't at the
bottom of the log. You'll need to look back through it, and find the first
occurence of "Waiting for unfinished jobs....".

Try to find the particular command which failed (make gives you a file and line
number), and see if you can reproduce the error by running that command by itself.

Often you might be missing a hidden dependency. Look for errors like "not found"
or "no such file or directory".

Make sure your CFLAGS are like `-O2` not `-02` (letter O not number 0).

Search online for the error message. Look through [issues in the community
repo](https://codeberg.org/kiss-community/community/issues), in case someone's
encountered it before.

If you need more help, the best place is IRC. Upload a *full* log to a pastebin.

Once you've found the solution, make a note of it so that others can learn. You
could contribute it to this page.

## [%[010]] My kernel doesn't build!

### [%[011]] Busybox diff given unrecognized options
These are not causing the build to fail; they are only warnings.

### [%[012]] Errors about `__always_inline`, versions 5.12-5.18
Kernels with minor version 5.12-5.18 require the following patch to add an include:

	$ sed -i '/<stdlib.h>/a #include <linux/stddef.h>' tools/objtool/arch/x86/decode.c

### [%[013]] `env: can't execute 'bash': No such file or directory`, versions 5.19 and 6.0
Kernels version 5.19 and 6.0 require bash to be built. There is a
patch by [$/ioraff](https://codeberg.org/ioraff) available
[here](https://codeberg.org/kiss-community/repo/issues/79) to remove this dependency.
Kernels 6.1 and later have had the patch merged into them already.

## [%[020]] Kernel config/boot problems

The kernel not booting can be a variety of issues. This is almost always
related to a configuration issue in the kernel or the bootloader.

KISS doesn't use an initramfs by default so the configuration of the kernel
may have different requirements from other distributions.

### [%[021]] Essential drivers
Make sure you've enabled drivers for at least your boot and root filesystems,
disk controller, and drives. They should be set to `=y` in your .config or `[*]`
when using make menuconfig. Essentially, every driver the kernel requires to
detect and mount the drive containing the root filesystem, must be built as a
part of the kernel binary (rather than as modules).

### [%[022]] Including firmware
Choose some location, such as `/usr/lib/firmware` and install the firmware you need into it.
This alone isn't enough; you need to tell the kernel the directory where to find firmware, and
the filenames relative to this directory for everything you want to use.
See [kernel/firmware](/kernel/firmware/) for details.

Firmware problems are most easily diagnosed by looking through `dmesg`.

### [%[023]] initramfs
KISS technically supports booting via an initramfs, it just doesn't require
or provide one. As a user you have the means to set this up yourself for
your system. A simple one is [tinyramfs](https://github.com/illiliti/tinyramfs).

Full disk encryption is also possible without the use of an initramfs in
modern kernels (see `dm-mod.create`).

## [%[100]] Software

### [%[110]] Is *SOFTWARE* packaged?

To quickly check through all the KISS repositories which exist, you can use the
`kiss-find` tool:

    $ kiss find music
    gnome-music          42.1 1        https://github.com/mdartmann/mkiss.git        gnome/gnome-music         main    "Mae Dartmann"
    io.elementary.music  5.0.5 1       https://github.com/eudaldgr/elementaKISS.git  apps/io.elementary.music  master  "Eudald Gubert i Roldan"
    texlive-music        2022.62533 1  https://github.com/ehawkvu/kiss-tex.git       texlive/texlive-music     master  "Ethan"
    zmusic               1.1.8 1       https://github.com/sdsddsd1/kiss-games.git    equipment/zmusic          master  "Claudia"

kiss-find is packaged in the community repo, or available [here](https://github.com/aabacchus/kiss-find).

### [%[120]] Can you package *SOFTWARE* for me?

Do it yourself!

### [%[130]] Why isnt my mouse/keyboard working on tinyx?

You lack the correct drivers.
Using PS/2 mouse and keyboard drivers however, seems to be what works for most users.

### [%[140]] Can I create a KISS linux live USB?

yes, you can. Have a look at [kiss-community/kiss-live](https://github.com/kiss-community/kiss-live).
