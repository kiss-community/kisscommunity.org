# 11/09/2019: Please update the package manager to 0.21.0

The previous package manager version had a bug which sometimes added a
package's repository files to '/'. The directories added to '/' by
the bug are harmless and safe to remove, but annoying nonetheless.

Please update to `0.21.0` (`kiss update`), I deeply apologize.
