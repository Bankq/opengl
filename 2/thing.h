#ifndef THING_H
#define THING_H

#define ALIVE 0
#define DEAD 1
#define DYING 2

#endif

#include <iostream>
#include <math.h>
#include <time.h>




class Thing{
 private:
  double px;
  double py;
  double vx;
  double vy;
  int state;
  int level;
  double my_rand(double,double);

 public:
  Thing(int);
  ~Thing(){};
  void display();
  void move();
  double get_x();
  double get_y();
  void set_x(double);
  void set_y(double);
  double get_vx();
  double get_vy();
  void set_vx(double);
  void set_vy(double);
  int get_level();
  void set_state(int);
  int get_state();
};
  
