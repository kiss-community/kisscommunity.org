FIRMWARE
========

Linux firmware is a package distributed alongside the Linux kernel that contains
firmware binary blobs necessary for partial or full functionality of certain
hardware devices. These binary blobs are usually proprietary because some
hardware manufacturers do not release source code necessary to build the
firmware itself.

This Wiki page will document firmare/driver configuration for various
peripherals, their requirement level (conditional, recommended or mandatory), a
brief description and a rationale if necessary.


## [%[0.0]] Index

* [1.0](#1.0) Overview
  * [1.1](#1.1) Incorporating Firmware
  * [1.2](#1.2) Rebuilding the Kernel
* [2.0](#2.0) Processor
  * [2.1](#2.1) AMD Microcode
  * [2.2](#2.2) Intel Microcode
* [3.0](#3.0) Graphics
  * [3.1](#3.1) NVIDIA
  * [3.2](#3.2) AMDGPU
* [4.0](#4.0) Wireless
  * [4.1](#4.1) Intel (iwlwifi)
* [5.0](#5.0) Bluetooth
* [6.0](#6.0) Sound


## [%[1.0]] Overview

The following are considered some best practices when configuring firmware for
peripherals.


## [%[1.1]] Incorporating Firmware

When building drivers into the kernel, ensure that the firmware blobs
(\*.ucode files) are referenced and the firmware root directory is set.

Replace '\*\*\*\*.ucode' with the firmware you would like to bake into the
kernel. Values are paths to files, separated by spaces with locations
relative to the value of `CONFIG_EXTRA_FIRMWARE_DIR`.

    +--------------------------------------------------------------------------+
    |   ".config" Example                                                      |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   CONFIG_EXTRA_FIRMWARE_DIR="/lib/firmware"                              |
    |   CONFIG_EXTRA_FIRMWARE="****.ucode"                                     |
    |                                                                          |
    +--------------------------------------------------------------------------+

If you are using the menuconfig tool, it should look something like the
following:

    +--------------------------------------------------------------------------+
    |   "menuconfig" Example                                                   |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   Device Drivers  --->                                                   |
    |     Generic Driver Options  --->                                         |
    |       Firmware loader --->                                               |
    |         -*- Firmware loading facility                                    |
    |         (****.ucode) Build named firmware blobs into the kernel binary   |
    |         (/lib/firmware) Firmware blobs root directory                    |
    |                                                                          |
    +--------------------------------------------------------------------------+

Note: The `CONFIG_EXTRA_FIRMWARE` should be a list of all of the required
firmware blobs, delimited by a single space character.


## [%[1.2]] Rebuilding the Kernel

Configuring a kernel is difficult and everyone is bound to make a few
mistakes or forget a step in the process.. fear not!  The road to "recovery"
is quick and painless.

The process after updating the .config file with the required changes would
be as follows:

    +--------------------------------------------------------------------------+
    | Rebuild the Kernel                                                       |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ make -j "$(nproc)" && make modules_install                           |
    |                                                                          |
    +--------------------------------------------------------------------------+
    | Remount the boot partition                                               |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ mount /boot                                                          |
    |                                                                          |
    +--------------------------------------------------------------------------+
    | Install the built kernel (to /boot). (Ignore the LILO error).            |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ make install                                                         |
    |                                                                          |
    +--------------------------------------------------------------------------+
    | Rename the kernel/system.map (vmlinuz -> vmlinuz-VERSION).               |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ mv /boot/vmlinuz    /boot/vmlinuz-VERSION                            |
    |   $ mv /boot/System.map /boot/System.map-VERSION                         |
    |                                                                          |
    +--------------------------------------------------------------------------+
    | Update the boot loader (assuming using GRUB2)                            |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ grub-mkconfig -o /boot/grub/grub.cfg                                 |
    |                                                                          |
    +--------------------------------------------------------------------------+
    | Reboot for the new kernel configuration to take effect:                  |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ reboot                                                               |
    |                                                                          |
    +--------------------------------------------------------------------------+


## [%[2.0]] Processor

The following sections describe the kernel requirements for microcode loading
for various manufacturers.


## [%[2.1]] AMD Microcode

Microcode updates for AMD processors are provided by linux-firmware
package.  [AMD specific microcode](https://wiki.gentoo.org/wiki/AMD_microcode) is located in the amd-ucode/ and amd/
folders.

In order determine which microcode firmware blob is required, you can use
grep to search for the "cpu family" value in /proc/cpuinfo:

    +--------------------------------------------------------------------------+
    |                                                                          |
    |    $ grep -F -m 1 "cpu family" /proc/cpuinfo                             |
    |                                                                          |
    +--------------------------------------------------------------------------+

Use the output from the command above to determine which firmware blob file
is required below:

    +---------------------------------+---------+------------------------------+
    |  File(s)                        |   Dec.  |   CPU Family Name            |
    +---------------------------------+---------+------------------------------+
    |                                 |         |                              |
    |  microcode_amd.bin              |   16    |   K10                        |
    |                                 |   17    |   Turion                     |
    |                                 |   18    |   Llano, Fusion              |
    |                                 |   20    |   Bobcat                     |
    |                                 |         |                              |
    |  microcode_amd_fam15h.bin       |   21    |   Bulldozer, Piledriver,     |
    |                                 |         |   Steamroller, Excavato      |
    |                                 |         |                              |
    |  microcode_amd_fam16h.bin       |   22    |   Jaguar, Puma               |
    |                                 |         |                              |
    |  microcode_amd_fam17h.bin       |   23    |   Zen                        |
    |  amd_sev_fam17h_model0xh.sbin   |         |                              |
    |                                 |         |                              |
    +---------------------------------+---------+------------------------------+

Remember to reference the firmware blobs in `CONFIG_EXTRA_FIRMWARE`. \[[1.1](#1.1)\]


## [%[2.2]] Intel Microcode

Microcode updates for Intel processors are provided by the
"[Intel-Linux-Processor-Microcode-Data-Files](https://github.com/intel/Intel-Linux-Processor-Microcode-Data-Files)" package and located in the
intel-ucode/ folder.

In order [determine which microcode firmware blob is required](https://github.com/intel/Intel-Linux-Processor-Microcode-Data-Files/issues/16), you can use
grep to search for "cpu family", "model" and "stepping" values in
/proc/cpuinfo:

    +--------------------------------------------------------------------------+
    |                                                                          |
    |    $ grep -F -m 1 "cpu family" /proc/cpuinfo                             |
    |    $ grep -F -m 1 "model" /proc/cpuinfo                                  |
    |    $ grep -F -m 1 "stepping" /proc/cpuinfo                               |
    |                                                                          |
    +--------------------------------------------------------------------------+

Use the outputed values (converted to Hex) from the commands above to
determine which firmware blob file is required by using the following naming
convention:

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   [cpu_family]-[model]-[stepping]                                        |
    |                                                                          |
    +--------------------------------------------------------------------------+

Note: If converting to Hex isn't your think, user $/[illiliti](https://github.com/illiliti) has provided an
example POSIX compliant shell script that can do this for you
"automagically":

    +--------------------------------------------------------------------+
    |                                                                    |
    |   #!/bin/sh -f                                                     |
    |   while IFS=: read -r key val; do                                  |
    |       case $key in                                                 |
    |           stepping*)   : ${stepping:=$val} ;;                      |
    |           cpu*family*) : ${family:=$val}   ;;                      |
    |           model*)      : ${model:=$val}    ;;                      |
    |       esac                                                         |
    |   done < /proc/cpuinfo                                             |
    |   printf "%02x-%02x-%02x\n" "$family" "$model" "$stepping"         |
    |                                                                    |
    +--------------------------------------------------------------------+

Remember to reference the firmware blobs in `CONFIG_EXTRA_FIRMWARE`. \[[1.1](#1.1)\]


## [%[3.0]] Graphics

The following sections describe the kernel requirements for graphics cards from
various manufacturers.


## [%[3.1]] NVIDIA

(this is a placeholder)


## [%[3.2]] AMDGPU

Setting up a system to use AMDGPU requires identifying the proper card,
installing the corresponding firmware, configuring the kernel, and
installing the X11 driver.

Begin by identifying the family and chipset of your AMDGPU:

    +--------------+-------------------------+---------------------------------+
    |   Family     |   Chipset               |   Product Name                  |
    +--------------+-------------------------+---------------------------------+
    |              |                         |                                 |
    |   Southern   |   CAPE VERDE,           |   HD7750-HD7970, R9 270,        |
    |   Island     |   PITCAIRN, TAHITI,     |   R9 280, R9 370X, R7 240,      |
    |              |   OLAND, HAINAN         |   R7 250                        |
    |              |                         |                                 |
    |   Sea        |   BONAIRE, KABINI,      |   HD7790, R7 260, R9 290,       |
    |   Island     |   KAVERI, HAWAII,       |   R7 360, R9 390                |
    |              |   MULLINS               |                                 |
    |              |                         |                                 |
    |   Volcanic   |   CARRIZO, FIJI,        |   R9 285, R9 380, R9 380X,      |
    |   Island     |   STONEY, TONGA,        |   R9 Fury, R9 Nano,             |
    |              |   TOPAZ, WANI           |   R9 Fury X, Pro Duo            |
    |              |                         |                                 |
    |   Arctic     |   POLARIS10/11/12       |   RX 460, RX 470, RX 480,       |
    |   Island     |                         |   RX 540, RX 550, RX 560,       |
    |              |                         |   RX 570, RX 580, RX 590        |
    |              |                         |                                 |
    |   Vega       |   VEGA10/11/12/20,      |   RX Vega 56, RX Vega 64,       |
    |              |   RAVEN                 |   Raven Ridge APU series5,      |
    |              |                         |   Radeon Vega II, Radeon VII    |
    |              |                         |                                 |
    |   Navi       |   NAVI10                |   RX 5500, RX 5500 XT,          |
    |              |                         |   RX 5600, RX 5600 XT,          |
    |              |                         |   RX 5700, RX 5700 XT           |
    |              |                         |                                 |
    +--------------+-------------------------+---------------------------------+

For more information on each chipset, refer to the [Gentoo AMDGPU Wiki](https://wiki.gentoo.org/wiki/AMDGPU).

The kernel can now be configured based on the information obtained above:

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   The following options are required (=y).                               |
    |                                                                          |
    |   CONFIG_MTRR                 Memory Type Range Register Support         |
    |   CONFIG_DRM_FBDEV_EMULATION  Direct Rendering Manager                   |
    |   CONFIG_DRM_AMDGPU                                                      |
    |   CONFIG_DRM_AMDGPU_SI        Support for SI parts                       |
    |   CONFIG_DRM_AMDGPU_CIK       Support for CIK parts                      |
    |                               (only for Sea Islands GPUs with the amdgpu |
    |                               driver)                                    |
    |   CONFIG_DRM_AMD_ACP          AMD Audio CoProcessor IP support           |
    |                               (only needed for APUs)                     |
    |   CONFIG_DRM_AMD_DC           AMD DC - Enable new display engine         |
    |   CONFIG_DRM_AMD_DC_DCN       DCN 1.0 Raven family                       |
    |                               (only Vega RX as part of Raven Ridge APUs) |
    |   CONFIG_HSA_AMD              HSA kernel driver for AMD GPU devices      |
    |   CONFIG_DRM_PANEL                                                       |
    |                                                                          |
    +--------------------------------------------------------------------------+

Note: When using AMDGPU, it is [recommended](https://wiki.gentoo.org/wiki/AMDGPU) to unset the ATI Radeon option so
that the radeon module is not built.

Remember to reference the firmware blobs, per Section \[[1.1](#1.1)\]. The correct
AMDGPU firmware blobs can be found in the amdgpu/ folder of the
linux-firmware package. For example, if I was using a GPU with the TONGA
chipset, I would want to reference all amdgpu/tonga_\* files.


## [%[4.0]] Wireless Devices

The following sections describe the kernel requirements for wireless devices
from various manufacturers.


## [%[4.1]] Intel (iwlwifi)

Determine which module your wireless device uses (iwldvm or iwlmvm), along
with which firmware (iwlwifi-\*\*\*\*.ucode) your device requires.

* <https://wireless.wiki.kernel.org/en/users/drivers/iwlwifi>

Once determined, ensure that the following kernel requirements are met:

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   The following options are required (=y).                               |
    |                                                                          |
    |   WLAN_VENDOR_INTEL        Store the .config in the kernel.              |
    |   MAC80211                 Enables hardware independent IEEE 802.11      |
    |   CFG80211                 Enables the Linux Wireless LAN config API     |
    |   IWLWIFI                  Enables the IWLWIFI driver.                   |
    |                                                                          |
    |   One of the following options is required (=y)                          |
    |                                                                          |
    |   IWLMVM                   Driver that supports MVM firmware             |
    |   IWLDVM                   Driver that supports DVM firmware             |
    |                                                                          |
    +--------------------------------------------------------------------------+

Remember to reference the firmware blobs in `CONFIG_EXTRA_FIRMWARE`. \[[1.1](#1.1)\]


## [%[5.0]] Bluetooth

(this is a placeholder)


## [%[6.0]] Sound

The options from the Sound card support menu need only to be set if the card
supports HDMI or DisplayPort audio and you want to use it. On newer kernels
where Enable AMD Audio CoProcessor IP support appears, that should also be set.

    +-----------------------------------------------------------------------------+
    |                                                                             |
    |   The following options are required for soundcard support (=y).            |
    |                                                                             |
    |   CONFIG_SND_PCI              CI sound devices                              |
    |   CONFIG_SND_HDA_INTEL        HD Audio PCI                                  |
    |   CONFIG_SND_HDA_PATCH_LOADER Patch loading for HD-audio                    |
    |   CONFIG_SND_HDA_CODEC_HDMI   HDMI/DisplayPort HD-audio codec support       |
    |                                                                             |
    |   (Remember to also specify whatever codec your soundcard needs.)           |
    |                                                                             |
    +-----------------------------------------------------------------------------+
