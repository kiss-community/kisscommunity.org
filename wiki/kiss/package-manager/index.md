# KISS Package Manager

Some extra information which isn't available on <https://kisslinux.org/wiki/package-manager/>.

## [%[0.0]] Index

- [1.0](#1.0) Interesting Features
  - [1.1](#1.1) Runtime dependency detector built around 'ldd'
  - [1.2](#1.2) Fully dynamic (and automatic) alternatives system
  - [1.3](#1.3) 3-way handshake for files in /etc/
- [2.0](#2.0) Repositories
  - [2.1](#2.1) What is a repository?
  - [2.2](#2.2) Enabling a remote repository
  - [2.3](#2.3) Preventing a package from receiving updates
  - [2.4](#2.4) Package fallbacks
  - [2.5](#2.5) Bypassing KISS\_PATH
- [3.0](#3.0) Hook examples
  - [3.1](#3.1) Logging build duration
  - [3.2](#3.2) Setting the terminal title
  - [3.3](#3.3) Drop into shell on build fail
- [4.0](#4.0) Tips and Tricks
  - [4.1](#4.1) Swap grep implementations for a major speed up
  - [4.2](#4.2) Shallow cloning

## [%[1.0]] Interesting Features

### [%[1.1]] Runtime dependency detector built around 'ldd'

Dynamic dependencies brought in by build systems (which are missing from the
package's dependency list) are fixed on-the-fly by checking which libraries link
to the package's files.

This prevents an incomplete dependency list from causing system breakage as the
package manager is able to complete the list.

A lot of packages make use of this "implicit" to "explicit" dependency list
"conversion" to provide optional dependencies.

Example output:

    -> libXmu Checking for missing dependencies
    --- /home/dylan/conf/cache/kiss/build-4477/depends
    +++ depends
    @@ -1,3 +1,8 @@
    +libX11
    +libXau
     libXext
     libXt
    +libxcb
     xorg-util-macros make

### [%[1.2]] Fully dynamic (and automatic) alternatives system

Any file conflicts between two packages automatically become choices in the
alternatives system.

This allows one to swap providers of files without needing to explicitly
tell the package manager that two packages conflict, provide the same
utilities, etc.

In other words, no changes need to be made to packages. In fact, nothing
needs to be done at all. It's entirely automatic.

List available alternatives ('a' is an alias to 'alternatives'):

    $ kiss a
    gnugrep /usr/bin/grep
    ncurses /usr/bin/clear

Swap to GNU grep:

    $ kiss a gnugrep /usr/bin/grep
    -> Swapping '/usr/bin/grep' from busybox to gnugrep

Swap back to busybox grep:

    $ kiss a busybox /usr/bin/grep
    -> Swapping '/usr/bin/grep' from gnugrep to busybox

Swap to all alternatives for a given package (sbase for example):

    $ kiss a | grep ^sbase | kiss a -
    -> Swapping '/usr/bin/cat' from busybox to sbase
    -> Swapping '/usr/bin/cut' from busybox to sbase
    -> Swapping '/usr/bin/yes' from busybox to sbase
    ...

The above command works as the output of the alternatives listing is
directly usable as input to 'kiss a'.

### [%[1.3]] 3-way handshake for files in /etc/

Files in /etc/ are handled differently to those elsewhere on the system. A
reinstallation or update to a package will not always overwrite these files.

Instead, a 3-way handshake happens during installation to determine how the
new /etc/ file should be handled.

If the user has made modifications to the file and those modifications
differ to the to-be-installed package's file, the file is installed with the
suffix '.new'.

If the user hasn't touched the file, it will be automatically overwritten by
the package manager as it will contain updated/new contents..

If the user has touched the file but the file has not changed between
package versions, it will simply be skipped over.

## [%[2.0]] Repositories

Repository management in KISS is very simple. Repositories are configurable via
an environment variable. This environment variable can be set system-wide,
per-user, conditionally (via a script or program), for a single invocation, etc.

The environment variable is called `KISS_PATH` and is functionally identical to
the `$PATH` variable. A colon separated list of paths, in other words.

For example,
    $ KISS_PATH=/var/db/kiss/repo/core:/var/db/kiss/repo/extra

In the above example, two repositories are enabled (Core and Extra). The package
manager will search this list for packages in the order it is written.

Repositories can live anywhere on the system. In your `$HOME` directory,
somewhere system-wide in '/', etc. The only requirement is that a full path be
used.

### [%[2.1]] What is a repository?

A KISS repository is simply a directory of directories. The quickest way to
get started is as follows.

Create the repository:

    $ mkdir -p repo
    $ cd repo

Let's "fork" a few packages into our new repository.

    $ kiss fork curl
    $ kiss fork xz
    $ kiss fork zlib

This is now a fully usable repository and it can be added to your `KISS_PATH`.

### [%[2.2]] Enabling a remote repository

Let's assume that our `KISS_PATH` matches the above example (Core and Extra).
As an example, we'll be enabling the Community repository. First, clone it:

    # This can live anywhere on the system.
    $ git clone https://codeberg.org/kiss-community/community

Now, enable the repository:

    $ export KISS_PATH=$KISS_PATH:/path/to/community/community

### [%[2.3]] Preventing a package from receiving updates

Preventing a package from receiving updates can be accomplished in a myriad
of different ways. The easiest method is to leverage a user repository.

Create a new repository:
    $ mkdir -p no_updates
    $ cd no_updates
Copy the package to the new repository:
    $ cp -r /var/db/kiss/installed/PKG_NAME /path/to/no_updates
Add the new repository to the **START** of your `KISS_PATH`:
    $ export KISS_PATH=/path/to/no_updates:$KISS_PATH

The package manager will search `KISS_PATH` in order. It will see that the
no\_updates repository provides PKG\_NAME and the version matches that which
is installed. No updates will again happen for the package.

### [%[2.4]] Package fallbacks

If you would like to package something in your own repository but would
like the package manager to prefer other repositories before yours, simply
add your repository to the end of `KISS_PATH`.

The moment that your package is available elsewhere, the package manager
will prefer the new location to yours. The list is searched (in order) and
the first match is picked.

### [%[2.5]] Bypassing KISS\_PATH

There is a special case where one can bypass the regular KISS\_PATH for a
single invocation of the package manager. This has been called "CRUX-like
usage" by users.

    $ cd /path/to/myrepo/firefox
    $ kiss b
    $ kiss i

As seen above, various package manager commands will work without arguments,
so long as you are in a package's repository directory. This will prepend
the current directory to '$KISS\_PATH' _only_ for this invocation.

## [%[3.0]] Hook examples

### [%[3.1]] Logging build duration

This hook adds a new message post-build with the total build duration in a
human readable format (00h 00m). Similar code is used in the boot process
of the system to calculate boot time.

    PKG="$2"
    
    case $1 in
        pre-build)
            cat /proc/uptime > "${KISS_TMPDIR:-/tmp}/_kiss_start"
        ;;
        
        post-build)
            IFS=. read -r _start _ < "${KISS_TMPDIR:-/tmp}/_kiss_start"
            IFS=. read -r _end _ < /proc/uptime
            
            rm -f "${KISS_TMPDIR:-/tmp}/_kiss_start"
            
            (
                _s=$((_end - _start))
                _h=$((_s / 60 / 60 % 24))
                _m=$((_s / 60 % 60))
                
                [ "$_h" = 0 ] || _u="${_u}${_h}h "
                [ "$_m" = 0 ] || _u="${_u}${_m}m "
                
                printf "-> %s %s\n" "$PKG" "Build finished in ${_u:-${_s}s}"
            )
        ;;
    esac

### [%[3.2]] Setting the terminal title

This hook uses the Xterm escape sequence to change the terminal title, which
is supported by most modern terminal emulators. The title will include the
name of the package currently being build, the position in the batch and the
total amount of packages to be built. That way it's easy to keep track of
build progress, without having to scroll past a wall of compiler output.

    case $1 in
        queue-status|queue)
            [ -t 2 ] && {
                printf '\033]0;kiss: %s (%d/%d)\a' \
                    "$2" "${3:-?}" "${4:-?}" >&2
            }
        ;;
    esac




### [%[3.3]] Drop into shell on build fail

    case $1 in
        build-fail)
            printf "-> %s %s\a\n" "$2" "Dropped into shell"
            sh >/dev/tty
        ;;
    esac


## [%[4.0]] Tips and Tricks

A lot of the package manager's features are hard to discover or otherwise
non-obvious to its users. This section will document these features, how to use
them and the benefits they bring.

### [%[4.1]] Swap grep implementations for a major speed up

The default grep implementation in KISS is busybox grep. This version of
grep works very well and supports a large number of features. The one issue
is that it is painfully slow when compared to other popular implementations.

A fairly major speedup can be attained by swapping to a different grep via
the alternatives system. The fastest grep implementation around is GNU grep
which is available in Community as 'gnugrep'.

    $ kiss b gnugrep && kiss i gnugrep
    $ kiss a gnugrep /usr/bin/grep

### [%[4.2]] Shallow cloning

By default, the package manager performs a shallow clone of the remote
repository, branch, or commit whenever possible. This is to speedup cloning,
and for most packages does not alter the package building process. This
shallow cloning is done in a way which still allows `git describe`.

For packages which require submodules, add `git submodule update --init` to
pull in the required submodules.
