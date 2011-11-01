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
const float shrink_rate[5] = { 1, 0.9, 0.8, 0.7, 0.6};


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
void draw_border();
void draw_thing(Thing*);
void draw_bomb(Bomb*);
void move();
bool hit_check(Bomb*, Thing*);


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
      Thing* thing = new Thing(i);
      level_things.push_back(thing);
    }
    things.push_back(level_things);
  }
}



void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  //cout << "IN DISPLAY" << endl;

  // draw border
  draw_border();

  // draw things
  vector< vector<Thing*> >::reverse_iterator ri;
  vector<Thing*>::iterator j;
  vector<Bomb*>::iterator b;
  for(ri = things.rbegin(); ri != things.rend(); ++ri){
    for( j = (*ri).begin(); j != (*ri).end(); ++j){
      if((*j)->get_state() != DEAD)
        draw_thing(*j);
      for( b = bombs.begin(); b != bombs.end(); ++b){
        if( (*b)->get_level() == (*j)->get_level() ){
          //if there are bombs on the same level
          if((*b)->get_state() != DEAD && (*b)->get_level() != -1 )
            draw_bomb(*b);
        }
      }   
    } 

   
  }
  
  glutSwapBuffers();
  
}

void draw_border(){
  glPushMatrix();
  int line_width = 5;// 5px line width
  for ( int i = 0 ; i < 5 ; i++){
    float new_origin_x = 0.5 * ( 1 - shrink_rate[i]) * UNIT_WIDTH;
    float new_origin_y = 0.5 * ( 1 - shrink_rate[i]) * UNIT_HEIGHT;
    float new_width = UNIT_WIDTH * shrink_rate[i];
    float new_height = UNIT_HEIGHT * shrink_rate[i];
    glBegin(GL_QUADS);
      if(i == 0)
        glColor3f(0.0,0.0,0.0);
      else
        glColor3f(0.75,0.75,0.75);
      glVertex2f(new_origin_x, new_origin_y);
      glVertex2f(new_origin_x + new_width, new_origin_y);
      glVertex2f(new_origin_x + new_width, new_origin_y + new_height);
      glVertex2f(new_origin_x, new_origin_y + new_height);
    glEnd();

    glBegin(GL_QUADS);
      if( i == 4)
        glColor3f(1.0,1.0,1.0);
      else
        glColor3f(0.7,0.7,0.7);
      glVertex2f(new_origin_x + line_width, new_origin_y + line_width);
      glVertex2f(new_origin_x + new_width - line_width, new_origin_y + line_width);
      glVertex2f(new_origin_x + new_width - line_width, new_origin_y + new_height - line_width);
      glVertex2f(new_origin_x + line_width, new_origin_y + new_height - line_width);
    glEnd();
  }
  
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_LINES);
    glVertex2f(0.0,0.0);
    glVertex2f(0.5 * ( 1 - shrink_rate[4]) * UNIT_WIDTH + line_width, 
               0.5 * ( 1 - shrink_rate[4]) * UNIT_HEIGHT + line_width);

    glVertex2f(0.0,UNIT_HEIGHT);
    glVertex2f(0.5 * ( 1 - shrink_rate[4]) * UNIT_WIDTH + line_width, 
               UNIT_HEIGHT - 0.5 * ( 1 - shrink_rate[4]) * UNIT_HEIGHT - line_width);

    glVertex2f(UNIT_WIDTH,UNIT_HEIGHT);
    glVertex2f(UNIT_WIDTH - 0.5 * ( 1 - shrink_rate[4]) * UNIT_WIDTH - line_width, 
               UNIT_HEIGHT - 0.5 * ( 1 - shrink_rate[4]) * UNIT_HEIGHT - line_width);

    glVertex2f(UNIT_WIDTH,0);
    glVertex2f(UNIT_WIDTH - 0.5 * ( 1 - shrink_rate[4]) * UNIT_WIDTH - line_width, 
               0.5 * ( 1 - shrink_rate[4]) * UNIT_HEIGHT + line_width);
  glEnd();
  glPopMatrix();
}

