# Wayland

Wayland [[0]](https://wayland.freedesktop.org/) is a display protocol that aims
to be a simpler and modern replacement for the X Window
System. [[1]](https://wayland.freedesktop.org/faq.html#heading_toc_j_4) The
Wayland protocol follows a client–server model in which clients are the
graphical applications requesting the display of pixel buffers on the screen,
and the server (compositor) is the service provider controlling the display of
these
buffers. [[2]](https://en.wikipedia.org/wiki/Wayland_(display_server_protocol))

Unlike Xorg, which is at the center of the universe (and everyone must talk to),
Wayland puts the Linux kernel and its components (DRI, DRM, etc) in the middle.
This effectively leaves the Wayland compositor off in the corner as its little
more than a special application. [[3]](https://lwn.net/Articles/413335/)

Wayland has been in development since September of 2008
[[4]](https://cgit.freedesktop.org/wayland/wayland/commit/?id=97f1ebe8d5c2e166fabf757182c289fed266a45a)
and is usable today for a large number of use-cases. Some hardware
configurations (namely NVIDIA GPUs)
[[5]](https://github.com/swaywm/sway/issues/490)
[[6]](https://drewdevault.com/2017/10/26/Fuck-you-nvidia.html) and a number of
features are not currently supported by compositors.


## Caveats

While the Wayland protocol is more or less done, the growing list of compositors
are in differing stages of completeness. Xorg is still in wide use and a lot of
software still requires it.

The major downside to Wayland (compositors) is the reduction in choice. While
the Wayland protocol does not define what a compositor shall depend on, they
typically lock the user into udev, libinput and systemd/logind.

The lack of standardized, desktop-oriented protocols has created a situation
where software may only work in some compositors and not others. This should
improve over time as more protocols become standardized.

- Limited hardware and driver support.
  [[5]](https://github.com/swaywm/sway/issues/490)
  [[6]](https://drewdevault.com/2017/10/26/Fuck-you-nvidia.html)
  [[7]](https://github.com/swaywm/sway/wiki#nvidia-users)
  [[8]](https://wayland.freedesktop.org/building.html (Hardware / Drivers))
- Non-standard and compositor specific software.
  [[10]](https://github.com/Alexays/Waybar)
  [[11]](https://github.com/any1/wayvnc)
  [[12]](https://github.com/fzwoch/obs-gnome-screencast)
- No Wayland support in SDL 1 (must use XWayland).
  [[13]](https://hansdegoede.livejournal.com/22212.html)
- Starting compositors without logind requires SUID permissions.
  [[14]](https://github.com/swaywm/sway/wiki/Running-Sway-without-systemd)
- Locked into using udev. [[15]](https://github.com/swaywm/wlroots#building)


## Benefits

Wayland has a large number of benefits and improvements over Xorg. The above
caveats do not apply to everyone (or every system). Those unaffected or willing
to live with the caveats will have no problem swapping over.

- Less moving parts [[13]](https://hansdegoede.livejournal.com/22212.html),
  although some software still heavily relies on the Xorg libraries (Mesa
  [[16]](https://github.com/kiss-community/repo/blob/master/extra/mesa/depends),
  Firefox
  [[17]](https://github.com/kiss-community/repo-bin/blob/main/bin/firefox/depends),
  etc).
- No screen tearing by design
  [[18]](https://people.freedesktop.org/~daniels/lca2013-wayland-x11.pdf).
- Hardware accelerated video playback in Firefox
  [[19]](https://bugzilla.mozilla.org/show_bug.cgi?id=1610199) and Webkit2GTK
  (webkit2gtk VAAPI source needed)

## Installation

Wayland is now officially supported by KISS in the [main
repositories](https://codeberg.org/kiss-community/repo/src/branch/master/wayland)
(see [/archive/blog/20210711a/](/archive/blog/20210711a/)).

## Post installation

* In environments without systemd/elogind/consolekit the `XDG_RUNTIME_DIR`
  variable must be set manually. Export this in your shellrc (.ashrc, .bashrc,
  .zshrc, etc)


    export XDG_RUNTIME_DIR=${XDG_RUNTIME_DIR:-/tmp/$(id -u)-runtime-dir}
    
    [ -d "$XDG_RUNTIME_DIR" ] || {
        mkdir -p   "$XDG_RUNTIME_DIR"
        chmod 0700 "$XDG_RUNTIME_DIR"
    }

* Install a Compositor of your choosing.

