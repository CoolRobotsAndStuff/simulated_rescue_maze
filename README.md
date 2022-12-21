# IITA - Robocup 2023 - Simulated Rescue Maze

## Instalation

### Ubuntu

#### Necesary libraries

```
sudo apt install -y g++ cmake make git libgtk2.0-dev pkg-config
```

#### Install Open CV

https://www.geeksforgeeks.org/how-to-install-opencv-in-c-on-linux/

#### Clone the repo
```
git clone https://github.com/opencv/opencv.git
```

#### Make Makefile with CMake

Go to ```~/simulated_rescue_maze/code/build/``` in a terminal and execute:
```
cmake .. -G "Unix Makefiles"
```
Done!


Now, to use the code in Erebus, go back to the ```~/simulated_rescue_maze/code``` directory.

Set the environment variable ```EREBUS_DIRECTORY``` to the home direcotry of your Erebus installation. For example:
```
export EREBUS_DIRECTORY=/home/username/Erebus-v21_2_4
```
Run the "create_makefiles.sh" script, so that the makefiles are created and the ```WEBOTS_HOME``` environment value is defined:
```
./create_makefiles.sh
```
Hop on the "compile.sh" script and set your Erebus Directory path. For example:
```
"/home/joaquin/Documents/RCJ2023-SimulatedRescueMaze/Erebus-v21_2_4/game/controllers/robot0Controller"
```
Run the compile script:
```
./compile.sh
```
And when you press play in the Erebus window in Webots, your code should run!

