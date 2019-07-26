#!/bin/bash

# Dump the package descriptions of all conda environments
DATE=$(date +%Y%m%d-%H%M%S)
MYDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
INSTALLDIR=$(dirname $MYDIR)
TOPLOGDIR="$INSTALLDIR/envlogs"

command -v conda &>/dev/null
if [[ $? -ne 0 ]]; then
    echo "conda command is not defined. Load the module" >&2
    exit 1
fi

CONDAPREFIX=$(expr "$(conda config --show root_prefix)" : '.*: *\(.*\)')

if [[ "$INSTALLDIR" != "$(dirname $CONDAPREFIX)" ]]; then
    printf "WARNING: you may be running the wrong conda command!!!\n" >&2
    printf "   PREFIX from conda root_prefix   : %s\n" "$(dirname $CONDAPREFIX)" >&2
    printf "   this script's associated prefix : %s\n" "$INSTALLDIR" >&2
    exit 1    
fi

mkdir -p "$TOPLOGDIR"
LOGDIR=$TOPLOGDIR/envdef-$DATE
mkdir $LOGDIR
for n in $(conda info --json | jq -r '.envs[]'|grep envs); do
    env=$(basename $n)
    echo ==== "$LOGDIR/${env}.txt ..." =====
    conda list -n $env -e > "$LOGDIR/${env}.txt"
done


