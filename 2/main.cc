#include "stdlib.h"

#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif


#include "header.h"
#include "thing.h"
#include "bomb.h"



#define RUNNING 0
#define PAUSE 1
#define END 2

#define INTERVAL 100

#define NUM_LEVEL 5
#define NUM_LEVEL_THING 4

using namespace std;



int UNIT_WIDTH = 400;
int UNIT_HEIGHT = 400;

int score = 100;
int game_state = 0;
int total_time = 1000;

struct ColorVec{
  float color[3];
};

struct ColorVec thing_color[5];


const int score_table[6] = { -4000, -2000, -1000, 1000, 2000, -100};



vector< vector<Thing*> > things;
vector<Bomb*> bombs;



void init();
void display();
void reshape(int,int);
void keyboard(unsigned char,int,int);
void mouse(int,int,int,int);
void timer(int);
void init_things();
void debug();
void init_color_table();
void draw_thing(Thing*);
void draw_bomb(Bomb*);
void move();
void border_check(Thing*);

int main( int argc, char** argv) {


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(UNIT_WIDTH, UNIT_HEIGHT);
  glutCreateWindow("Game");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutTimerFunc(INTERVAL, timer, PAUSE);
  init();
  glutMainLoop();
  return 0;
}

void init(){
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);

  glClearColor(1,1,1,1);
  glShadeModel(GL_SMOOTH);
    
  glViewport(0,0,UNIT_WIDTH,UNIT_HEIGHT);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();

  //Initialize the thing list
  init_things();
  // Initialize the color table
  init_color_table();
  //debug();





}

void init_color_table(){
  // red
  thing_color[0].color[0] = 1.0;
  thing_color[0].color[1] = 0.0;
  thing_color[0].color[2] = 0.0;
  // tomato
  thing_color[1].color[0] = 1.0;
  thing_color[1].color[1] = 99.0/255.0;
  thing_color[1].color[2] = 7.0/255.0;
  // orange
  thing_color[2].color[0] = 1.0;
  thing_color[2].color[1] = 165.0/255.0;
  thing_color[2].color[2] = 0.0;
  // dark green
  thing_color[3].color[0] = 0.0;
  thing_color[3].color[1] = 100.0/255.0;
  thing_color[3].color[2] = 0.0;
  //green
  thing_color[4].color[0] = 0.0;
  thing_color[4].color[1] = 1.0;
  thing_color[4].color[2] = 0.0;
}

void init_things(){
  for( int i = 0 ; i < NUM_LEVEL ; i++){
    vector<Thing*> level_things;
    for( int j = 0 ; j < NUM_LEVEL_THING ; j++){
      Thing* thing = new Thing(i,UNIT_WIDTH,UNIT_HEIGHT);
      level_things.push_back(thing);
    }
    things.push_back(level_things);
  }
}



void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  //cout << "IN DISPLAY" << endl;
  //draw things
  vector< vector<Thing*> >::reverse_iterator ri;
  vector<Thing*>::iterator j;
  vector<Bomb*>::iterator b;
  for(ri = things.rbegin(); ri != things.rend(); ++ri){
    for( j = (*ri).begin(); j != (*ri).end(); ++j){
      draw_thing(*j);
      for( b = bombs.begin(); b != bombs.end(); ++b){
        if( (*b)->get_level() == (*j)->get_level() ){
          //if there are bombs on the same level
          draw_bomb(*b);
        }
      }   
    } 

   
  }
  
  glutSwapBuffers();
  
}

void draw_thing(Thing* thing){
  //cout << "IN DRAW_THING"<< endl;
  glPushMatrix();
  float color[] = { thing_color[thing->get_level()].color[0],
                    thing_color[thing->get_level()].color[1],
                    thing_color[thing->get_level()].color[2]
                  };
  //cout << color[0] << ',' << color[1] << ',' << color[2] << endl;
  glColor3fv(color);
  double w_size = 0.05 * UNIT_WIDTH;
  double h_size = 0.05 * UNIT_HEIGHT;

  glBegin(GL_POLYGON);
    glVertex2f(thing->get_x() - w_size, thing->get_y() + h_size);
    glVertex2f(thing->get_x() + w_size, thing->get_y() + h_size);
    glVertex2f(thing->get_x() + w_size, thing->get_y() - h_size);
    glVertex2f(thing->get_x() - w_size, thing->get_y() - h_size);
  glEnd();

  glPopMatrix();
}

void draw_bomb(Bomb* bomb){
  glPopMatrix();
  glColor4f(0.0,0.0,0.0,1-bomb->get_level()*0.2);

  double w_size = 0.02 * UNIT_WIDTH;
  double h_size = 0.02 * UNIT_HEIGHT;

  glBegin(GL_POLYGON);
    glVertex2f(bomb->get_x() - w_size, bomb->get_y() + h_size);
    glVertex2f(bomb->get_x() + w_size, bomb->get_y() + h_size);
    glVertex2f(bomb->get_x() + w_size, bomb->get_y() - h_size);
    glVertex2f(bomb->get_x() - w_size, bomb->get_y() - h_size);
  glEnd();

  glPopMatrix();
}

void debug(){
  vector< vector<Thing*> >::iterator i;
  vector<Thing*>::iterator j;
  for(i = things.begin(); i != things.end(); ++i){
    for( j = (*i).begin(); j != (*i).end(); ++j){
      (*j)->display();
    }    
  }
}


void reshape(int w,int h){
  UNIT_WIDTH = w;
  UNIT_HEIGHT = h;
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport (0, 0, UNIT_WIDTH, UNIT_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();               
  gluOrtho2D(0,UNIT_WIDTH,0,UNIT_HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y ){
  if( key == 'q')
    exit(-1);
  return;
}

void mouse(int button, int state, int x, int y){
  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    score += score_table[5];// minus 100 for each bomb dropped
    bombs.push_back(new Bomb(x,UNIT_HEIGHT-y));
  }
}

void timer(int id){
  move();
  glutPostRedisplay();
  glutTimerFunc(100,timer,0);
}

void move(){
  total_time --;

  vector< vector<Thing*> >::reverse_iterator ri;
  vector<Thing*>::iterator j;
  for(ri = things.rbegin(); ri != things.rend(); ++ri){
    for( j = (*ri).begin(); j != (*ri).end(); ++j){
      border_check(*j);
      (*j)->move();
      }   
    }   
}

void border_check(Thing* thing){
  if( thing->get_x() + thing->get_vx() > 0.95 * UNIT_WIDTH){
    thing->set_x( 1.9 * UNIT_WIDTH - thing->get_x() );
    thing->set_vx( - thing->get_vx());
  }
  if( thing->get_x() + thing->get_vx() < 0.05 * UNIT_WIDTH){
    thing->set_x( 0.1 * UNIT_WIDTH - thing->get_x() );
    thing->set_vx( - thing->get_vx());
  }
  if( thing->get_y() + thing->get_vy() > 0.95 * UNIT_HEIGHT){
    thing->set_y( 1.9 * UNIT_HEIGHT - thing->get_y() );
    thing->set_vy( - thing->get_vy());
  }
  if( thing->get_y() + thing->get_vy() < 0.05 * UNIT_HEIGHT){
    thing->set_y( 0.1 * UNIT_HEIGHT - thing->get_y() );
    thing->set_vy( - thing->get_vy());
  }
}






















  
