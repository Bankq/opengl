#include "stdlib.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

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
#define STEP 3

#define INTERVAL 80

#define NUM_LEVEL 5
#define NUM_LEVEL_THING 4



using namespace std;



int UNIT_WIDTH = 400;
int UNIT_HEIGHT = 400;

int score = 100;
int game_state = 0;
int total_time = 1000;

float current_mouse_x = 0.0;
float current_mouse_y = 0.0;
struct ColorVec{
  float color[3];
};

struct ColorVec thing_color[5];
char time_str[] = "TIME: ";
char score_str[] = "SCORE: ";
char pause_str[] = "PAUSE";
char timeup_str[] = "TIME UP!";
char win_str[] = "YOU WIN!";

const int score_table[6] = { -4000, -2000, -1000, 1000, 2000, -100};
const float shrink_rate[5] = { 1, 0.9, 0.8, 0.7, 0.6};


vector< vector<Thing*> > things;
vector<Bomb*> bombs;



void init(); // initialize the settings
void display(); // display routine
void reshape(int,int); // reshape routine
void keyboard(unsigned char,int,int); // keyboard routine
void mouse(int,int,int,int); //mouse routine
void aim(int,int);// passive mouse callback
void draw_aim(int,int,int);// draw a helping aim
void timer(int); // timer routine
void init_things(); // intialize the thing list
void debug();// console output
void init_color_table(); // intialize the color table
void draw_border(); // draw the wall
void draw_thing(Thing*); // draw a single thing
void draw_bomb(Bomb*); // draw a single bomb
void move(); // move everything one step
bool hit_check(Bomb*, Thing*); // check if a bomb hit something
void display_info(); // display time and score
void display_timeup();// display time up info
void display_win(); // display winning info
void pause_game(); // pause the game
bool clear(); // check if destroy all bad things
void one_step_move(); // execute a one step move
bool foo(Bomb*);



int main( int argc, char** argv) {


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(UNIT_WIDTH, UNIT_HEIGHT);
  glutCreateWindow("Game");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(aim);
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

/* 
 * Loop the thing list and call each one's
 * constuctor function
*/

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
  // always draw border
  draw_border();
 
  // if game ends;
  if(game_state == END){
    if ( total_time <= 0){
      display_timeup();
    }
    else{
      display_win();
    }
  }

  // draw things
  if( game_state == RUNNING || 
      game_state == PAUSE || 
      game_state == STEP){
    vector< vector<Thing*> >::reverse_iterator ri;
    vector<Thing*>::iterator j;
    vector<Bomb*>::iterator b;
    for(ri = things.rbegin(); ri != things.rend(); ++ri){
      for( j = (*ri).begin(); j != (*ri).end(); ++j){
        if((*j)->get_state() != DEAD)
          draw_thing(*j);
          draw_aim((*j)->get_level(),current_mouse_x,current_mouse_y);
        for( b = bombs.begin(); b != bombs.end(); ++b){
          if( (*b)->get_level() == (*j)->get_level() ){
            //if there are bombs on the same level
            if((*b)->get_state() != DEAD && (*b)->get_level() != -1 )
              draw_bomb(*b);
          }
        }   
      } 
    }
  }
 
  display_info();
  glutSwapBuffers();
  
}
void display_win(){
    char* p = win_str;
    glColor3f(1,0,0);
    glRasterPos2f(5,UNIT_HEIGHT-23);
    while( *p != '\0'){
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,*p);
      p += 1; 
    } 
}
void display_timeup(){
    char* p = timeup_str;
    glColor3f(1,0,0);
    glRasterPos2f(5,UNIT_HEIGHT-23);
    while( *p != '\0'){
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,*p);
      p += 1; 
    }
}

void display_info(){
  glPushMatrix();

  // write time and score
  glColor3f(1,1,0);
  glRasterPos2f(5,5);
  char* c = time_str;
  while( *c != '\0'){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,*c);
    c += 1; 
  }
  glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,' ');
  
  char tt[10];
  sprintf( tt,"%d", total_time);
  c = tt;
  while( *c != '\0'){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,*c);
    c += 1; 
  }
  glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,' ');
  

  char* s = score_str;
  while( *s != '\0'){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,*s);
    s += 1; 
  }
  glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,' ');
  
  char sc[10];
  sprintf( sc,"%d", score);
  c = sc;
  while( *c != '\0'){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,*c);
    c += 1; 
  }


  //display pause if needed
  if( game_state == PAUSE ){
    char* p = pause_str;
    glColor3f(1,0,0);
    glRasterPos2f(5,UNIT_HEIGHT-23);
    while( *p != '\0'){
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,*p);
      p += 1; 
    }
  }
  glPopMatrix();
  
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


