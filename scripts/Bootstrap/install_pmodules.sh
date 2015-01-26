#!/bin/bash

declare -r BASE_DIR=$(cd "$(dirname $0)/../.." && pwd)
declare -r BOOTSTRAP_DIR="${BASE_DIR}/scripts/Bootstrap"

source "/opt/psi/config/environment.bash"
source "${BASE_DIR}/config/pmodules_version.conf"

sed_cmd="s:@PMODULES_HOME@:${PMODULES_HOME}:g;"
sed_cmd+="s:@PMODULES_VERSION@:${PMODULES_VERSION}:g;"
sed_cmd+="s:@MODULES_VERSION@:${MODULES_VERSION}:g"
sed "${sed_cmd}" "${BOOTSTRAP_DIR}/modulecmd.bash" > "${BOOTSTRAP_DIR}/modulecmd"

install -d -m 0755 "${PMODULES_HOME}/etc"

install -m 0755 "${BOOTSTRAP_DIR}/modulecmd" "${PMODULES_HOME}/bin"
install -m 0755 "${BOOTSTRAP_DIR}/init_local_env.bash" "${PMODULES_HOME}/bin"
install -m 0755 "${BOOTSTRAP_DIR}/modsync.bash" "${PMODULES_HOME}/bin"
install -m 0755 "${BOOTSTRAP_DIR}/dialog.bash" "${PMODULES_HOME}/bin"

install -m 0644 "${BOOTSTRAP_DIR}/modulerc" "${PMODULES_HOME}/etc"

install -m 0644 "${BOOTSTRAP_DIR}/bash" "${PMODULES_HOME}/init"
install -m 0644 "${BOOTSTRAP_DIR}/bash_completion" "${PMODULES_HOME}/init"

install -m 0644 "${BOOTSTRAP_DIR}/libmodules.tcl" "${PMODULES_HOME}/lib"
