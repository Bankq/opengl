# A simple 3-D based OpenGL game
## Introduction

We will think of the game as taking place in three dimensional space, but the graphics will be drawn in the plane. We have a set of objects, called things. Each thing is drawn as a colored square on the (x,y) plane.The things move around within a large square window with constant speed. Whenever a thing hits the side of the square it bounces off, while maintaining its speed. Initially the things start with random locations and random velocities.

## Tech Spec
I deploy it in Python use PyOpenGL, it can be executed on any machine which have python and pyopengl installed. You can use your mouse and keyboard to play.

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
Click middle button will pause the game and fortunately we can resume it by click it again.
Click right button will execute step by step ,and every thing's status will output to standard output.


* make 3d view
* make thing move smoothly
* add end view
* indicate the hit thing
