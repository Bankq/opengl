#ifndef BOMB_H
#define BOMB_H

#define ALIVE 0
#define DEAD 1
#endif


#include <iostream>

class Bomb{
 private:
  int px;
  int py;
  int level;
  int state;
  
 public:
  Bomb(int,int);
  ~Bomb(){};
  void display();
  void move();
  int get_x();
  int get_y();
  int get_level();
  void add_level();
  void set_state(int);
  int get_state();
};
