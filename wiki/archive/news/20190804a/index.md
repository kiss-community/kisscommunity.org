# 04/08/2019: Firefox has been built

After hours of build attempts of both Chromium and Firefox, we have
successfully packaged Firefox. Chromium is a story for another time. The
build systems for these two browsers border on insanity and their
overall size and complexity is paramount.

-   Firefox requires both GTK2 and GTK3. GTK2 is required only for
    flash. \[1\]
-   Both Chromium and Firefox require `nodejs` to build.
-   Both Chromium and Firefox require Python 2.
-   Both browsers bundle all of their required third-party libraries and
    they cannot all be set to use the system\'s.
-   `clang` is now the default and "supported" compiler of both
    browsers.
-   Firefox requires a version of `automake` which is 18(?) years old.
    \[2\] \[3\]
-   Firefox requires `rust` which was painful to package for `musl` to
    say the least.
-   Chromium\'s build scripts require `python2` yet call `python` which
    points to `python3`.
-   A large number of patches were needed for both to support `musl`.
-   Both browsers depend on GTK+3 which depends on `dbus`. This
    dependency was removed by using a fake `atk` library.
-   ALSA audio support is being removed from Firefox. This includes the
    configure flag to enable it.
-   This will be updated as I remember things.

Sources:

-   \[1\] <https://bugzilla.mozilla.org/show_bug.cgi?id=1377445>
-   \[2\] <https://bugzilla.mozilla.org/show_bug.cgi?id=104642>
-   \[3\] <https://bugzilla.mozilla.org/show_bug.cgi?id=297544>
