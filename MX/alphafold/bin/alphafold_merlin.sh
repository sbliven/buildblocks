#!/bin/bash
#SBATCH -p gpu
#SBATCH -J alphafold
#SBATCH -M gmerlin6
#SBATCH --gpus=1
#SBATCH -n 1
#SBATCH -c 10

# Alphafold submission script for the merlin cluster
# Usage: sbatch [slurm_opts] alphafold_merlin.sh [options] fasta_file
#
# OPTIONS
# All alphafold options are set automatically, but can be overwritten.
# Some common options:
#
# --max_template_date=YYYY-MM-DD (default: today)
# --output_dir (default: current directory
# --helpfull List all options
#
# 2021-12-22 Spencer Bliven, D.Ozerov
#

export ALPHAFOLD_DATA=/data/project/bio/shared/alphafold/versions/latest
module purge
module use MX unstable
module load alphafold/2.1.1
conda activate "${ALPHAFOLD_ENV:?"Error: ALPHAFOLD_ENV not set. Try 'module use MX unstable; module load alphafold'"}"

echo "hostname=$(hostname)"
echo "python=$(which python)"
echo "ALPHAFOLD_DATA=$(realpath "$ALPHAFOLD_DATA")"

python "${ALPHAFOLD_DIR:?Error loading module}/bin/alphafold_runner.py" -v 0 "$@"

