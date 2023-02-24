# 06/09/2019: Firefox updated to 69.0

I thought Firefox 69.0 would not be possible on KISS due to the new
unconditional dependency on `dbus`. I have written a patch which removes
this dependency and allows us to build it again!

Firefox 69.0 introduces something called `audio_thread_priority` and
from what I understand it's a way to prioritize audio threads when
needed. This entire "feature" works using `dbus` to do IPC on Linux
and subsequently breaks the `--disable-dbus` configure flag.

The patch I have written disables `audio_thread_priority` and in turn
causes audio to work the same as it did in 68.0 and below.

Sources:

-   Firefox Bug: <https://bugzilla.mozilla.org/show_bug.cgi?id=1561207>
-   [firefox-69-no-dbus.patch](https://github.com/kisslinux/repo/blob/aa24ba44e318f5fbb85eea5fe14c908b24cab6fb/extra/firefox/patches/firefox-69-no-dbus.patch)
