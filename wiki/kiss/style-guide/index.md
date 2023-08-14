PACKAGE STYLE GUIDE
===================

This document is a style guide which will double as documentation for a possible
package linter in the future. Every package in the Official repositories and the
Community repository adheres to this style guide.

NOTE: Exceptions are made where it makes sense.

## Index

- [MAINTAINERSHIP](#MAINTAINERSHIP)
- [GENERAL](#GENERAL)
- [BUILD](#BUILD)
  - [GNU AUTOTOOLS](#GNU AUTOTOOLS)
  - [MESON](#MESON)
  - [CMAKE](#CMAKE)
  - [MAKE](#MAKE)
  - [RUST](#RUST)
  - [GO](#GO)
  - [PYTHON](#PYTHON)
- [DEPENDS](#DEPENDS)
- [SOURCES](#SOURCES)
- [VERSION](#VERSION)
- [PATCHES](#PATCHES)


## %[MAINTAINERSHIP]

* Each package has a set maintainer stored via git commits. Use 'git log' or
  'kiss-maintainer pkg' to find the maintainer's contact information.

* Only the maintainer of a package has the ability to make changes to said
  package. Any pull requests by a non-maintainer for a package will be closed.

* If you would like to make a change to an existing package, contact the
  maintainer and they will do so on your behalf.

* If the maintainer leaves a package out of date and does not respond in a
  reasonable time frame, the package will be orphaned and up for grabs.

* If no one steps forward to adopt an orphaned package, it will be dropped from
  the repositories.


## %[GENERAL]


%[0000]

Some packages are not suitable for inclusion in the Community repository.

Examples: ConsoleKit, dbus, electron, gettext, gtk2, intltool, libsn,
logind, pam, python2, polkit, pulseaudio, systemd and all Desktop Environments.

The same rules above may apply to other software at the discretion of
maintainers.


%[0001]

Packages which are binaries must contain the suffix '-bin' to reflect
this fact. Similarly, packages which pull from git should contain the
suffix '-git'. The version of git packages must also be set to 'git'.



## %[BUILD]


%[0200]

This guide should be used alongside shellcheck and not in place of it.


%[0201]

All shell code must pass the shellcheck linter. Any false-positives or
intended behavior must have a rationale attached with the exclusion.

    # Disable warning as CFLAGS must work this way.
    # shellcheck disable=2086
    "${CC:-cc}" $CFLAGS ...


%[0202]

Use 4 spaces for indentation.


%[0203]

Lines should not exceed 80 characters in length.


%[0204]

All packages must use the POSIX shell shebang with '-e' to exit on error.
Additionally, '-ef' can be used if word-splitting is required.

There must also be a blank line directly below the shebang.

    #!/bin/sh -e
    
    # Code starts here.


%[0205]

All comments should start with a capital letter and use proper spelling,
grammar and punctuation.

    # This is a comment.


%[0206]

Leave comments to explain *why* the code is needed and not *what* it does.

Bad:

    # Create a directory.
    mkdir -p "$1/usr/bin"

Good:

    # 'make install' doesn't create the directory.
    mkdir -p "$1/usr/bin"


%[0207]

Avoid adding braces around variables if unneeded.

    Bad:  printf '%s\n' "${var}"
    Good: printf '%s\n' "$var"
    Good: printf '%s\n' "${var}.${var2}"


%[0208]

Avoid quotes when unneeded.

    Bad:  [ "$var" = "test" ]
    Good: [ "$var" = test ]
    
    Bad:  cp "file" "$1/usr/bin/file"
    Good: cp file "$1/usr/bin/file"


%[0209]

Quote entire strings instead of variables.

    Bad:  cp -f cat "$1"/usr/bin/cat
    Good: cp -f cat "$1/usr/bin/cat"


%[0210]

Align arguments in blocks of command calls.

Bad:

    cp file.h "$1/usr/include/file.h"
    cp libfile.so "$1/usr/lib/libfile.so"

Good:

    cp file.h     "$1/usr/include/file.h"
    cp libfile.so "$1/usr/lib/libfile.so"


%[0211]

Use `mkdir` and `cp` instead of `install`.

Bad:

    install -Dm755 ls "$1/usr/bin/ls"

Good:

    mkdir -p "$1/usr/bin"
    cp ls "$1/usr/bin/"

NOTE: since Dylan wrote this style guide, he changed opinions on this point
since install isn't POSIX. Both styles are accepted in the community repo.


%[0212]

Prefer `$CC` to ...

    Bad:  gcc -o file file.c
    Good: "${CC:-cc}" -o file file.c


%[0213]

Always use `-p` with `mkdir`.


%[0214]

Always use `printf`. Do not use `echo`.



### %[GNU AUTOTOOLS]


%[0400]

Use the following style:

    ./configure \
        --prefix=/usr \
        --more_args_here
    
    make
    make DESTDIR="$1" install


%[0401]

Avoid running ./autogen.sh, autoreconf or similar tools prior to starting
the build process. If there are no pre-generated configure or Makefiles, an
alternate source must be sought.

An exception can be made for packages in which no such source exists. If
autogen.sh or autoreconf are required, prefer autoreconf.



### %[MESON]


%[0600]

Use the following style:

    export DESTDIR="$1"
    
    meson setup \
        -Dprefix=/usr \
        -Dexample=false \
        output
    
    ninja -C output
    ninja -C output install



### %[CMAKE]


%[0800]

Use the following style:

    export DESTDIR="$1"
    
    cmake -B build \
        -DCMAKE_INSTALL_PREFIX=/usr \
        -DFLAG=1
    
    cmake --build   build
    cmake --install build



### %[MAKE]


%[1000]

Use one of the following style when applicable:

    make
    make DESTDIR="$1" PREFIX=/usr install
    
    
    make PREFIX=/usr
    make DESTDIR="$1" install
    
    
    make PREFIX=/usr
    make DESTDIR="$1" PREFIX=/usr install


For packages which require a few variables be set, prefer this style.

    make \
        PREFIX=/usr \
        SBINDIR=/usr/bin \
        OPT="$CFLAGS"
    
    make \
        DESTDIR="$1" \
        PREFIX=/usr \
        install


For packages which require the variables be set for all calls to make,
prefer this style.

    mk() {
        make \
             PREFIX=/usr \
             DESTDIR="$1" \
             EXAMPLE=1 \
             "$@"
    }
    
    mk
    mk install



### %[RUST]


%[1050]

Use the following style:

    cargo build --release
    
    install -Dm755 target/release/rg "$1/usr/bin/rg"



### %[GO]


%[1100]

Use the following style:

    export GOPATH="$PWD/go"
    export GO111MODULE=on
    
    go build \
        -modcacherw \
        -trimpath
    
    install -Dm755 lazygit "$1/usr/bin/lazygit"

NOTE: If the directory 'vendor' is available in the root directory of the
source, the preferred method is to omit GOPATH and GO111MODULE and use:

    go build \
       -mod=vendor \
       -further-options

to prevent cluttering $HOME and enable offline building.

### %[PYTHON]


%[1150]

Use the following style:

    python setup.py build
    python setup.py install --prefix=/usr --root="$1"



## %[DEPENDS]


%[1201]

If dependency is unneeded, then it must be removed.


%[1202]

Some packages are assumed to always be available. Such dependency must be
removed.

Examples: gcc, make, musl.


%[1203]

Build-time dependencies must be marked as 'make' dependencies.

Examples: autoconf, automake, cmake, meson.


%[1204]

Runtime dependencies must not be marked as 'make' dependencies.


%[1205]

The depends file must be sorted.


%[1206]

If depends file is empty, then it must be removed.



## %[SOURCES]


%[1401]

Use a HTTPS source if at all possible.


%[1402]

Don't specify patches remotely. Store them as a part of the package's
repository files.

    Bad:  https://example.com/fix-build.patch
    Good: patches/fix-build.patch


%[1403]

Don't use a git repository in place of a release tarball unless it makes
sense to do so.


%[1404]

Drop www. and .git from all sources if possible.



## %[VERSION]


%[1601]

Package version must be latest upstream version.


%[1602]

Use 'git' in place of '9999'.


%[1603]

The version file must contain relative version number.

    Bad:  1.0.0
    Good: 1.0.0 1



## %[PATCHES]


%[1800]

Use the following style:

    patch -p1 < patch.patch
    
    # If there is more than one patch.
    for patch in *.patch; do
        patch -p1 < "$patch"
    done


%[1801]

All patches should use the same strip amount. If this is not possible,
modify the patches. Strip amount is controlled by the -p flag.
