#!/usr/bin/env python
"""
Wrapper script for Alphafold 2, with automatic setting of common options

usage: python alphafold_runner.py [alphafold options] input.fa
"""
import sys
import os
import importlib
import subprocess
import logging
import argparse
from datetime import date
from pathlib import Path
from typing import Union
from absl import app
from absl.flags import FLAGS
from absl import logging

def import_alphafold():
    "Import run_alphafold.py from ALPHAFOLD_HOME"
    home = os.environ.get('ALPHAFOLD_HOME', str(Path(__file__).parent.resolve("../alphafold")))
    sys.path.append(home)
    try:
        return importlib.import_module("run_alphafold")
    except ImportError:
        sys.stderr.write(f"Unable to find run_alphafold.py\n")
        sys.stderr.write(f"path:{', '.join(sys.path)}")
        sys.exit(1)
af =  import_alphafold()

def multi_fasta(fasta_path):
    entries = 0
    with open(fasta_path, 'r') as fasta:
        for line in fasta:
            if line and line[0] == '>':
                entries += 1
                if entries > 1:
                    return True
    return False


def guess_model_preset(fasta_paths):
    if any(multi_fasta(f) for f in fasta_paths):
        logging.info("Input appears to be multimer")
        return "multimer"
    logging.info("Input appears to be monomer")
    return "monomer"


def main(argv):
    """Set some option defaults and then call alphafold's main method

    Most alphafold options have defaults set automatically:

    - database files are set from the ALPHAFOLD_DATA variable or the --data_dir option
      (assuming the versioned layout, which differs slightly from the default)
    - `--model_preset` is set to either monomer or multimer depending on the number of sequences in the fasta file
    - `--max_template_date` defaults to the current date
    """


    if len(argv) > 2:
        raise app.UsageError('Too many command-line arguments.')

    # Accept positional fasta_paths
    if len(argv) > 1:
        if FLAGS["fasta_paths"].present:
            raise app.UsageError("Both the --fasta_paths option and a fasta file argument were given")
        FLAGS["fasta_paths"].parse(argv[1])
    elif not FLAGS.fasta_paths:
        raise app.UsageError("No fasta file specified")

    # Database flags
    if FLAGS["data_dir"].present:
        data_dir = FLAGS.data_dir
    elif "ALPHAFOLD_DATA" in os.environ:
        data_dir = os.environ["ALPHAFOLD_DATA"]
        logging.info(f"Using ALPHAFOLD_DATA={data_dir}")
        FLAGS['data_dir'].value = data_dir
    else:
        raise app.UsageError("Specify --data_dir or set ALPHAFOLD_DATA")

    if not FLAGS["model_preset"].present:
        FLAGS.model_preset = guess_model_preset(FLAGS.fasta_paths)

    use_small_bfd = FLAGS.db_preset == 'reduced_dbs'

    if use_small_bfd:
        if not FLAGS.small_bfd_database_path:
            FLAGS.small_bfd_database_path = os.path.join(data_dir, "small_bfd", "bfd-first_non_concensus_sequences.fasta")
    else:
        if not FLAGS.bfd_database_path:
            FLAGS.bfd_database_path = os.path.join(data_dir, "bfd", "bfd_metaclust_clu_complete_id30_c90_final_seq.sorted_opt")
        if not FLAGS.uniclust30_database_path:
            FLAGS.uniclust30_database_path = os.path.join(data_dir, "uniclust30", "uniclust30_2018_08")

    run_multimer_system = 'multimer' in FLAGS.model_preset

    if run_multimer_system:
        if not FLAGS.pdb_seqres_database_path:
            FLAGS.pdb_seqres_database_path = os.path.join(data_dir, "pdb", "pdb_seqres.txt")
        if not FLAGS.uniprot_database_path:
            FLAGS.uniprot_database_path = os.path.join(data_dir, "uniprot", "uniprot.fasta")
    else:
        if not FLAGS.pdb70_database_path:
            FLAGS.pdb70_database_path = os.path.join(data_dir, "pdb70", "pdb70")

    if not FLAGS.mgnify_database_path:
        FLAGS.mgnify_database_path = os.path.join(data_dir, "mgnify", "mgy_clusters_2018_12.fa")
    if not FLAGS.obsolete_pdbs_path:
        FLAGS.obsolete_pdbs_path = os.path.join(data_dir, "pdb", "obsolete.dat")
    if not FLAGS.template_mmcif_dir:
        FLAGS.template_mmcif_dir = os.path.join(data_dir, "pdb", "mmcif_files")
    if not FLAGS.uniref90_database_path:
        FLAGS.uniref90_database_path = os.path.join(data_dir, "uniprot", "uniref90.fasta")

    if not FLAGS.output_dir:
        FLAGS.output_dir = os.getcwd()

    if not FLAGS.max_template_date:
        FLAGS["max_template_date"].parse(date.today().isoformat())

    af.main(argv[0:1])


if __name__ == "__main__":
    app.run(main)