/*
  This is the most tricky part of the program
  Different level has different view_size
  We need to shrink the view_size of each level
  the shrink ratio is pre defined as shrink_rate[]
*/
void draw_thing(Thing* thing){
  //cout << "IN DRAW_THING"<< endl;
  glPushMatrix();
  float color[] = { thing_color[thing->get_level()].color[0],
                    thing_color[thing->get_level()].color[1],
                    thing_color[thing->get_level()].color[2]
                  };
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
  cout << "---------------------" << endl;
  cout << "Current Window Size:";
  cout << "Width: "<<UNIT_WIDTH << " | Height: "<< UNIT_HEIGHT << endl;
  cout << "-------- THINGS ----------" << endl;

  vector< vector<Thing*> >::iterator i;
  vector<Thing*>::iterator j;
  for(i = things.begin(); i != things.end(); ++i){
    cout << "- - - - - - - - - - - " << endl;
    for( j = (*i).begin(); j != (*i).end(); ++j){
      (*j)->display();
    }    
  }
  cout << "-------- BOMBS ----------" << endl;
  vector<Bomb*>::iterator k;
  for(k = bombs.begin(); k != bombs.end(); ++k){
    (*k)->display();
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
  if( key == 'p' || key == 'P')
    pause_game();
  return;
}

void mouse(int button, int state, int x, int y){
  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 
      (game_state == RUNNING || game_state == STEP) ){
    score += score_table[5];// minus 100 for each bomb dropped
    double x_pos = (double)x/UNIT_WIDTH;
    double y_pos = 1.0 - (double)y/UNIT_HEIGHT;
    bombs.push_back(new Bomb(x_pos,y_pos));
  }
  if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
    pause_game();
  }
  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    one_step_move();
  }
}

void aim(int x, int y){
    y = UNIT_HEIGHT - y; 
    current_mouse_x = x;
    current_mouse_y = y;
 
}

void draw_aim(int level,int x, int y){
  //cout << "IN DRAW AIM, X: "<< x << " Y: " << y << endl;
  int line_width = 3;
  
    glPushMatrix();
    float x_shift = UNIT_WIDTH * (1 - shrink_rate[level]) * 0.5 + x * shrink_rate[level];
    float y_shift = UNIT_HEIGHT * (1 - shrink_rate[level]) * 0.5 + y * shrink_rate[level];
    float w_size = 0.02 * shrink_rate[level] * UNIT_WIDTH;
    float h_size = 0.02 * shrink_rate[level] * UNIT_HEIGHT;
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
     glVertex2f(x_shift - w_size, y_shift + h_size);
     glVertex2f(x_shift + w_size, y_shift + h_size);
     glVertex2f(x_shift + w_size, y_shift - h_size);
     glVertex2f(x_shift - w_size, y_shift - h_size);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
     glVertex2f(x_shift - w_size + line_width, y_shift + h_size - line_width);
     glVertex2f(x_shift + w_size - line_width, y_shift + h_size - line_width);
     glVertex2f(x_shift + w_size - line_width, y_shift - h_size + line_width);
     glVertex2f(x_shift - w_size + line_width, y_shift - h_size + line_width);
    glEnd();
    glPopMatrix();
 
}
void one_step_move(){
  if(game_state == RUNNING){
    game_state = STEP;
  }
  else if( game_state == STEP ){
    move();
    debug();
    glutPostRedisplay();
  }
}
void pause_game(){
  if (game_state == RUNNING){
    game_state = PAUSE;
  }
  else if(game_state == PAUSE || game_state == STEP){
    game_state = RUNNING;
  }
}

void timer(int id){
  if(game_state == RUNNING)
    move();
  if(total_time <= 0 ){
    game_state = END;
  }
  if ( clear()){
    game_state = END;
  }
  glutPostRedisplay();
  glutTimerFunc(INTERVAL,timer,0);
}

bool clear(){
//-------------------------------------------------
// erase the dead bombs.
  vector<Bomb*>::iterator b = bombs.begin();
  while( b != bombs.end()){
    if( (*b)->get_state() == DEAD){
      b = bombs.erase(b);
    }
    else{
      ++b;
    }
  }

//-------------------------------------------------
  vector< vector<Thing*> >::reverse_iterator ri;
  vector<Thing*>::iterator j;
  for(ri = things.rbegin(); ri != things.rend(); ++ri){
    for( j = (*ri).begin(); j != (*ri).end(); ++j){
      if((*j)->get_state() != DEAD && (*j)->get_level() > 2){
        return false;
      }
    }   
  }
  return true;
}

void move(){
  total_time --;
  // loop over the thing list and move each one
  vector< vector<Thing*> >::reverse_iterator ri;
  vector<Thing*>::iterator j;
  for(ri = things.rbegin(); ri != things.rend(); ++ri){
    for( j = (*ri).begin(); j != (*ri).end(); ++j){
      if((*j)->get_state() == DYING){
        // if one got hit, don't move it
        (*j)->set_state(DEAD);
        continue;
      }
      (*j)->move();
    }   
  }
  // loop bomb list and move every one
  vector<Bomb*>::iterator b;
  for( b = bombs.begin(); b != bombs.end(); ++b){
    (*b)->move();
    if((*b)->get_level() == 5){
      // 5 means hits the ground
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
          //if a bomb hits a thing ,set the thing's state
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

bool foo(Bomb* b){
  if( b->get_state() == DEAD ) return true;
  return false;
}





















  
