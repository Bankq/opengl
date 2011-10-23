


/*****************************************************
 This program is the homework1 of CSC630-Interactive
 Computer Graphic course which mentored by Dr.Wei.

 It draws a window put a diamond, a triangle, and a cir-
 cle in it. It has the following features:

 1. click left button will make diamond drawn above the
 	the circle and release it will do the opposite.
 2. drag with left button will make circle move with the
	the pointer, and with right button will move the dia-
	mond.
 3. use arrow key to move the circle, shift+arrow key to 

	move the diamond and alt+arrow key to move the triangle.
	use 'm' to enlarge the unit move length and use 'l' to
	reduce it. 
 4. triangle will blink between green and black. use 'a' to 
	speed up and 'd' to slow down.
 5. hit 'c' will see something strange.....
 6. hit 'q' to quit, obviously.

Author: Hang Qian
Contact: ibank.qh@gmail.com
Date: Sep 29 2011

******************************************************/
#include <stdlib.h>	
#include <time.h>
#include <stdio.h>			// C I/O (for sprintf) 
#include <iostream>
#include <math.h>			// standard definitions

//#include <GL/glut.h>			// GLUT
//#include <GL/glu.h>			// GLU
//#include <GL/gl.h>			// OpenGL

/*----------------------------------------------------
 I use a define protection to include the right library
 and make sure it will work on several platform and
 compilers without changing any code.
----------------------------------------------------*/
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

// use macro instead of const variables
#define LEFT_BUTTON 0
#define RIGHT_BUTTON 1
#define LARGE_SEGMENT_NUMBER 100
#define SMALL_SEGMENT_NUMBER 8
#define DIAMOND_ABOVE 0
#define CIRCLE_ABOVE 1

using namespace std;

// global variable declarations

// it's kind of frustrating that OpenGL is not
// OO, and the project is so small that I don't 
// want to use class stuff. So I use global variables
// to comunicate. Take special care not to mess up with them

GLsizei WINDOW_HEIGHT = 400, WINDOW_WIDTH = 400;
int VIEW_SIZE_WIDTH = 8;
int VIEW_SIZE_HEIGHT = 8;
const float RED [3] = { 1.0, 0.0, 0.0 };
const float BLUE [3] = { 0.0, 0.0, 1.0};
const float GREEN [3] = { 0.0, 1.0, 0.0};
const float BLACK [3] = { 0.0, 0.0, 0.0};

float CIRCLE_POSITION [2] = {0.0, 0.0};
float DIAMOND_POSITION [2] = {0.0, 0.0};
float TRIANGLE_POSITION [2] = {0.0, 0.0};

float CIRCLE_RADIUS = 1.5;
float DIAMOND_WIDTH = 3.0;
float DIAMOND_HEIGHT = 4.0;
float TRIANGLE_SIDE_LENGTH = 1.6;
float UNIT_LENGTH = 0.1;
int TIMEOUT = 1000;
int TIME_TOGGLE = 0;
int KEYBOARD_TOGGLE = 100;
//int CUR_BUTTON = LEFT_BUTTON;
bool LEFT_BUTTON_DOWN = false;
bool RIGHT_BUTTON_DOWN = false;
int SEQ = CIRCLE_ABOVE;

