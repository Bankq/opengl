#ifndef BOMB_H
#define BOMB_H

#define ALIVE 0
#define DEAD 1
#define DYING 2
#endif


#include <iostream>

class Bomb{
 private:
  double px;
  double py;
  int level;
  int state;
  
 public:
  Bomb(double,double);
  ~Bomb(){};
  void display();
  void move();
  double get_x();
  double get_y();
  int get_level();
  void add_level();
  void set_state(int);
  int get_state();
};
