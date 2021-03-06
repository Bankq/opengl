/*************************************************
* Author: Hang Qian
* Email: hq577780@sju.edu
* 
* This is the homework 4 of CSC630-Interactive 
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
#define RUNNING 0
#define PAUSE 1
#define STEP 2
#define TRANSLATE 0
#define ROTATE 1

/* window dimensi0ns */
int wh=800;
int ww=600;

float x_view;
float y_view;
float z_view;


float x_eye;
float y_eye;
float z_eye;

int spin;

int current_postion;
int game_state;

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
         {0.99, 1.00, 1.00}};
           
/*ship coordinates for all ships, (x,y,z) for each ship*/
GLfloat ship_coords[NO_SHIPS][3]={{100.0,10.0,10.0},
        {105.0,0.0,15.0}};


/*velocites (translational and rotational) for each ship */
GLfloat ship_velocities[NO_SHIPS][2]={{0.0,2.0},
             {-2.0,1.0}};


/*heading initializations for each ship */
GLfloat ship_headings[NO_SHIPS]={0.0, 180.0};


/*lighting*/
GLfloat light_postition[] = {1.0,1.0,0.0,0};
GLfloat ambient_color[] = {0.2,0.2,0.2,1.0};
GLfloat diffuse_color[] = {1.0,1.0,1.0,1.0};
GLfloat specular_color[] = {2.0,2.0,2.0,1.0};
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat mat_emission[] = { 0.0,0.0,0.0,0.0,1.0};
GLfloat mat_shininess[] = { 100.0 };

static GLint fogMode;

Ship* ship1;
Ship* ship2;



/****************************/
void init(void);
void draw_clouds(void);
void draw_ship(Ship* ship);
void draw_ships(void);
void draw_ground(void);
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void move(void);
void change_view_position(void);
void change_eye_position(void);
void timer(int id);
void mouse(int button, int state, int x, int y);
void switch_ship(void);
void pause_game(void);
void debug(void);
void step_game(void);
void speed_up(int mode);
void slow_down(int mode);
/****************************/








void init(void){


  glClearColor(1,1,1,1);
  glShadeModel(GL_SMOOTH);
  //  glColorMaterial( GL_FRONT_AND_BACK, GL_EMISSION );
  


  glLightfv(GL_LIGHT0,GL_POSITION,light_postition);
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_color);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_color);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular_color);
	  
  glLightfv(GL_LIGHT0,GL_POSITION,light_postition);
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_color);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_color);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular_color);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mat_emission);
  //  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,
  
  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
 

  /* add fog here */
  glEnable(GL_FOG);
  {
	GLfloat fogColor[] = {0.5,0.5,0.5,1.0};

	fogMode = GL_EXP2;//GL_EXP;
	glFogi(GL_FOG_MODE,fogMode);
	glFogi(GL_FOG_INDEX,32);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogf(GL_FOG_DENSITY,0.35);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START,1.0);
	glFogf(GL_FOG_END, 5.0);
	glClearIndex((GLfloat) 17);

  }

  glEnable(GL_LINE_SMOOTH);
   glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);


  //Initialize the two ships
  ship1 = new Ship(ship_coords[0][0],
                   ship_coords[0][1],
                   ship_coords[0][2],// coordinate
                   0.0,
                   1.0,
                   0.0,//direction
                   ship_velocities[0][0],
                   ship_velocities[0][1]); // velocity
  ship2 = new Ship(ship_coords[1][0],
                   ship_coords[1][1],
                   ship_coords[1][2],
                   0.0,
                   -1.0,
                   0.0,
                   ship_velocities[1][0],
                   ship_velocities[1][1]);

  x_eye = ship1->px;
  y_eye = ship1->py;
  z_eye = ship1->pz;

  x_view = ship1->dx + ship1->px;
  y_view = ship1->dy + ship1->py;
  z_view = ship1->dz + ship1->pz;

  current_postion = 0;
  spin = 0 ;

}

void draw_ground(){
  glPushMatrix();
  glColor3f(0.0,0.0,0.0);
  glRectf(-999999.0,-999999.0,999999.0,999999.0);
  glPopMatrix();
}


void draw_clouds(){
  for(int i=0; i<NO_CLOUDS; i++){
    glPushMatrix();
    glColor3fv(cloud_colors[i]);
    glTranslatef(cloud_coords[i][0],
                 cloud_coords[i][1],
                 cloud_coords[i][2]);
    glutSolidSphere(SPHERERADIUS,NO_SLICES,NO_STACKS);
    glPopMatrix();
  }
}

void draw_ship(Ship* ship){
  glPushMatrix();
  glColor4fv(ship_color);

  // move to position
  glTranslatef(ship->px,ship->py,ship->pz);

  // find heading direction
  //glRotatef(ship->dx,1.0,0.0,0.0);
  //glRotatef(ship->dy,0.0,1.0,0.0);
  //glRotatef(ship->dz,0.0,0.0,1.0);
  //glRotatef(90,0.0,0.0,1.0);


  // do self rotation
  glRotatef(ship->angle,1.0,0.0,0.0);

  // draw horizontal torus
  glutSolidTorus(INNER,OUTER,NO_SIDES,NO_RINGS);

  // draw vertical torus
  glRotatef(90,1.0,0.0,0.0);

  glutSolidTorus(INNER,OUTER,NO_SIDES,NO_RINGS);
  glPopMatrix();
}

