#!/bin/bash
#SBATCH -p gpu-week
#SBATCH -t 2-00:00:00
#SBATCH -J alphafold
#SBATCH --gres=gpu:1
#SBATCH -J alphafold
#SBATCH -n 1
#SBATCH -c 10

# Alphafold submission script for the merlin cluster
# Usage: sbatch [slurm_opts] alphafold_merlin.sh [options] fasta_file
#
# OPTIONS
# All alphafold options are set automatically, but can be overwritten.
# Some common options:
#
# --max_template_date=YYYY-MM-DD    (default: today)
# --output_dir                      (default: current directory)
# --helpfull                        List all options
#
# 2021-12-22 Spencer Bliven, D.Ozerov
#

export ALPHAFOLD_DATA=/das/work/common/opt/alphafold/data_2.1.1/versions/latest

# Need at least rc6 to see alphafold
PMODULES_VERSION=1.0.0rc10;
source /opt/psi/config/profile.bash;

module --version

module purge
module use MX unstable Programming
module load alphafold/2.1.1
conda activate "${ALPHAFOLD_ENV:?"Error: ALPHAFOLD_ENV not set. Try 'module use MX unstable; module load alphafold'"}"

echo "hostname=$(hostname)"
echo "python=$(which python)"
echo "ALPHAFOLD_DATA=$(realpath "$ALPHAFOLD_DATA")"

python "${ALPHAFOLD_DIR:?Error loading module}/bin/alphafold_runner.py" -v 0 "$@"

