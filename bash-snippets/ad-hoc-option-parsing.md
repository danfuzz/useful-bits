Ad-hoc Option Parsing
=====================

In cases where [the "fancy" `arg-processor`](../arg-processor) is overkill or
otherwise undesirable, here's some boilerplate for parsing options in a
reasonably standard-ish and sufficiently robust way.

**Note:** The case form `-?*` means "anything starting with a dash and with more
characters afterwards." As such, a single dash argument (`-`) is treated as an
argument per se and not an option. This is desirable and usual, in that `-` is
often used as an abbreviation for `stdin` or `stdout`.

```bash
# Error during argument processing?
argError=0

# Do something better?
doBetter=0

# Betterness factor.
moreFactor=''

while true; do
    case "$1" in
        --better)
            doBetter=1
            ;;
        --even-more=*)
            moreFactor="${1#*=}"
            ;;
        -h|--help)
            argError=-1 # `-1` suppresses error exit after displaying usage.
            break
            ;;
        --)
            # Explicit end of options.
            shift
            break
            ;;
        -?*)
            echo 1>&2 "Unknown option: $1"
            argError=1
            break
            ;;
        *)
            # Non-option argument.
            break
    esac

    shift
done

if (( argError )); then
    echo "${progName} [<opt> ...] -- <arg> ..."
    echo ''
    echo 'Does something fun.'
    echo ''
    echo '--better -- Makes it better.'
    echo '--even-more=<num> -- Increases betterness by factor <num>.'
    echo ''
    echo "${progName} [--help | -h]"
    echo '  Displays this message.'
    if (( argError == -1 )); then
        argError=0
    fi
    exit "${argError}"
fi
```