void draw_diamond ( float x, float y, float w, float h,const float color[3] ) {
	// It draws a diamond: 
	// (x,y): the center coordinate, 
	// w: width h: height
	// color: color vector
 	glPushMatrix();
 	glColor3fv(color);
	glBegin(GL_POLYGON);
		glVertex2f(x, y+h/2);
		glVertex2f(x+(w/2), y);
		glVertex2f(x, y-(h/2));
		glVertex2f(x-(w/2), y);
	glEnd();
	glFlush();
	glPopMatrix();
	
}
void draw_triangle (float x, float y, float l, int toggle ) {
	// (x,y): center coordinates
	// l: side length
	// toggle: how quick it blink betweent 2 colors( green & black by default)
	
	glPushMatrix();
	if ( toggle == 0)
 		glColor3fv(GREEN);
	else
		glColor3fv(BLACK);
	glBegin(GL_POLYGON);
	glVertex2f(x, y+l*sqrt((float)3)/3);
	glVertex2f(x-l/2, y-l*sqrt((float)3)/6);
	glVertex2f(x+l/2,y-l*sqrt((float)3)/6); 
	glEnd();
	glFlush();
	glPopMatrix();
}
void draw_circle ( float cx, float cy, float r, int num_segments,const float color[3] ) {
	glPushMatrix(); 
	glColor3fv(color);
	glBegin(GL_TRIANGLE_FAN); 
	for(int i = 0; i < num_segments; i++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 
	glFlush();
	glPopMatrix();
}

void my_init (void) {
	//glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);		// background color
    
	glShadeModel(GL_SMOOTH);		// smooth shading
    
	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	//------------------------
	//draw_diamond(0.0, 0.0);
	

}

void my_reshape( GLsizei w, GLsizei h ) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	/* set global size for use by drawing routine */

		WINDOW_WIDTH = w;
	   	WINDOW_HEIGHT = h;
	/* adjust clipping box */

		glViewport (0, 0, w,  h);  // update the viewport
		  glMatrixMode(GL_PROJECTION);              // update the projection
		  glLoadIdentity();               

		  gluOrtho2D(-4.0, 4.0, -4.0, 4.0);           // map unit square to viewport
		  glMatrixMode(GL_MODELVIEW);



	
	glutPostRedisplay();
}

void my_display () {
	glClear( GL_COLOR_BUFFER_BIT );
	if( SEQ == CIRCLE_ABOVE){
 		draw_diamond(DIAMOND_POSITION[0],
		     	DIAMOND_POSITION[1], 
		     	DIAMOND_WIDTH, 
		     	DIAMOND_HEIGHT,
		     	RED);
 	
		draw_circle(CIRCLE_POSITION[0], 
		    		CIRCLE_POSITION[1], 
		   			CIRCLE_RADIUS, 
		    		KEYBOARD_TOGGLE, 
		    		BLUE);
	}
	else{
		draw_circle(CIRCLE_POSITION[0], 
			    	CIRCLE_POSITION[1], 
			    	CIRCLE_RADIUS, 
			    	KEYBOARD_TOGGLE, 
			    	BLUE);
		draw_diamond(DIAMOND_POSITION[0],
				     DIAMOND_POSITION[1], 
				     DIAMOND_WIDTH, 
				     DIAMOND_HEIGHT,
				     RED);
		
	}
	draw_triangle(TRIANGLE_POSITION[0], 
		      TRIANGLE_POSITION[1], 
		      TRIANGLE_SIDE_LENGTH, 
		      TIME_TOGGLE);
	glutSwapBuffers();
	//draw_diamond(1.0, 1.0, 3.0, 4.0);
 	
}
 
void my_timer( int id ) {
	if(TIME_TOGGLE == 0){
		//toggle triangle from green to black
		TIME_TOGGLE = 1;
		draw_triangle(TRIANGLE_POSITION[0], 
			      TRIANGLE_POSITION[1], 
			      TRIANGLE_SIDE_LENGTH,
			      TIME_TOGGLE );
		
	}
	else{
		//toggle triangle from black to green
		TIME_TOGGLE = 0;
		draw_triangle(TRIANGLE_POSITION[0], 
			      TRIANGLE_POSITION[1], 
			      TRIANGLE_SIDE_LENGTH,
			      TIME_TOGGLE );	
	}
	
	glutTimerFunc(TIMEOUT, my_timer, 0);
}

void my_mouse( int button, int state, int x, int y ) {
	switch(button){
		case GLUT_LEFT_BUTTON:
		  //CUR_BUTTON = LEFT_BUTTON;
			if( state == GLUT_DOWN){
				SEQ = DIAMOND_ABOVE;
 				LEFT_BUTTON_DOWN = true;
						
			}
			else if (state == GLUT_UP){
				SEQ = CIRCLE_ABOVE;
				LEFT_BUTTON_DOWN = false;
			}
			break;
		case GLUT_RIGHT_BUTTON:
		  if( state == GLUT_DOWN){
				RIGHT_BUTTON_DOWN = true;
			}
		  else{
			RIGHT_BUTTON_DOWN = false;
			}	
		break;
	}
	glutPostRedisplay();
	
}

