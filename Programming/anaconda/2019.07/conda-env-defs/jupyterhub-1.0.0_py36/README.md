TODO


Installation done on pmod6

```
conda env create -f jupyterhub-1.0.0_py36.yml

conda activate jupyterhub-1.0.0_py36.yml
```

The current production versions of the spawners (e.g. batchspawner-0.81) are
not compatible with jupyterhub-1.0.0. So, one is forced to deploy the
development versions.

Installation uses versions of 30.08.2019
in /opt/psi/Programming/anaconda/2019.07/src

```
cd /opt/psi/Programming/anaconda/2019.07/src
git clone https://github.com/jupyterhub/jupyterhub.git
git clone https://github.com/jupyterhub/batchspawner.git
git clone https://github.com/jupyterhub/wrapspawner.git
git clone https://github.com/ResearchComputing/jupyterhub-options-spawner.git

pip install ./batchspawner
pip install ./wrapspawner
pip install ./jupyterhub-options-spawner
```

```
(jupyterhub-1.0.0_py36) [feichtinger-adm@pmod6 src]$ conda list | grep pypi
batchspawner              0.9.0.dev0               pypi_0    pypi
optionsspawner            0.1.0                    pypi_0    pypi
wrapspawner               0.0.1.dev0               pypi_0    pypi

```
