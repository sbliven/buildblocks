#!/bin/bash

declare -r BASE_DIR=$(cd "$(dirname $0)/../.." && pwd)
declare -r BOOTSTRAP_DIR="${BASE_DIR}/scripts/Bootstrap"

source "/opt/psi/config/environment.bash"
source "${BASE_DIR}/config/pmodules_version.conf"

${BOOTSTRAP_DIR}/gettext.build --bootstrap
${BOOTSTRAP_DIR}/getopt.build --bootstrap
${BOOTSTRAP_DIR}/dialog.build --bootstrap
${BOOTSTRAP_DIR}/bash.build --bootstrap
${BOOTSTRAP_DIR}/Tcl.build --bootstrap

# we have to remove the init directory - otherwise the next build will fail...
rm -rf "${PMODULES_HOME}/init"
${BOOTSTRAP_DIR}/Modules.build --bootstrap
mv -v "${PMODULES_HOME}/bin/modulecmd" "${PMODULES_HOME}/bin/modulecmd.tcl"
