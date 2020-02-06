# INSTALLATION

IMPORTANT! DON'T INSTALL WITH AURISTOR. Use an OpenAFS system (e.g. pmod6)

    CONDA_COPY_ALWAYS=1 conda env create --file cryocare.yml
    conda activate cryocare

Now configure jupyter

    cp share/jupyter/kernels/python3/kernel.json $CONDA_PREFIX/share/jupyter/kernels/python3/
    cp etc/conda/activate.d/cryocare-env.sh $CONDA_PREFIX/etc/conda/activate.d/
    cp etc/conda/deactivate.d/cryocare-env.sh $CONDA_PREFIX/etc/conda/deactivate.d/

## Package notes

- cudatoolkit version should ideally match merlin6's CUDA module
  (required by the MotionCor2 package). However, tensorflow needs cuda 10.0 while
  no MotionCor2 binary is available. For now, having a different version in
  conda and modules is working OK, but it could cause problems with future compilation.
- You can test GPU support by running this command on a GPU machine:
  `python -c 'import tensorflow as tf; print(tf.test.is_gpu_available())'`

