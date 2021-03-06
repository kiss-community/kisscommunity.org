STORAGE
=======

This article will provide general guidance on the process of preparing a disk
device (SSD or HDD) for a new installation of KISS Linux.  Advanced storage
formats (e.g. RAID, LVM) are considered out of scope.


Index
-----

* [0.0](#0.0) Overview
  * [0.1](#0.1) Terminology
  * [0.2](#0.2) Tools
* [1.0](#1.0) Partitioning Schemata
  * [1.1](#1.1) Minimum Partition Layouts
  * [1.2](#1.2) Swap Partition vs File
* [2.0](#2.0) Partitioning Example
* [3.0](#3.0) Formatting
  * [3.1](#3.1) Filesystems
  * [3.2](#3.2) Swap Partition
  * [3.3](#3.3) Swap File
* [4.0](#4.0) fstab


## [%[0.0]] Overview

Next to kernel configuration, preparing a disk device for installing a Linux
distribution is one of the more intimidating topics for a new UNIX user to
tackle. This process is not only highly dependent on user circumstances (the
type of hardware you have access to, your file system needs, your backup
requirements, etc.), but the process varies based on the tools used for the job.
Therefore, the first step to a successful installation is understanding the
terminology and the tools which are required throughout the process.


### [%[0.1]] Terminology

    +------------------+-------------------------------------------------------+
    |                  |                                                       |
    |   Block Device   |   Represents an abstract interface to the disk.       |
    |                  |   User programs can use these block devices to        |
    |                  |   interact with the disk without worrying about       |
    |                  |   whether the drives are SATA, SCSI, or something     |
    |                  |   else. (e.g. /dev/sd*, /dev/nvme0n*, etc)            |
    |                  |                                                       |
    |   Partition      |   Represent smaller, more manageable block devices.   |
    |                  |   These can be thought of as the places where user    |
    |                  |   data lives.                                         |
    |                  |                                                       |
    |   Filesystem     |   A filesystem allows for data to actually be written |
    |                  |   to a given partition. Filesystems vary in features, |
    |                  |   requirements, and read/write access. In short, a    |
    |                  |   filesystem is the structure for a given partition.  |
    |                  |                                                       |
    |   DOS            |   The DOS disklabel setup uses 32-bit identifiers     |
    |                  |   for the start sector and length of the partitions,  |
    |                  |   and supports three partition types: primary,        |
    |                  |   extended, and logical. Primary partitions have      |
    |                  |   their information stored in the master boot         |
    |                  |   record itself - a very small (usually 512 bytes)    |
    |                  |   location at the very beginning of a disk. Due to    |
    |                  |   this small space, only four primary partitions      |
    |                  |   are supported (for instance, /dev/sda1 to           |
    |                  |   /dev/sda4). This is the old format for disklabels.  |
    |                  |                                                       |
    |   GPT            |   GPT (GUID Partition Table) setup uses 64-bit        |
    |                  |   identifiers for the partitions. The location in     |
    |                  |   which it stores the partition information is much   |
    |                  |   bigger than the 512 bytes of a DOS disklabel,       |
    |                  |   which means there is practically no limit on the    |
    |                  |   amount of partitions for a GPT disk. Also the       |
    |                  |   size of a partition is bounded by a much greater    |
    |                  |   limit (almost 8 ZB - yes, zettabytes). A GPT disk   |
    |                  |   is required for UEFI systems.                       |
    |                  |                                                       |
    |   ROOTFS         |   ROOTFS (Root Filesystem) is the primary partition   |
    |                  |   where the entire system is directly or indirectly   |
    |                  |   mounted to. This is commonly referred to as '/'.    |
    |                  |                                                       |
    |   BOOT           |   The boot partition is where important files         |
    |                  |   required at boot time, such as the kernel, are      |
    |                  |   stored. This partition is required only on UEFI     |
    |                  |   systems. It is usually mounted at /boot.            |
    |                  |                                                       |
    |   HOME           |   This partition is where most user data is stored.   |
    |                  |   It is usually mounted at /home.                     |
    |                  |                                                       |
    |   SWAP           |   Swap space can take the form of a disk partition    |
    |                  |   or a file. Users may create a swap space during     |
    |                  |   installation or at any later time as desired.       |
    |                  |   Swap space can be used for two purposes: to         |
    |                  |   extend the virtual memory beyond the installed      |
    |                  |   physical memory (RAM), and also for hibernation     |
    |                  |   or for suspend-to-disk support.                     |
    |                  |                                                       |
    +------------------+-------------------------------------------------------+

Some useful facts and things to keep in mind:

Due to using 32-bit identifiers, DOS partitioning tables cannot handle disks
that are >2 TBs in size.

Unless an extended partition is created, DOS disk labels supports a maximum
of four partitions.

Using GPT on a BIOS-based computer works, and is referred to as a hybrid
setup. This type of setup requries a 1MB BIOS boot partition (unformatted)
so that extra data can be stored by the bootloader (like GRUB2). This setup
is useful in cases where more than four primary or secondary partitions are
required for a system.
Unfortunately this has several limitations. For instance, you cannot
dual-boot with a Microsoft Windows operating system, as Windows will boot in
UEFI mode if it detects a GPT partition label. Also note that some buggy
(old) motherboard firmware configured to boot in BIOS/CSM/legacy mode might
also have problems with booting from GPT labeled disks. As such, this style
is undesireable, and in general it is a good idea to use GPT in cases where
UEFI can be used.

UEFI/GPT and BIOS/MBR are not synonymous. UEFI/BIOS refer to particular
types of systems that utilize the Unified Extensible Firmware Interface or
the Basic Input/Output System. This is determined strictly by the
motherboard used in a given system. GPT/DOS, however, refer to particular
disk labels: GUID Partition Tables versus the DOS label. These types
directly limit the structures available on any given disk drive - both the
number of partitions available, as well as the size of any given partition.
A good rule of thumb, however, is that UEFI systems use GPT disk labels,
BIOS systems use DOS disk labels, and hybrid systems use BIOS + GPT.

The BOOT partition is a source of much confusion for users. For instance,
it is erroneously claimed that it must be mounted to `/efi`, or that kernel
images should be named `vmlinuz.efi`.
In point of fact, it is only necessary on UEFI systems, though it may be
useful on BIOS systems. The BOOT partition need not be mounted to `/efi`.
Indeed, the only requirements are that it be formatted to FAT32 (in the case
of UEFI systems), and be at least 100MB in size. The recommended minimum
size for UEFI systems is 256MB.
That the kernel be named `vmlinuz.efi` serves only to make the fact that it
is a UEFI system explicit.
If users intend on using a multiboot system, a single BOOT partition can be
shared by all operating systems.

An important point of consideration is whether or not a separate HOME
partition should be used. This is useful in cases where users wish to keep
their data in a location separate from their operating system, for instance
in cases of critical failures requiring the OS to be reinstalled, or if
users wish to encrypt their personal data separately from their core OS.
This separation between `/` and `/home` allow users to easily migrate their data
across many different operating systems; they need only remount the HOME
partition to `/home` on the new system. In general, this is recommended.

In addition to a separate HOME, several other additional partition options
exist. For instance, a separate var (`/var`) and data partitions can be used.
Separate data partitions are useful in instances where users would like to
easily share data across different operating systems, as allowing write
access to a user's home directory is a security risk. A separate `/var` is
useful in niche cases where `/usr` is read-only. For more detailed information
on filesystem structures, refer to the [Filesystem Hierarcy Standard](https://refspecs.linuxfoundation.org/fhs.shtml).
Additionally, the Linux From Scratch project has some [useful rationales](http://linuxfromscratch.org/lfs/view/stable/chapter02/creatingpartition.html).


### [%[0.2]] Tools

Depending on which live environment the user chooses for installing a KISS
Linux system, the tools available vary. On most UNIX systems, the following
can usually be expected:

- [fdisk](https://man7.org/linux/man-pages/man8/fdisk.8.html): a dialogue driven partition manipulator
- [gdisk](http://rodsbooks.com/gdisk/): GPT fdisk (note that busybox fdisk also supports GPT)
- [cfdisk](https://linux.die.net/man/8/cfdisk): a partition editor with a curses-based UI, part of util-linux
- [parted](https://gnu.org/software/parted/manual/parted.html): a GNU partition editor

It is also possible to use the live CD version of parted, [GParted](https://gparted.org/), to
partition disks, and it offers many other useful features for disk
management and data recovery.

In general, most programs can handle the majority of use-cases. The tool of
choice is almost entirely user preference. However, some utilities have
powerful and advanced features that can aid in fixing damaged disks. fdisk
is one such program, and is useful in cases where more fine-grained control
is required. For general system setup, however, any tool will do.


## [%[1.0]] Partitioning Schemata

Great care should be taken when picking a partition structure, as changing it
afterwards is (generally) a difficult endeavor. Ensure that the chosen structure
meets your use case. Things to consider include whether or not a swap partition
is needed, whether to use a separate home partition, whether separate partitions
are needed for general data storage (like music or photos), and whether
dual-booting is desired.


### [%[1.1]] Minimum Partition Layouts

The number of partitions required is highly variable and dependent on the
use case. The following table provides examples of common partition
schemata, formats, and recommended minimum sizes:

    +----------------------------+---------------------------------------------+
    |    Schemata Description    |   Partition (Type,      Format, Size)       |
    +----------------------------+---------------------------------------------+
    |                            |                                             |
    |   GPT + UEFI (with /home)  |   /dev/sda1 (BOOT,      FAT32,  256MB)      |
    |                            |   /dev/sda2 (ROOTFS,    EXT4,   30GB )      |
    |                            |   /dev/sda3 (HOME,      EXT4,   *    )      |
    |                            |                                             |
    |   Legacy DOS (with swap)   |   /dev/sda1 (SWAP,      swap,   RAM  )      |
    |                            |   /dev/sda2 (ROOTFS,    EXT4,   *    )      |
    |                            |                                             |
    |   Hybrid BIOS/GPT          |   /dev/sda1 (BIOS BOOT, XXXX,   1MB  )      |
    |                            |   /dev/sda2 (SWAP,      swap,   RAM  )      |
    |                            |   /dev/sda3 (ROOTFS,    EXT4,   xxxGB)      |
    |                            |   /dev/sda4 (HOME,      XFS,    yyyGB)      |
    |                            |   /dev/sda5 (DATA,      BTRFS,  zzzGB)      |
    |                            |                                             |
    +----------------------------+---------------------------------------------+

The boot partition is generally only used for storing kernels or an
initramfs. As these files are usually very small (<20MB), 256MB is more
than enough to accomodate most use-cases. 512MB is plenty. A separate BOOT
is only required on UEFI systems.

In cases where no other additional partition is desired, the ROOTFS or HOME
partition should span the remainder of the disk.

For source-based distributions like KISS, maximizing the amount RAM that can
be used is paramount for successful builds, especially for large packages
such as rust, firefox, or qt5-webengine. If the amount of RAM available is
less than 8GB, the usage of a swap partition or swap file is strongly
recommended to avoid build failures due to out-of-memory (OOM) issues. A
decent rule of thumb for swap size is to have the same amount of swap as
you have RAM.

These examples only serve to show a minimum partition layout required for
each type of disk style (UEFI + GPT, BIOS + DOS, hybrid).


### [%[1.2]] Swap Partition vs File

When considering swap space, there are benefits and tradeoffs to certain
choices. The traditional recommendation has been to create a swap partition
as close to the first partition as possible, that is at least half the
amount of RAM available - this number is a sliding scale and varies by use
case. For instance, if few RAM intensive programs are going to be used, and
little compiling will be done on the host system, less swap space is needed
(if any at all).

Historically, swap was placed at the beginning of disks as this allowed for
the fastest possible seek times on traditional spinning disk drives (hard
drives). This was preferred because disk access times are orders of
magnitude slower than RAM access times, and long swap operations result in
a desktop feeling 'slow' or 'laggy'. However, with the rise in popularity
of solid state drives (and, more recently, NVMe based storage), along with
the precipitous decrease in storage space cost, the requirement of a
separate swap partition has laxed. If users have access to low latency,
large storage drives, a swap file may be a preferable alternative.

Swap files allow for ondemand, resizeable swap spaces. Swap may not be
necessary for day-to-day operation but only in cases where large builds are
happening. With access to these newer technologies, users can simply create
a file and define it to be a dedicated swap location which is used
identically to the traditional swap partition. This has left the need for a
swap partition largely to cases where solid state storage is not an option.

For more modern systems, swap files are in general preferable to partitions.
Care should be taken, however. Changes may occur outside of the user's
control that necessitate intervention. For instance, if a swapfile
disappears but is still referenced in `/etc/fstab`, disk mounting will fail
at boot and the system will drop users into an emergency shell.
Additionally, file fragmentation can cause swap files to become unreliable.
Finally, kernel updates could potentially [cause issues](https://bugzilla.kernel.org/show_bug.cgi?id=207585).

In addition to swap, @/[zswap](/storage/zswap/) and @/[zram](/storage/zram) are useful options to consider for
maximizing swap usage and memory management.


## [%[2.0]] Partitioning Example

The following is a step-by-step partitioning example.

**PLEASE BE AWARE**: The following commands can cause irreparable damage to the
data on your drives. Ensure that the data on these drives is backed up to a
separate device, and make sure you select the correct device for partitioning.

Again, these commands are dangerous and **WILL CAUSE DATA LOSS**.

In order to identify the correct disk, there are several commands that can help

    +------------------------------------------------------------------------------+
    |                                                                              |
    |    $ fdisk -l                                                                |
    |    $ sfdisk -l                                                               |
    |    $ parted -l                                                               |
    |    $ lsblk                                                                   |
    |                                                                              |
    +------------------------------------------------------------------------------+

While partitioning disks, you will be asked multiple questions. These include
the starting sector of the partition, the last sector of the partition, and the
hex code for that partition.

Generally, using the default as the first sector is the best choice - this will
ensure there are no strange breaks between partitions.

Most programs support relative last sector locations. Therefore, instead of
typing out the desired sector number, one need only write '+400GB' to make the
partition start at the first available sector and continue for the next 400GB.

Hex codes or partition IDs are hexadecimal identifiers which the kernel and
filesystem programs can interpret, and programs like fdisk and cfdisk will use
the hex code of a given partition to display a useful fact about the partition,
like that it's specifically an EFI partition, or a Linux root partition, or a
Solaris partition. Because GPT uses 64-bit partitions identifiers, far more
partition types are available for use on GPT systems over MBR systems.

Be aware that altering partitions on in-use disks could cause data corruption,
and the changes in partition layout may not be available until the next reboot.

This example assumes the target device block of `/dev/nvme0n1`, using gdisk
for the actual partitioning process.

To create a GPT + EFI disk with a separate `/home`,

    +------------------------------------------------------------------------------+
    |                                                                              |
    |    $ gdisk /dev/nvme0n1                                                      |
    |                                                                              |
    |    # Enter '?' for a list of available commands                              |
    |                                                                              |
    |    # Delete partition data by creating a new GPT:                            |
    |    $ o                                                                       |
    |    This option deletes all partitions and creates a new GPT.                 |
    |    Proceed? (Y/N): y                                                         |
    |                                                                              |
    |    # Create Partition 1 (/boot):                                             |
    |    $ n                                                                       |
    |    Partition Number:  (RETURN key for 1)                                     |
    |    First sector: (RETURN key for first available)                            |
    |    Last sector: +128M                                                        |
    |    Hex Code (L to show codes): ef00                                          |
    |                                                                              |
    |    # Create Partition 2 (ROOTFS):                                            |
    |    $ n                                                                       |
    |    Partition Number:  (RETURN key for 2)                                     |
    |    First sector: (RETURN key for first available)                            |
    |    Last sector: +30G                                                         |
    |    Hex Code: 0304                                                            |
    |                                                                              |
    |    # Create Partition 3 (HOME):                                              |
    |    $ n                                                                       |
    |    Partition Number:  (RETURN key for 3)                                     |
    |    First sector: (RETURN key for first available)                            |
    |    Last sector:  (RETURN key for rest of disk)                               |
    |    Hex Code: 0302                                                            |
    |                                                                              |
    |    # Write Partition Table To Disk:                                          |
    |    $ w                                                                       |
    |    Do you want to proceed? (Y/N): Y                                          |
    |                                                                              |
    +------------------------------------------------------------------------------+

cfdisk may be preferable to users who prefer a more visual representation of
partition manipulation and a constantly updating table of information on the
current partition layout and structure.


## [%[3.0]] Formatting

Now that the disks have been partitioned, it is time to create the relevant
filesystems for each partition.


### [%[3.1]] Filesystems

There are many different filesystems to choose from on any given Linux
system. Which filesystem is used depends almost entirely on the use-case of
the system. For simple data storage read only by UNIX systems, EXT4 is a
perfectly normal choice. For data that needs to be accessible to Windows,
FAT or NTFS is required. The Apple Filesystem (APFS) is used by Macs.
In the simple case where only Linux systems require access to a given
partition, many choices exist. Below is a list of filesystems which are
available in KISS either in the official repository or in community.

    +--------------+------------------------+----------------------------------+
    |  Filesystem  |  Package               |  Command                         |
    +--------------+------------------------+----------------------------------+
    |              |                        |                                  |
    |  swap        | core/busybox           |  mkswap                          |
    |  EXT2/3/4    | extra/e2fsprogs        |  mkfs.ext2/3/4                   |
    |  DOS/FATxx   | extra/dosfstools       |  mkfs.dos/fat/vfat               |
    |  XFS         | extra/xfsprogs         |  mkfs.xfs                        |
    |  BTRFS       | community/btrfs-progs  |  mkfs.btrfs                      |
    |  NTFS        | community/ntfs-3g      |  mkfs.ntfs                       |
    |              |                        |                                  |
    +--------------+------------------------+----------------------------------+

Other filesystems exist with varying degrees of popularity, including JFS,
ReiserFS, and ZFS. The community repository is an excellent place to share
work in including these filesystems in KISS! Others are available in
user-created repositories. [ZFS](https://github.com/jedavies-dev/kiss-zfs) is one such example. Due to licensing
restrictions, ZFS requires more work to use than other filesystems.

EXT4 is a solid, general purpose filesystem. For UEFI systems, FAT32 is a
required filesystem for the BOOT partition. BTRFS is an experimental
filesystem which sees heavy development by organizations like Facebook,
and offers a different way of managing storage than more traditional (EXT,
DOS, NTFS) filesystems. All of these have built-in kernel support.

For a more complete list of other filesystem options and what limitations
and features exist for them, refer to the [Arch Wiki](https://wiki.archlinux.org/index.php/file_systems).

Continuing from the partition example in [2.0](#2.0), we will make a FAT32
parition on BOOT (`/dev/nvme0n1p1`), and an EXT4 partition on ROOTFS and HOME
(`/dev/nvme0n1p2` and `/dev/nvme0n1p3`, respectively):

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ mkfs.ext4     /dev/nvme0n1p2                                         |
    |   $ mkfs.ext4     /dev/nvme0n1p3                                         |
    |   $ mkfs.fat -F32 /dev/nvme0n1p1                                         |
    |                                                                          |
    |   $ mount /dev/nvme0n1p2 /mnt                                            |
    |   $ mount /dev/nvme0n1p3 /mnt/home                                       |
    |   $ mount /dev/nvme0n1p1 /mnt/boot                                       |
    |                                                                          |
    +--------------------------------------------------------------------------+


### [%[3.2]] Swap Partition

To set up a partition as a Linux swap space, the `mkswap` command is used.
Replace `X` with the drive where the swap partition is located, and `Y` by the
partition on that drive that will be formatted as swap.

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ mkswap /dev/sdXY                                                     |
    |   $ swapon /dev/sdXY                                                     |
    |                                                                          |
    +--------------------------------------------------------------------------+


### [%[3.3]] Swap File

As an alternative to creating an entire partition, a swap file offers
similar functionality, and the added benefits of being able to vary its size
on-the-fly, as well as being more easily removed. This may be especially
desirable if disk space is at a premium.

The most straightforward way to create a swap file is to use dd:

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ dd if=/dev/zero of=$LOCATION bs=$BYTES count=$BLOCKS                 |
    |                                                                          |
    +--------------------------------------------------------------------------+

`$LOCATION` is where the swapfile should be made. Assume `$LOCATION`=`/swapfile`.

`$BYTES` is the size of each block to be written to the file. Disks have
varying supported block sizes; choosing the correct size for the partition
where the swapfile will be is important for optimizing read/write
throughput. dd defaults to 512 bytes, but this is suboptimal for drives
with larger supported block sizes. To determine the block size for your
device, you can use stat:

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ stat -fc %s .                                                        |
    |                                                                          |
    +--------------------------------------------------------------------------+

For instance, if the result is 4096, `$BYTES`=4k should be chosen.

`$BLOCKS` is the number of blocks of size `$BYTES` you wish to write to
`$LOCATION`. `$BLOCKS` determines the final size of the swapfile.

`$BYTES` and `$BLOCKS` can be suffixed by b (512 bytes), kB (1,000 bytes), k
(1,024 bytes), MB (a thousand kB), M (a thousand k), GB (a million kB), or
G (a million k).

To create a 16G swapfile at `/swapfile` with a 4k block size,

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ dd if=/dev/zero of=/swapfile bs=4k count=4M                          |
    |                                                                          |
    +--------------------------------------------------------------------------+

Set the permissions, create the swap filesystem, and activate it as swap,

    +--------------------------------------------------------------------------+
    |                                                                          |
    |   $ chmod 600 /swapfile                                                  |
    |   $ mkswap    /swapfile                                                  |
    |   $ swapon    /swapfile                                                  |
    |                                                                          |
    +--------------------------------------------------------------------------+

To remove a swap file, it's as simple as disabling and deleting it,

    +--------------------------------------------------------------------------+
    |                                                                          |
    |  $ swapoff /swapfile                                                     |
    |  $ rm -f   /swapfile                                                     |
    |                                                                          |
    +--------------------------------------------------------------------------+


## [%[4.0]] fstab

The fstab file contains a list of partitions with their filesystem type, their
mount location, and the options they should be mounted with. The mount program
will read the fstab file (by default `/etc/fstab`) and will mount all of the
partitions and filesystems for you. This is useful for automatically mounting
things like BOOT, HOME, and tmpfs during the init process.

The fstab is NOT required - the kernel location and ROOTFS should be specified
in the bootloader entry. If you find yourself mounting the same partitions
repeatedly with consistent options, the fstab file serves to automate this
prcess for you.

Here is an example fstab, which will mount ROOTFS to `/`, BOOT to `/boot`, HOME to
`/home`, enable the swap file, and mount some important virtual filesystems:

    +------------------------------------------------------------------------------+
    |                                                                              |
    |   # device      mount-point   type   options         dump  fsck order        |
    |                                                                              |
    |   /dev/sda2     /             ext4   defaults        0     1                 |
    |   /dev/sda1     /boot         vfat   defaults        0     2                 |
    |   /dev/sda3     /home         ext4   defaults        0     2                 |
    |   /swapfile     none          swap   defaults        0     0                 |
    |   tmpfs         /tmp          tmpfs  rw,nodev,nosuid 0     0                 |
    |   proc          /proc         proc   defaults        0     0                 |
    |   sysfs         /sys          sysfs  defaults        0     0                 |
    |   devpts        /dev/pts      devpts gid=4,mode=620  0     0                 |
    |                                                                              |
    +------------------------------------------------------------------------------+

tmpfs, proc, sysfs, and devpts should be mounted during the init process.
Therefore, proc, sysfs, and devpts can be left out of the fstab. A reason to
keep tmpfs in the fstab is to use it for building packages in RAM.

Devices can be referred to either by their `/dev` pathname, by a label, by UUID,
or by Part-UUID. For systems with multiple drives, it is recommended to use
UUIDs or labels instead of `/dev` pathnames, as these are volatile and could
change during each system reboot. See the [Arch Wiki](https://wiki.archlinux.org/index.php/Fstab#Identifying_file_systems) for details on identifying disks.  
**NOTE**: busybox does not support mounting disks by Part-UUID.

The dump entry refers to the backup utility, [dump](https://linux.die.net/man/8/dump).

`fsck order` gives the order in which a filesystem check should be ran in. ROOTFS
should be specified with a 1. All other filesystems should be specified with 2
or 0. swap and virtual filesystems should not be `fsck`'d.

There are a large number of options that you can choose from for mounting
partitions. '`defaults`' is a basic, filesystem-independent option which will
mount the partition `rw,suid,dev,exec,auto,nouser,async`. For an explanation of
these options (and far more detailed information on the fstab) see [fstab(5)](https://man7.org/linux/man-pages/man5/fstab.5.html).

**CAUTION**: an improperly configured fstab will result in the user being dumped
into an emergency shell! Even a small typo will result in this. If it occurs,
simply check the fstab for errors, mount the partitions that failed to be
mounted, and exit the emergency shell.
