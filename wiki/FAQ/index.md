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

### [%[013]] `env: can't execute 'bash': No such file or directory`, version 5.19
Kernels version 5.19 and 6.0 currently require bash to be built. There is a
patch by [$/ioraff](https://codeberg.org/ioraff) available
[here](https://codeberg.org/kiss-community/repo/issues/79) to remove this dependency.


## [%[020]] Kernel config/boot problems

### [%[021]] Filesystem drivers
Make sure you've enabled drivers for at least your boot and root filesystems.

### [%[022]] Including firmware
Choose some location, such as `/usr/lib/firmware` and install the firmware you need into it.
This alone isn't enough; you need to tell the kernel the directory where to find firmware, and
the filenames relative to this directory for everything you want to use.
See [kernel/firmware](/kernel/firmware/) for details.

Firmware problems are most easily diagnosed by looking through `dmesg`.
