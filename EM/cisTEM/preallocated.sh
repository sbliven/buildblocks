#!/bin/bash
# Wrapper for the 'preallocated' default profiles
# usage in cistem profile: preallocated.sh $command
set -e

# Ensure we actually allocated resources
: "${SLURM_NODELIST:?Error: No nodes preallocated! See https://intranet.psi.ch/BIO/ComputingCisTEM}"

srun -N 1 -n 1 -c 2 --exclusive $@
