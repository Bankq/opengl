/*************************************************
* Author: Hang Qian
* Email: hq577780@sju.edu
* 
* This is the homework 2 of CSC630-Interactive 
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
  int    level;
  int    state;
  
 public:
  Bomb(double,double);
  ~Bomb(){};
  void   display();
  void   move();
  double get_x();
  double get_y();
  int    get_level();
  void   add_level();
  void   set_state(int);
  int    get_state();
};