void draw_thing(Thing* thing){
  //cout << "IN DRAW_THING"<< endl;
  glPushMatrix();
  float color[] = { thing_color[thing->get_level()].color[0],
                    thing_color[thing->get_level()].color[1],
                    thing_color[thing->get_level()].color[2]
                  };
  //cout << color[0] << ',' << color[1] << ',' << color[2] << endl;
  if(thing->get_state() == ALIVE)
    glColor3fv(color);
  else
    glColor3f(0.0,0.0,0.0);
  
  int level = thing->get_level();

  double w_size = 0.05 * shrink_rate[level];
  double h_size = 0.05 * shrink_rate[level];

  double x_shift = thing->get_x() * shrink_rate[level] + 0.5 * ( 1 - shrink_rate[level]);
  double y_shift = thing->get_y() * shrink_rate[level] + 0.5 * ( 1 - shrink_rate[level]);


  glBegin(GL_POLYGON);
    glVertex2f((x_shift - w_size) * UNIT_WIDTH, (y_shift + h_size) * UNIT_HEIGHT);
    glVertex2f((x_shift + w_size) * UNIT_WIDTH, (y_shift + h_size) * UNIT_HEIGHT);
    glVertex2f((x_shift + w_size) * UNIT_WIDTH, (y_shift - h_size) * UNIT_HEIGHT);
    glVertex2f((x_shift - w_size) * UNIT_WIDTH, (y_shift - h_size) * UNIT_HEIGHT);
  glEnd();

  glPopMatrix();
}

void draw_bomb(Bomb* bomb){
  glPushMatrix();
  glColor4f(0.0,0.0,1.0,1-bomb->get_level()*0.2);

  int level = bomb->get_level();

  double w_size = 0.02 * shrink_rate[level];
  double h_size = 0.02 * shrink_rate[level];

  double x_shift = bomb->get_x() * shrink_rate[level] + 0.5 * ( 1 - shrink_rate[level]);
  double y_shift = bomb->get_y() * shrink_rate[level] + 0.5 * ( 1 - shrink_rate[level]);


  glBegin(GL_POLYGON);
    glVertex2f((x_shift - w_size) * UNIT_WIDTH, (y_shift + h_size) * UNIT_HEIGHT);
    glVertex2f((x_shift + w_size) * UNIT_WIDTH, (y_shift + h_size) * UNIT_HEIGHT);
    glVertex2f((x_shift + w_size) * UNIT_WIDTH, (y_shift - h_size) * UNIT_HEIGHT);
    glVertex2f((x_shift - w_size) * UNIT_WIDTH, (y_shift - h_size) * UNIT_HEIGHT);
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
  if( key == 'q' || key == 'Q')
    exit(-1);
  return;
}

void mouse(int button, int state, int x, int y){
  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    score += score_table[5];// minus 100 for each bomb dropped
    double x_pos = (double)x/UNIT_WIDTH;
    double y_pos = 1.0 - (double)y/UNIT_HEIGHT;
    bombs.push_back(new Bomb(x_pos,y_pos));
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
      if((*j)->get_state() == DYING){
        (*j)->set_state(DEAD);
        continue;
      }
      (*j)->move();
    }   
  }
  
  vector<Bomb*>::iterator b;
  for( b = bombs.begin(); b != bombs.end(); ++b){
    (*b)->move();
    if((*b)->get_level() == 5){
      (*b)->set_state(DEAD);
      continue;
    }
    else if((*b)->get_state() == ALIVE){
      vector<Thing*> current_level = things.at((*b)->get_level());
      vector<Thing*>::iterator i;
      for( i = current_level.begin(); i != current_level.end(); i++){
        if((*b)->get_state() == ALIVE && 
           (*i)->get_state() == ALIVE &&
           hit_check(*b, *i)){
          //set thing's state
          (*i)->set_state(DYING);
          // update score
          score += score_table[(*b)->get_level()];
        }
      }
    }
  }   
}

bool hit_check(Bomb* b, Thing* t){
  if( fabs( b->get_x() - t->get_x() ) <= 0.05 && 
      fabs( b->get_y() - t->get_y() ) <= 0.05 )
      return true;
  return false;
}
























  
