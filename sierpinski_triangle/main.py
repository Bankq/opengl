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




def main():
    print "---------Bank------------"
    glutInit(sys.argv)
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(800,800)
    glutCreateWindow("Bank-Game")
    glutDisplayFunc(display)
    init ()
    glutMainLoop()    

def init():
    glClearColor(1,1,1,1)
    glViewport(0,0,800,800)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0.0,800.0,0.0,800.0)
   
    
def display():
  glClear(GL_COLOR_BUFFER_BIT)
  a = [400.0,400+sqrt(3)/3*(sqrt(3)*400)]
  b = [400-sqrt(3)*200,400-sqrt(3)/6*(sqrt(3)*400)]
  c = [400+sqrt(3)*200,400-sqrt(3)/6*(sqrt(3)*400)]
  
  glColor3f(1,0,0)
  glBegin(GL_POLYGON)
    
  glVertex2f(a[0],a[1])
  glVertex2f(b[0],b[1])
  glVertex2f(c[0],c[1])

  glEnd()
  draw(a,b,c,0)

def draw(a,b,c,level):

  if level <= 6:
    print a,b,c
    glColor3f(1,1,1)
    
    glBegin(GL_POLYGON)
    
    glVertex2f((a[0]+b[0])/2,(a[1]+b[1])/2)
    glVertex2f((b[0]+c[0])/2,(b[1]+c[1])/2)
    glVertex2f((c[0]+a[0])/2,(c[1]+a[1])/2)

    glEnd()
    glFlush()
    level = level + 1
    draw([(a[0]+b[0])/2,(a[1]+b[1])/2],b,[(b[0]+c[0])/2,(b[1]+c[1])/2],level)
    draw(a,[(a[0]+b[0])/2,(a[1]+b[1])/2],[(c[0]+a[0])/2,(c[1]+a[1])/2],level)
    draw([(c[0]+a[0])/2,(c[1]+a[1])/2],[(b[0]+c[0])/2,(b[1]+c[1])/2],c,level)
  else :
    print 'return'
    return
  

if __name__ == '__main__':
  main()
