Script Location Detection
=========================

It's often useful to know where a script is in the filesystem, including
especially following symlinks (so that a script invoked via a link can find its
"home").

Current best-known (to me) boilerplate for determining that. This assumes the
availability of `readlink -f`, which can at least _mostly_ be counted on to
exist as of the mid-2010s.

```bash
# Figure out the symlink-resolved program name and directory.
cmdName="$(readlink -f "$0")" || exit "$?"
cmdDir="${cmdName%/*}"
cmdName="${cmdName##*/}"
baseDir="${cmdDir%/*}" # Parent of `cmdDir`; often useful.
```

If `readlink -f` can't be counted on to exist, here's a version that follows
symlinks-to-symlinks "manually:"

```bash
# Figure out the symlink-resolved program name and directory.
function init-cmd {
    local newp p="$0"

    while newp="$(readlink "$p")"; do
        [[ ${newp} =~ ^/ ]] && p="${newp}" || p="$(dirname "$p")/${newp}"
    done

    cmdDir="${p%/*}"
    cmdName="${p##*/}"
    baseDir="${cmdDir%/*}" # Parent of `cmdDir`; often useful.
}
init-cmd
unset -f init-cmd # Leave no trace.
```
