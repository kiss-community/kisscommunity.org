MANAGING SERVICES WITH BUSYBOX
==============================

KISS uses busybox's init with busybox's runit utilities for services by default.


Basic usage
-----------

    +---------+--------------------------------------------------------------------+
    | Action  | Command                                                            |
    |---------+--------------------------------------------------------------------|
    | List    | $ ls /etc/sv/                                                      |
    |         |                                                                    |
    | Enable  | $ ln -s /etc/sv/SERVICE_NAME/ /var/service                         |
    | Disable | $ unlink /var/service/SERVICE_NAME                                 |
    |         |                                                                    |
    | Stop    | $ sv down   SERVICE_NAME                                           |
    | Start   | $ sv up     SERVICE_NAME                                           |
    | Status  | $ sv status SERVICE_NAME                                           |
    |         |                                                                    |
    +---------+--------------------------------------------------------------------+

See <https://git.busybox.net/busybox/tree/runit/sv.c> for full usage.


Running commands during boot/shutdown
-------------------------------------

This can be accomplished in a generic way (using /etc/rc.d) or by modifying the
busybox-init only /etc/inittab file.


### Using /etc/rc.d

This method of configuration works with every init system which uses the
KISS init framework. See <https://github.com/kisslinux/init>

    +--------------------------------------------------------------------------+
    | Run command during boot.                                                 |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |  # Load the iwlwifi kernel module.                                       |
    |  echo "modprobe iwlwifi" > /etc/rc.d/wifi.boot                           |
    |                                                                          |
    +--------------------------------------------------------------------------+
    | Run command during shutdown.                                             |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |  # Save system time to hwclock.                                          |
    |  echo "hwclock -w" > /etc/rc.d/hwclock.pre.shutdown                      |
    |                                                                          |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |   TIP: .post.shutdown can also be used.                                  |
    |                                                                          |
    +--------------------------------------------------------------------------+


### Using /etc/inittab

    +--------------------------------------------------------------------------+
    | Run command during boot.                                                 |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |  # Load the iwlwifi kernel module.                                       |
    |  ::once:/bin/modprobe iwlwifi                                            |
    |                                                                          |
    +--------------------------------------------------------------------------+
    | Run command during shutdown.                                             |
    +--------------------------------------------------------------------------+
    |                                                                          |
    |  # Save system time to hwclock.                                          |
    |  ::shutdown:/bin/hwclock -w                                              |
    |                                                                          |
    +--------------------------------------------------------------------------+

