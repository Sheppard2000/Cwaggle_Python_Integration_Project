# Comp4780_Cwaggle_Python_Integration_Project
A Project wherein the goal is to allow for the control of cwaggle worlds/agents in python, 
specifically using Open AI Gym, to allow for the use of python based RL packages for further 
RL experiments in the cwaggle environment.


the Testing folder was used for learning pybind11 and the different ways it can be used to 
make python modules out of C++ code

Most of the work is currently being done in the cwaggle_with_pybind directory, 
pybind11 bindings are being written in bridge.cpp under cwaggle_with_pybind/cwaggle/src/cwaggle_bridge.
The testing code in python is being done in test.py under cwaggle_with_pybind/cwaggle/bin.
Some older files used during the learning/testing process were kept and contain outdated tests, code, commands, and tasks.
the files were kept so that I could more easily look back and remeber what I had already done/tried. 
Not all files were kept however, so if there are any holes, that is why.

If there are any questions or comments, I can be contacted at tjsheppard@mun.ca,
and my Discord handel is TSheppard#2195.

# QuickStart Guide

For those who wish to use my work, here is a little guide to help you get started. Hopefully it will be of  some help. 

In order to properly use this project, you will need to have Pybind11 set up, and in order to use cwaggle_gym you will also need to have OpenAI Gym. If you wish to run the RL training experiments I made you will additionally need to have Tensorflow and Keras.

My work in building a module so that CWaggle can be use in python comprises of a custom PybindControl class, located in cwaggle_with_pybind/cwaggle/src/pybind_control/control_bridge.cpp.

The PybindControl Class is created to store pointers towards a cwaggle world, simulator, and GUI. The world and simulator are created when the PybindControl class is initialized, and the GUI is made in its own makeGUI function, so that visualization can be separated from the running of the simulator. The various functions in PybindControl are used to run the various aspects of the CWaggle simulation, such as controlling any robots in the world and returning sensor data from sensors attached to the robots. These functions are then exposed to python in  the Pybind11 module at the bottom of the file. If you want to add new functions to be used on the python side, do not forget to add those functions to the Pybind11 module.
NOTE: the cwaggle Entity class is also exposed through the module so that the Python side does not raise any errors about unknown class/object types.

The makefile to compile the Pybind module is located in cwaggle_with_pybind/cwaggle/Makefile

The tests used to ensure that the Pybind module works are located in cwaggle_with_pybind/cwaggle/bin/test.py

The CWaggle Master folder contains a copy of the original CWaggle code copied from https://github.com/davechurchill/cwaggle
It was used as a reference to aid in the use of the CWaggle aspects of the code.

The cwaggle_gym and the associated RL agent testing are continued in cwaggle_with_pybind/cwaggle/bin/cwaggle_gym.py

If you wish to see how the PybindControl class is used to create and control CWaggle in python, both cwaggle_with_pybind/cwaggle/bin/test.py and cwaggle_with_pybind/cwaggle/bin/cwaggle_gym.py can be used as references.

The Testing, new_bridge_testing, and python_integration folders are legacy folders used in early experiments while trying to figure out how to go about using Pybind11 to allow for CWaggle to be used in Python.
