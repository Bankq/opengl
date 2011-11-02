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
  int    state;
  int    level;
  double my_rand(double,double);

 public:
  Thing(int);
  ~Thing(){};
  void   display();
  void   move();
  double get_x();
  double get_y();
  void   set_x(double);
  void   set_y(double);
  double get_vx();
  double get_vy();
  void   set_vx(double);
  void   set_vy(double);
  int    get_level();
  void   set_state(int);
  int    get_state();
};
  
