# 28/08/2019: Firefox 69 now fully depends on dbus

The upcoming Firefox release now depends on `dbus` and this dependency
can't be disabled. The usual `--disable-dbus` option has no effect.

Until this is fixed upstream or we find a way to patch this out KISS
will be swapping to the next ESR release of Firefox (68.0.2 -> 68.1.0).
This gives us a little over a year to sort out this situation.

With the release of Firefox 70 ALSA support will also be dropped from
Firefox and we will have to ship `apulse` with KISS to fix this.\*

It seems to be getting harder and harder to run and maintain a system
which doesn't follow the usual trend of software choices. Firefox even
has a `dbus` dependency on FreeBSD and OpenBSD!

The upstream bug report can be found here:
[#1561207](https://bugzilla.mozilla.org/show_bug.cgi?id=1561207)

\*: Update: On inspection of the Firefox 71 beta, ALSA is still
supported!

## Update (*Nov 3 2019*)

I have written a patch to remove the `dbus` requirement in versions
**69.0** to **71.0** beta. Firefox in KISS works 100% fine
*without* `dbus`!

-   Firefox 71.0 beta:
    [patch](https://github.com/kiss-community/repo/blob/ded0a8fc3e2800a579a2ed7df850e619a113c8eb/testing/firefox/patches/firefox-71-no-dbus.patch)
-   Firefox 70.0:
    [patch](https://github.com/kiss-community/repo/blob/a71e02ef014d044ab3e8c0938003b4183c3e26fc/extra/firefox/patches/firefox-70-no-dbus.patch)
-   Firefox 69.0.2:
    [patch](https://github.com/kiss-community/repo/blob/a7e7f001cd829f9e177fc93959dfcdd0d6749014/extra/firefox/patches/firefox-69.0.2-no-dbus.patch)
-   Firefox 69.0:
    [patch](https://github.com/kiss-community/repo/blob/aa24ba44e318f5fbb85eea5fe14c908b24cab6fb/extra/firefox/patches/firefox-69-no-dbus.patch)

### Why did --disable-dbus break?

Firefox 69.0 added a new audio feature called "audio\_thread\_priority"
to prioritize audio threads. On Linux, this uses `dbus` to function.

Firefox has historically always provided the `--disable-dbus` option to
remove the requirement. It has always been optional. The feature works
in its entirety **minus** the new `audio_thread_priority` code.

No (*or little*) testing was done with the `--disable-dbus` configure
flag and this is marked as a **defect** in the upstream bug report
(*which gives me hope that it'll be fixed*).

My patch to workaround this issue simply disables the
`audio_thread_priority` feature which removes the `dbus` requirement and
effectively reverts audio to how it was prior to version 69.0.

The upstream bug report can be found here:
[#1561207](https://bugzilla.mozilla.org/show_bug.cgi?id=1561207)

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
