/*************************************************
* Author: Hang Qian
* Email: hq577780@sju.edu
* 
* This is the homework 3 of CSC630-Interactive 
* Comupter Graphic of 2011 fall.
*
*    
*    This file is part of the program.
*
*    The program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with the program.  If not, see <http://www.gnu.org/licenses/>.

**************************************************/



#include "stdlib.h"

#include <iostream>


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "ship.h"






using namespace std;

#define FOVY 60

#define NO_SHIPS 2           /*number of ships */
#define NO_CLOUDS 8          /*number of clouds */
#define SHIP_TVEL_INC 2      /*incremen/decrement amounts for ship velocities */
#define SHIP_TVEL_DEC -2
#define SHIP_RVEL_INC 2
#define SHIP_RVEL_DEC -2
#define INNER 1              /*inner radius of torus */
#define OUTER 4              /*outer radius of torus */ 
#define SPHERERADIUS 10            /*radius of sphere */
#define NEAR 1               /*clipping plane near and far */
#define FAR 10000
#define TIMER_TOGGLE 100


/* window dimensi0ns */
int wh=300;
int ww=400;

float x_view;
float y_view;
float z_view;


float x_eye;
float y_eye;
float z_eye;

int current_postion;

/* parameters for drawing sphere and torus */
GLint NO_STACKS=20;
GLint NO_SLICES=20;
GLint NO_SIDES=20;
GLint NO_RINGS=20;


GLfloat ship_color[4]={1.0,0.627,0.478, 1.0};  /*color of a ship */
GLfloat ground_color[4]={0.0, 1.0, 0.0, 1.0}; 
 
/* The ground should be located at z=0 plane, you can use (0,0,0) as the lower left corner and (200, 200, 0) as the upper right corner. */

/*several initializations */
/* cloud coordinates(x,y,z) for each cloud */ 
GLfloat cloud_coords[NO_CLOUDS][3]={{30, 30, 30},
         {30, 170, 15},
         {80, 110, 25},
         {70,  60, 12},
         {90, 150, 13},
         {120,  80, 17},
         {150,  40, 15},
         {160, 170, 22}};

/*cloud colors(rgb) for each cloud */
GLfloat cloud_colors[NO_CLOUDS][3]={{0.30, 0.30, 0.30},
         {1.00, 0.00, 0.00},
         {0.00, 1.00, 0.00},
         {0.00, 0.00, 1.00},
         {1.00, 1.00, 0.00},
         {1.00, 0.00, 1.00},
         {0.00, 1.00, 1.00},
         {1.00, 1.00, 1.00}};
           
/*ship coordinates for all ships, (x,y,z) for each ship*/
GLfloat ship_coords[NO_SHIPS][3]={{100.0,10.0,10.0},
        {105.0,0.0,15.0}};


/*velocites (translational and rotational) for each ship */
GLfloat ship_velocities[NO_SHIPS][2]={{0.0,0.0},
             {-2.0,0.0}};


/*heading initializations for each ship */
GLfloat ship_headings[NO_SHIPS]={0.0, 180.0};



Ship* ship1;
Ship* ship2;

void init(void){
  glEnable(GL_LINE_SMOOTH);

  glClearColor(1,1,1,1);
  glShadeModel(GL_SMOOTH);

  //Initialize the two ships
  ship1 = new Ship(ship_coords[0][0],
                   ship_coords[0][1],
                   ship_coords[0][2],
                   ship_velocities[0][0],
                   ship_velocities[0][1],
                   0.0); // no pre-requirement for vz
  ship2 = new Ship(ship_coords[1][0],
                   ship_coords[1][1],
                   ship_coords[1][2],
                   ship_velocities[1][0],
                   ship_velocities[1][1],
                   0.0);

  x_eye = ship1->px;
  y_eye = ship1->py;
  z_eye = ship1->pz;

  x_view = ship2->px;
  y_view = ship2->py;
  z_view = ship2->pz;

  current_postion = 0;

}

void draw_clouds(){
  for(int i=0; i<NO_CLOUDS; i++){
    glPushMatrix();
    glColor3fv(cloud_colors[i]);
    glTranslatef(cloud_coords[i][0],
                 cloud_coords[i][1],
                 cloud_coords[i][2]);
    glutWireSphere(SPHERERADIUS,NO_SLICES,NO_STACKS);
    glPopMatrix();
  }
}

void draw_ship(Ship* ship){
  glPushMatrix();
  glColor4fv(ship_color);
  glTranslatef(ship->px,ship->py,ship->pz);
  glutWireTorus(INNER,OUTER,NO_SIDES,NO_RINGS);
  glRotatef(90,1.0,0.0,0.0);
  glutWireTorus(INNER,OUTER,NO_SIDES,NO_RINGS);
  glPopMatrix();
}

void draw_ships(){
  draw_ship(ship1);
  draw_ship(ship2);

}



void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity(); 
  gluLookAt (x_eye, y_eye, z_eye, 
            x_view,y_view,z_view,
            0.0, 0.0, 1.0);
  draw_clouds();
  draw_ships();

  glutSwapBuffers();
}

void reshape(int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   gluPerspective(FOVY,(GLfloat)w/h,NEAR,FAR);
   //glOrtho(-10.0,10.0,-10.0,10.0,1.0,20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
    case 'q':
      exit(0);
    case 'a':
      x_view -= 5;
      glutPostRedisplay();
      break;
    case 'd':
      x_view += 5;
      glutPostRedisplay();
      break;
    case 'w':
      z_view += 5;
      glutPostRedisplay();
      break;
    case 's':
      z_view -= 5;
      glutPostRedisplay();
      break;
    case 'u':
      x_view = ship1->px;
      y_view = ship1->py;
      z_view = ship2->pz;
      glutPostRedisplay();
      break;
    case 'i':
      x_view = ship2->px;
      y_view = ship2->py;
      z_view = ship2->pz;
      glutPostRedisplay();
      break;
    default:
      break;
  }
}

void move(){
  ship1->move();
  ship2->move();
}


void change_view_position(){
  if( current_postion == 0){
    // eye on ship1
    x_view = ship1->px;
    y_view = ship1->py;
    z_view = ship1->pz;
  }
  else{
    x_view = ship2->px;
    y_view = ship2->py;
    z_view = ship2->pz;    
  }   
}

void timer(int id){
  move();
  change_view_position();
  glutPostRedisplay();
  glutTimerFunc(TIMER_TOGGLE,timer,0);
  
}

void change_eye_position(){
  if( current_postion == 0){
    // eye on ship1
    current_postion = 1;
    x_eye = ship2->px;
    y_eye = ship2->py;
    z_eye = ship2->pz;

  }
  else{
    current_postion = 0;
    x_eye = ship1->px;
    y_eye = ship1->py;
    z_eye = ship1->pz;
  
  }   
}

void mouse(int button, int state, int x, int y){
  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    change_eye_position();
  }
}

int main( int argc, char** argv) {


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(wh,ww);
  glutCreateWindow("Game");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  //glutPassiveMotionFunc(aim);
  glutTimerFunc(TIMER_TOGGLE, timer, 0);
  init();
  glutMainLoop();
  return 0;
}






















  
