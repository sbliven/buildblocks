# INSTALLATION

IMPORTANT! DON'T INSTALL WITH AURISTOR. Use an OpenAFS system (e.g. *pmod7*).
GLIBC>=2.14 is required (so pmod6 doesn't work).

In theory, the yaml environment contains all the requirements. This should be
updated for each version to change the env name and update requirements.

    CONDA_COPY_ALWAYS=1 conda env create --file cryodrgn.yml
    conda activate cryodrgn-1.1.0

In practice, some manual installation was required following the github
instructions. (Most errors ultimately stemed from quota issues, so try the
file-based install next version).

Now configure jupyterlab:

    jupyter labextension install @jupyter-widgets/jupyterlab-manager --no-build
    jupyter labextension install jupyterlab-plotly --no-build
    jupyter labextension install plotlywidget --no-build
    jupyter lab build

## Pmodules

After installing a new environment, wrap it in the EM/cryodrgn module

## Testing

To test:

    conda activate cryodrgn-1.1.0
    cryodrgn -h

    git clone https://github.com/zhonge/cryodrgn.git
    cd cryodrgn/testing
    ./quicktest.sh

It should take ~20 seconds to run and reach a final loss around 0.08 in version
1.0 and 0.03 in version 1.1+. Note that the output should contain  Use cuda
True in the first few lines.
