# 31/10/2019: ninja replaced by samurai

The build tool `ninja` has been replaced with `samurai`.

This replacement is 1:1 compatible with `ninja`, absolutely tiny in
size, doesn't require `python` to build and is simply *simpler*.

The one downside is that a smidgen of manual intervention is required.
Simply remove `ninja` (`KISS_FORCE=1 kiss r ninja`) and run
`kiss update`.

The sources for Samurai can be found here:
<https://github.com/michaelforney/samurai>
