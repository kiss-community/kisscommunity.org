# 08/09/2019: The cache directory has been moved

**NOTE:** This only affects existing installations.

Starting from version `0.12.0` of the package manager, the cache
directory is now located at `$XDG_CACHE_HOME/kiss` (*`~/.cache/kiss` if
the `$XDG_CACHE_HOME` variable is unset*).

This change was made to prevent a potential security issue when KISS is
used on a multi-user system. The cache is now effectively local to each
user.

The system-wide `/var/cache/kiss` directory is no longer used by the
package manager. If you would like to keep your current cache, you will
need to relocate it to the new location mentioned above.