void draw_ships(){
  if(current_postion == 1){
	draw_ship(ship1);
	draw_ship(ship2);
  }
  else{
	draw_ship(ship2);
	draw_ship(ship1);
  }

}



void display(){

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  //  gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
  glPushMatrix();
  glRotatef(spin,1.0,1.0,1.0);
  GLfloat pos[] = {ship1->px,ship1->py,ship1->pz};
  glLightfv(GL_LIGHT1,GL_POSITION,pos);
  glPopMatrix();
  glPopMatrix();

  glLoadIdentity(); 
  gluLookAt(x_eye,y_eye,z_eye,
            x_view,y_view,z_view,
            0.0,0.0,1.0);
  draw_ground();
  draw_clouds();
  draw_ships();

  glutSwapBuffers();
}

void reshape(int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   gluPerspective(FOVY,(GLfloat)w/h,NEAR,FAR);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
  case 'q':
	exit(0);
  case 'p':
	pause_game();
	break;
  case 'a':
	speed_up(TRANSLATE);
	break;
  case 's':
	slow_down(TRANSLATE);
	break;
  case 'l':
	speed_up(ROTATE);
	break;
  case 'k':
	slow_down(ROTATE);
	break;
  case 'f':
  case 'F':
	if( fogMode == GL_EXP){
	  fogMode = GL_EXP2;
	  printf("Fog mode is GL_EXP2\n");
	}
	else if ( fogMode == GL_EXP2){
	  fogMode = GL_LINEAR;
	  printf("Fog mode is GL_LINEAR\n");
	}
	else if ( fogMode == GL_LINEAR){
	  fogMode = GL_EXP;
	  printf("Fog mode is GL_EXP\n");
	}
	glFogi(GL_FOG_MODE,fogMode);
	glutPostRedisplay();
	break;
  case 'y':
	glDisable(GL_FOG);
	glutPostRedisplay();
	break;
  case 'u':
	glEnable(GL_FOG);
	glutPostRedisplay();
	break;
  default:
	break;
  }
}

void move(){
  ship1->move();
  ship2->move();
  spin  = ( spin + 30 ) % 360;
}

void speed_up(int mode){
  if ( mode == TRANSLATE ){
    // speed up heading velocity
    if ( current_postion  == 0 ){
      ship1->v += SHIP_TVEL_INC;
    }
    else if ( current_postion == 1) {
      ship2->v += SHIP_TVEL_INC;
    }
  }
  else if( mode == ROTATE ){
    if( current_postion == 0 ){
      ship1->vr += SHIP_RVEL_INC;
    }
    else if ( current_postion == 1 ){
      ship2->vr += SHIP_RVEL_INC;
    }
  }
  glutPostRedisplay();
}

void slow_down(int mode){
  if ( mode == TRANSLATE ){
    // speed up heading velocity
    if ( current_postion  == 0 ){
      ship1->v += SHIP_TVEL_DEC;
    }
    else if ( current_postion == 1) {
      ship2->v += SHIP_TVEL_DEC;
    }
  }
  else if( mode == ROTATE ){
    if( current_postion == 0 ){
      ship1->vr += SHIP_RVEL_DEC;
    }
    else if ( current_postion == 1 ){
      ship2->vr += SHIP_RVEL_DEC;
    }
  }
  glutPostRedisplay();  
}
void switch_ship(){
  if ( current_postion == 0){
    current_postion = 1;
  }
  else{
    current_postion = 0;
  }
  glutPostRedisplay();
}

void change_view_position(){
  if( current_postion == 0){
    // eye on ship1
    x_view = ship1->dx + ship1->px;
    y_view = ship1->dy + ship1->py;
    z_view = ship1->dz + ship1->pz;
  }
  else{
    x_view = ship2->dx + ship2->px;
    y_view = ship2->dy + ship2->py;
    z_view = ship2->dz + ship2->pz;    
  }   
}


void change_eye_position(){
  if( current_postion == 0){
    // eye on ship1
    x_eye = ship1->px;
    y_eye = ship1->py;
    z_eye = ship1->pz;

  }
  else{
    x_eye = ship2->px;
    y_eye = ship2->py;
    z_eye = ship2->pz;
    
  }   
}

void pause_game(){
  if ( game_state != PAUSE ){
    game_state = PAUSE;
  }
  else{
    game_state = RUNNING;
  }
}

void debug(){
  ship1->display();
  ship2->display();
}

void step_game(){
  if ( game_state != STEP ){
    game_state = STEP;
  }
  move();
  debug();
  glutPostRedisplay();
}

void timer(int id){
  if( game_state == RUNNING){
    move();    
  }
  change_eye_position();
  change_view_position();
  glutPostRedisplay();
  glutTimerFunc(TIMER_TOGGLE,timer,0);
  
}


void mouse(int button, int state, int x, int y){
  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    switch_ship();
  }
  if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
    pause_game();
  }
  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    step_game();
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






















  
