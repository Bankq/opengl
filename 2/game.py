#!/usr/bin/env python -tt

# This is statement is required by the build system to query build info
if __name__ == '__build__':
  raise Exception

import string
__date__ = string.join(string.split('$Date: 2011/10/21 $')[1:3], ' ')
__author__ = 'Hang Qian <ibank.qh@gmail.com>'

try:
  from numpy import *
  from numpy.random import *
except ImportError, err:
  try: 
    from Numeric import *
    from RandomArray import *
  except ImportError, err:
    print "This demo requires the numpy or Numeric extension, sorry"
    import sys
    sys.exit()
    

import string
import sys 
import math

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from thing import Thing
from thing import Bomb



UNIT_WIDTH = 400
UNIT_HEIGHT = 400

score = 100
game_state = 0
time = 1000

color_dict = {
  0:[1,0,0], # red
  1:[1,99.0/255,7.0/255], # tomato
  2:[1,165.0/255,0], # orange
  3:[0,100.0/255,0], # dark green
  4:[0,1,0], # green
}
score_table = {
  0:-4000,
  1:-2000,
  2:-1000,
  3:+1000,
  4:+2000,
  5:0,
  -1:-100,
}

things = list()
bombs = list()




def main():
    glutInit(sys.argv)
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB)
    glutInitWindowSize(UNIT_WIDTH,UNIT_HEIGHT)
    glutCreateWindow("Bank-Game")
    glutDisplayFunc(display)
    glutReshapeFunc(reshape)
    glutTimerFunc(100,timer, 0)
    glutMouseFunc (mouse)
    glutKeyboardFunc(keyboard)
    #glutIdleFunc(idle)
    #glutSpecialFunc(my_special_key)
    init ()
    glutMainLoop()    

def init():
    global things
    global bombs 

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);



    glClearColor(1,1,1,1)
    glShadeModel(GL_SMOOTH)   
    
    glViewport(0,0,UNIT_WIDTH,UNIT_HEIGHT)
    glClear(GL_COLOR_BUFFER_BIT)
    glFlush()
    
    #initialize the thing's list
    for i in range(5):
        same_level_list = list();
        if i < 3:
            for j in range(4):
                same_level_list.append(Thing(i,UNIT_WIDTH,UNIT_HEIGHT))
        else:
            for j in range(4):
                same_level_list.append(Thing(i,UNIT_WIDTH,UNIT_HEIGHT))
        things.append(same_level_list)
    

    #initial time
    if len(sys.argv) > 1:
        global time
        time = sys.argv[1]
    
                  
                                     
    

    
    

def display():
    glClear(GL_COLOR_BUFFER_BIT)
    for i in range(len(things)):
        for j in range(len(things[4-i])):
            draw_thing(things[4-i][j])

    for b in bombs:
        draw_bomb(b)

    display_info()

    
    glutSwapBuffers()

def display_info():
    glPushMatrix()
    glColor3f(0,0,0)
    glRasterPos2f(0,0)
    for c in list("SCORE: "):
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,ord(c))

    glColor3f(0,1,0)
    glRasterPos2f(80,0)
    for c in list(str(score)):
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,ord(c))

    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,ord(' '))

    glColor3f(0,0,0)
    glRasterPos2f(120,0)
    for c in list("TIME: "):
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,ord(c))

    glColor3f(1,0,0)
    glRasterPos2f(180,0)
    for c in list(str(time)):
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,ord(c))
    glPopMatrix()


def draw_bomb(thing):
    glPushMatrix()
    glColor3f(thing.level*0.2,thing.level*0.2,thing.level*0.2)
    half_width = 0.02 * UNIT_WIDTH
    half_height = 0.02 * UNIT_HEIGHT

    glBegin(GL_POLYGON)

    glVertex2f(thing.px - half_width, thing.py + half_height)
    glVertex2f(thing.px + half_width, thing.py + half_height)
    glVertex2f(thing.px + half_width, thing.py - half_height)
    glVertex2f(thing.px - half_width, thing.py - half_height)
    
    glEnd()
    glFlush()

    glPopMatrix()

