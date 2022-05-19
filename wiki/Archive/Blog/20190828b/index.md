# 28/08/2019: Why does GTK3 Firefox require GTK2?

Firefox only supports Linux builds with GTK3 for some time now, however
GTK2 is still a mandatory dependency. It turns out that GTK2 is required
for NPAPI plugins and the **only** plugin which is still in use is the
Flash Plugin!

You cannot disable NPAPI plugin support which means that **Firefox has a
dependency on GTK2 solely for Flash**. The sole reason that KISS ships
GTK2 is for Firefox, Flash will die some time in 2020 (*possibly 2021*)
so until then we're stuck with GTK2.

Source:

> As long as NPAPI plugins are supported, build dependency on gtk2
> cannot be dropped.

> NPAPI is currently only around to support Flash (bug 1269807). Per
> https://developer.mozilla.org/en-US/docs/Plugins/Roadmap, Firefox's
> Flash support (and thus NPAPI support) will be removed sometime in
> 2020.

<https://bugzilla.mozilla.org/show_bug.cgi?id=1377445>

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
