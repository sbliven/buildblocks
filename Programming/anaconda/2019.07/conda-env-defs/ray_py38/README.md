Ray has to be installed by pip into this environment

#######
conda env create -f ray_py38/ray_py38.yml

pip install -U ray
########


The pip install brings in these additional dependencies
########
(ray_py38.yml) [feichtinger-adm@pmod6 conda-env-defs]$ conda list | grep pypi
aiohttp-cors              0.7.0                    pypi_0    pypi
aioredis                  1.3.1                    pypi_0    pypi
beautifulsoup4            4.9.3                    pypi_0    pypi
blessings                 1.7                      pypi_0    pypi
colorama                  0.4.4                    pypi_0    pypi
colorful                  0.5.4                    pypi_0    pypi
filelock                  3.0.12                   pypi_0    pypi
google                    3.0.0                    pypi_0    pypi
google-api-core           1.26.3                   pypi_0    pypi
googleapis-common-protos  1.53.0                   pypi_0    pypi
gpustat                   0.6.0                    pypi_0    pypi
hiredis                   2.0.0                    pypi_0    pypi
nvidia-ml-py3             7.352.0                  pypi_0    pypi
opencensus                0.7.13                   pypi_0    pypi
opencensus-context        0.1.2                    pypi_0    pypi
py-spy                    0.3.7                    pypi_0    pypi
ray                       1.0.1.post1              pypi_0    pypi
redis                     3.4.1                    pypi_0    pypi
soupsieve                 2.2.1                    pypi_0    pypi
##########

2021-05-17 Derek, initial install

