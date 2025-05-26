# TOPAZ

The topaz module is build for using it with the cryosparc software. An executable path to the topaz binary needs to be provided in cryosparc. 

## Adding New Versions

Adding new versions: change the environment file in the build folder accordingly (and the config.yaml file)  and run the build script.
IMPORTANT: Build it on the GPU node , otherwise the pytorch installation will not enable GPU support. 

## HINTS

Current successful environment.yaml file: 

channels:
  - tbepler
  - pytorch
dependencies:
  - python=3.6
  - cudatoolkit
  - topaz 
  - pytorch

- specifing cudatoolkit version of 11.8 failed for GPU support (see below)
- specifing higher python/cudatoolkit versions lead to higher pytorch versions, which again failed for topaz to run successful (https://discuss.cryosparc.com/t/topaz-train-typeerror-concat-takes-1-positional-argument-but-2-were-given/11240/18) 

## Versions

Nov. 2024:  0.2.5 (TOPAZ) with 
```
python3.6
cudatoolkit               11.3.1               h2bc3f7f_2  
pytorch                   1.10.2          py3.6_cuda11.3_cudnn8.2.0_0
pytorch-mutex             1.0                        cuda
```
