# napari-boxmanager

The napari module is built in combination with the crYOLO module : 

From crYOLO/1.9.9 crYOLO exists as two different conda envs, one crYOLO (code itself) env, one napari (visualization) env. 
The installation notes recommend to link one into another, on Merlin7 simply two different modules and envs exist.
Users need to load one env in one terminal ( crYOLO itself) and another for visualization (napari).

## Adding New Versions

Adding new versions: change the environment file in the build folder accordingly (and the config.yaml file)  and run the build script. 

