# A simple 3-D based OpenGL game
## Introduction

This is a simple 3-D based(2-D view) game written in OpenGL.

We will think of the game as taking place in three dimensional space, but the graphics will be drawn in the plane. We have a set of objects, called things. Each thing is drawn as a colored square on the (x,y) plane.The things move around within a large square window with constant speed. Whenever a thing hits the side of the square it bounces off, while maintaining its speed. Initially the things start with random locations and random velocities.

## Files
* main.cc: the main function entrance. Defined all opengl functions and routines here.
* thing.h: the header file of definition of Class Thing
* thing.cc: the implementation of Class Thing
* bomb.h: the header file of definition of Class Bomb
* bomb.cc: the implementation of Class Bomb
* Makefile: makefile if compiled with GNU C Compiler kit

## How to compile
### Windows
* Create a new project in Visual C++ or any other IDE, which is needed to have OpenGL and GLUT installed
* Compile it and run it

### Linux/Unix & Mac OS X
* Open a terminal
* go into the file folder
* make: to compile it
* make clean: to delete all the .o files and executable files
* ./exec to have some fun!

## Instruction

Drop the bomb use your left mouse button, as it drop downward every level, you will see its color changes toward totally transparent.

If you hit the thing on certain level, there will be scores changes as follow:

* level 0: -4000
* level 1: -2000
* level 2: -1000
* level 3: +1000
* level 4: +2000

And, although there's no bombs number limit, every bomb you drop will cause a 100 score lose. 

Use 'q' on keyboard to exit
Click middle button ( or 'p' on keyboarde) will pause the game and fortunately we can resume it by click it again.
Click right button will execute step by step ,and every thing's status will output to standard output.

After you destroy all the bad things, the game is over.

There's a time limit, so hurry up!

## Features
It implemented all the features describeb in the requiremnt(guideline)

### Extra features
* Aiming help
* Time and score display
* Pause view
* End view
* smooth view

## Known Bugs
There's no spotted bugs until I wrote this file. If you find any bugs or problems, please contact me or, if you wish, modify it yourself.


