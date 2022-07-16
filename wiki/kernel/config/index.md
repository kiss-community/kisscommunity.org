KERNEL CONFIGURATION GUIDE
==========================

Configuring the Linux kernel is arguably the hardest step in the installation
process. The kernel is humongous and figuring out what to enable in the
seemingly endless option list can be a daunting task.

The most important factor for success is how well one knows their hardware.
Spend a little time doing some research prior to configuring the kernel. Knowing
what is inside one's system is of immense value in all contexts.

The physical realm however, is only part of the equation. Configuration extends
to general features, file-systems, networking protocols, cryptography, security,
processor features and more.

This Wiki page will document kernel options, their requirement level
(conditional, recommended or mandatory), a brief description and a rationale if
necessary. Information about pre-built hardware as a whole will not be covered.


## [%[0.0]] Index

* [1.0](#1.0) Getting a config
* [2.0](#2.0) Modifying a config
* [3.0](#3.0) Busybox compatibility
* [4.0](#4.0) Never lose your .config ever again
* [5.0](#5.0) Removing the perl requirement


## [%[1.0]] Getting a config

The first step in this process is creating a .config file in the Linux source
tree. It is essentially just a text file containing KEY=value pairs (along with
comments), each of which control something in the linux build process.

An important subset of the options control "drivers"; sections of code that give
the kernel the capability to interact with filesystems, protocols and hardware
components. These options typically have three possible values: "n" to not
compile the driver, "y" to compile it into the kernel binary and "m" to compile
the driver as a module (.ko files stored in /usr/lib/modules). Modules can be
loaded/unloaded dynamically by the kernel as needed.

A fairly generic and compatible base configuration for your architecture can be
created by running the following command. This handles a large portion of the
work required during the configuration stage.

    $ make defconfig

There are countless flows of configuring the Linux kernel, and there are fun
things to try scattered all over the internet. Good luck!


## [%[2.0]] Modifying a config

There are several ways to modify an existing config file that are more
convenient than editing each of them by hand, most of them very well
documented. They arrange all of the config options in neat menus and submenus
and provide descriptions for each of them, allowing the Linux kernel to be
comprehended by mere mortals.

Terminal based configuration tools (requires ncurses)

    $ make menuconfig
    $ make nconfig

Graphical configuration tools (requires a working Xorg server and QT/GTK)

    $ make xconfig  # Requires qt5.
    $ make gconfig  # Requires gtk+3.

Another option you may find very useful to easily trim down general (default,
distro, etc.) configuration files is:

    $ make localyesconfig

This modifies the current .config to only compile whatever drivers are loaded in
the host kernel's current state. Running this after connecting all the hardware
you will be using is a pretty quick way to come up with a pretty lean
configuration.


## [%[3.0]] Package compatibility

Various parts of the Linux build system use non-standard options with core
utilities, this causes a build failure when using busybox. Thankfully, this non-
standard usage depends on unimportant and rarely used kernel features.

When these options are disabled (is the case by default unless 'allyesconfig' is
used), the kernel builds just fine.

The following options are mandatory (when using busybox) (=n).

* `CONFIG_IKHEADERS`: This option enables access to the in-kernel headers that
  are generated during the build process. These can be used to build eBPF
  tracing, or similar programs.

* `CONFIG_HAVE_GCC_PLUGINS`:  This option enables loadable modules that provide
  plugins for GCC which are useful for runtime instrumentation and static analysis.

Because gmp, mpc, and mpfr are bundled with our gcc instead of being built as
standalone packages, the headers are missing. This results in build failures
when building GCC Plugins. Either install gmp & mpc separately from gcc, or
disable `CONFIG_HAVE_GCC_PLUGINS` in the kernel config.


## [%[4.0]] Never lose your .config ever again

The kernel can be configured to store its configuration file to later make it
accessible via /proc/config.gz. Storing the .config in the kernel ensures that
you will never lose your config so long as you have its kernel.

The following options are recommended (=y).

* `CONFIG_IKCONFIG`:          Store the .config in the kernel.
* `CONFIG_IKCONFIG_PROC`:     Make the .config accessible as /proc/config.gz


## [%[5.0]] Removing the perl requirement

Perl is needed by the `build_OID_registry` script which will be executed during
the compilation process in most systems. This makes perl a mandatory dependency
to build the kernel.

A patch can be applied which adds a POSIX shell implementation of the perl
script. This fully removes the perl requirement.

@/[patches/kernel-no-perl.patch](/kernel/patches/kernel-no-perl.patch)  (Written by $/[E5ten](https://github.com/E5ten))
