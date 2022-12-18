KISS Linux Community Installation Guide
=======================================

Since Dylan is currently on a hiatus, the KISS community is maintaining a set
of repos and a fork of the package manager. We have made enough minor changes
to the system that some differences to the install process should be noted.
Dylan's page (<https://kisslinux.org/install.html>) is still the canonical
reference. This page lists the differences to the official guide.

If you run into any problems, please join us in IRC (`#kisslinux` in
libera.chat) and ask.

- - -

## [%[001]] Tarball

(Official guide steps 001-005)

You should start with the updated rootfs tarball from the
[latest release](https://codeberg.org/kiss-community/repo/releases) which is
currently
[22.11.15](https://codeberg.org/kiss-community/repo/releases/tag/22.11.15).
Make sure you extract it *as root*. The tarball is not signed so step 004
doesn't apply. You should still verify the checksums though.

**NOTE** that the current release has a bug in the tarball; there are details
on the release page for the simple fix.

## [%[002]] Repos

(Official guide steps 007-009)

The core repos should be cloned from <https://codeberg.org/kiss-community/repo>.
For example, you might want to do something like this:

    $ mkdir ~/repos
    $ cd ~/repos
    $ git clone https://codeberg.org/kiss-community/repo
    $ export KISS_PATH="$HOME/repos/repo/core:$HOME/repos/repo/extra:$KISS_PATH"

You can put the repos wherever you like; `~/repos` is just an example.
Note that you should set `KISS_PATH` in your `.profile` so that it is set every
time you log in, rather than having to run the last line every time.

To make sure that kiss can find these packages, you can run
    $ kiss s \*
(`*` needs to be escaped so that it isn't used as a glob for all the files in
your current working directory). The command should output every package found
in `$KISS_PATH` as well as all installed packages (listed in `/var/db/kiss/installed`).
Check that the paths like `~/repos/repo/core/...` show up.

We also maintain a community repo with many more packages than are found in
repo. You will probably want to use this; it can be found at
<https://codeberg.org/kiss-community/community> and enabled similarly to above.

## [%[003]] Commit signing

(Official guide steps 010-013)

`gnupg1` used to be used for signature verification but now commits are signed
with ssh (only for `repo`). To enable verification, run:

    $ cd /path/to/repo
    $ git config gpg.ssh.allowedSignersFile .allowed_signers
    $ git config merge.verifySignatures true

## [%[004]] Kernel

(Official guide step 018)

There are a number of patches which may need to be applied to the kernel
depending on your version. Check the [FAQ page](/FAQ/#010) for details.