void my_keyboard( unsigned char c, int x, int y ) {
//	glClear( GL_COLOR_BUFFER_BIT );
	
	switch ( c ) {
      	case 'q':
		  exit(0);			// exit
	// other keyboard events may follow
		case 'c':
		// toggle circle between 20 segments and 100 segments
			if( KEYBOARD_TOGGLE == LARGE_SEGMENT_NUMBER) {
 				KEYBOARD_TOGGLE = SMALL_SEGMENT_NUMBER;			
			}
			else if( KEYBOARD_TOGGLE == SMALL_SEGMENT_NUMBER ) {
 				KEYBOARD_TOGGLE = LARGE_SEGMENT_NUMBER;
			}
			break;
		case 'a':
		 	TIMEOUT += 1000;
			break;
		case 'd':
			if(TIMEOUT >= 1000)
				TIMEOUT -= 1000;
			break;
		case 'm':
			UNIT_LENGTH += 0.1;
			break;
		case 'l':
			if(UNIT_LENGTH >= 0.1)
				UNIT_LENGTH -= 0.1;
	}
	glutPostRedisplay();
}

void my_special_key(int key, int x, int y){
//	glClear( GL_COLOR_BUFFER_BIT );
	
	if( glutGetModifiers() & GLUT_ACTIVE_SHIFT ) {
		switch ( key ) {
			case GLUT_KEY_LEFT:
 				DIAMOND_POSITION[0] -= UNIT_LENGTH;
				break;
			case GLUT_KEY_RIGHT:
 				DIAMOND_POSITION[0] += UNIT_LENGTH;
				break;
			case GLUT_KEY_UP:
 				DIAMOND_POSITION[1] += UNIT_LENGTH;
				break;	
			case GLUT_KEY_DOWN:
 				DIAMOND_POSITION[1] -= UNIT_LENGTH;
				break;
			}			
	}
	else if( glutGetModifiers() & GLUT_ACTIVE_ALT ) {
		switch ( key ) {
			case GLUT_KEY_LEFT:
 				TRIANGLE_POSITION[0] -= UNIT_LENGTH;
				break;
			case GLUT_KEY_RIGHT:
 				TRIANGLE_POSITION[0] += UNIT_LENGTH;
				break;
			case GLUT_KEY_UP:
 				TRIANGLE_POSITION[1] += UNIT_LENGTH;
				break;	
			case GLUT_KEY_DOWN:
 				TRIANGLE_POSITION[1] -= UNIT_LENGTH;
				break;
			}			
	}
	else{
		switch ( key ) {
			case GLUT_KEY_LEFT:
	 			CIRCLE_POSITION[0] -= UNIT_LENGTH;
				break;
			case GLUT_KEY_RIGHT:
	 			CIRCLE_POSITION[0] += UNIT_LENGTH;
				break;
			case GLUT_KEY_UP:
	 			CIRCLE_POSITION[1] += UNIT_LENGTH;
				break;	
			case GLUT_KEY_DOWN:
				CIRCLE_POSITION[1] -= UNIT_LENGTH;
				break;
			}
	}	
	glutPostRedisplay();
		
}

void my_drag( int x, int y ){
	//Step 1: convert Y axis
	y = WINDOW_HEIGHT - y;
	//Step 2: adjust radio: x = x/50, y = y/50
	float new_x = ((float)x)/(WINDOW_WIDTH/VIEW_SIZE_WIDTH);
	float new_y = ((float)y)/(WINDOW_HEIGHT/VIEW_SIZE_HEIGHT);
	//Step 3: shift up and right: x = x - 4, y = y - 4
	new_x = new_x - 4;
	new_y = new_y - 4;
	
	//glClear( GL_COLOR_BUFFER_BIT );
	if( LEFT_BUTTON_DOWN  ) {
 		CIRCLE_POSITION[0] = new_x;
		CIRCLE_POSITION[1] = new_y;
	}
	if( RIGHT_BUTTON_DOWN){
 		DIAMOND_POSITION[0] = new_x;
		DIAMOND_POSITION[1] = new_y;
	}
	glutPostRedisplay();
}


/**********************************************************
main
***********************************************************/
int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
//	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Bank");
   	
	glutDisplayFunc(my_display);
	glutReshapeFunc(my_reshape);
	glutTimerFunc(TIMEOUT, my_timer, 0);
   	glutMouseFunc (my_mouse);
   	glutMotionFunc(my_drag);
	
	glutKeyboardFunc(my_keyboard);
	glutSpecialFunc(my_special_key);

	my_init ();
   	glutMainLoop();
	return 0;
}