def draw_thing(thing):

    glPushMatrix()
    color = color_dict[thing.level]
    glColor3fv(color)
    half_width = 0.05 * UNIT_WIDTH
    half_height = 0.05 * UNIT_HEIGHT
    # print half_width
    # print color;
    # print thing.px, ",",thing.py

    glBegin(GL_POLYGON)

    glVertex2f(thing.px - half_width, thing.py + half_height)
    glVertex2f(thing.px + half_width, thing.py + half_height)
    glVertex2f(thing.px + half_width, thing.py - half_height)
    glVertex2f(thing.px - half_width, thing.py - half_height)
    
    glEnd()
    glFlush()

    glPopMatrix()

def reshape(w,h):
    global UNIT_WIDTH
    global UNIT_HEIGHT
    UNIT_WIDTH = w
    UNIT_HEIGHT = h
    glClear(GL_COLOR_BUFFER_BIT)
    glViewport (0, 0, UNIT_WIDTH, UNIT_HEIGHT)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity();               
    gluOrtho2D(0,UNIT_WIDTH,0,UNIT_HEIGHT)
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay()
            
def keyboard(key,x,y):
    if key == 'q':
        sys.exit()

def mouse(button,state,x,y):
    global bombs
    global score
    global game_state
    
    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        #draw a bomb
        score += score_table[-1]
        bombs.append(Bomb(x,UNIT_HEIGHT-y))
    
    if button == GLUT_MIDDLE_BUTTON and state == GLUT_DOWN:
        if game_state == 0:
            game_state = 1
        elif game_state == 1:
            game_state = 0

    if button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
        if game_state == 0:
            game_state =1
        elif game_state == 1:
            move()
            console_output()
            glutPostRedisplay()


def timer(id):
    if game_state == 0:
        move()  

    glutPostRedisplay()
    glutTimerFunc(100,timer,0)

    


def move():
    global score
    global time

    time -= 1

    for level_list in things:
        for thing in level_list:
            # move every thing
            border_check(thing)
            thing.move()
    
    for b in bombs:
        b.move()
        if b.level == 5:
            #check if bomb hit the ground
            bombs.remove(b)
        else:
            for thing in things[b.level]:
                # check all things in the same level with the current bomb
                if abs( b.px - thing.px ) <= 0.03 * UNIT_WIDTH and abs( b.py - thing.py ) <= 0.03 * UNIT_HEIGHT:
                    things[b.level].remove(thing)
                    #renew score
                    score += score_table[b.level]
                    

def border_check(thing):
        if thing.px + thing.vx > UNIT_WIDTH:
            thing.px = UNIT_WIDTH + ( UNIT_WIDTH - thing.px)
            thing.vx = -thing.vx

        if thing.px + thing.vx < 0:
            thing.px = -thing.px
            thing.vx = -thing.vx

        if thing.py + thing.vy > UNIT_HEIGHT:
            thing.py = UNIT_HEIGHT + ( UNIT_HEIGHT - thing.py)
            thing.vy = -thing.vy

        if thing.py + thing.vy < 0:
            thing.py = -thing.py
            thing.vy = -thing.vy
            
            
def console_output():
    print "---------------------------"
    print "Current Window Size:"
    print "Width, ",UNIT_WIDTH," | Height: ", UNIT_HEIGHT
    print "---------------------------"      
    print "Things"
    print ""
    for same_level_list in things:
        print "- - - - - - - - - - - -"
        for thing in same_level_list:
            print "|","---" * (thing.level), "> X: ",thing.px," , Y: ",thing.py
    print "---------------------------"
    print "Bombs"
    print ""
    for bomb in bombs:
        print "Current level: ",bomb.level,"| X: ",thing.px," , Y: ",thing.py



if __name__ == "__main__":
    main()



















