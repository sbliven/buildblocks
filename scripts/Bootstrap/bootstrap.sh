#!/bin/bash
declare -r BASE_DIR=$(cd "$(dirname $0)/../.." && pwd)
declare -r BOOTSTRAP_DIR="${BASE_DIR}/scripts/Bootstrap"

${BOOTSTRAP_DIR}/build_pmodules.sh
${BOOTSTRAP_DIR}/install_pmodules.sh

