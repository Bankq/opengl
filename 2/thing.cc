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


#include "thing.h"


Thing::Thing(int level){
  this->px = my_rand(0.05, 0.95);
  this->py = my_rand(0.05, 0.95);
  this->vx = my_rand(-0.0025, 0.0025);
  this->vy = my_rand(-0.0025, 0.0025);
  this->level = level;
  this->state = ALIVE;
}

void Thing::display(){
  std::cout << "X: " << this->px << ", ";
  std::cout << "Y: " << this->py;
  std::cout << " | ";
  std::cout << "VX: " << this->vx << ", ";
  std::cout << "VY: " << this->vy;
  std::cout << " | ";
  std::cout << "LEVEL: " << this->level;
  std::cout << " | ";
  std::cout << "STATE: " << this->state;
  std::cout << std::endl;
}

double Thing::my_rand(double dbegin,double dend){
  double D = (double)rand()/((double)RAND_MAX +1.0) ;
  //  std::cout << "D " << D << std::endl;
  return dbegin + ( dend - dbegin) * D;
}

double Thing::get_x(){
  return this->px;
}

double Thing::get_y(){
  return this->py;
}

void Thing::set_x(double new_x){
  this->px = new_x;
  return;
}

void Thing::set_y(double new_y){
  this->py = new_y;
  return;
}

double Thing::get_vx(){
  return this->vx;
}

double Thing::get_vy(){
  return this->vy;
}

void Thing::set_vx(double new_vx){
  this->vx = new_vx;
  return;
}

void Thing::set_vy(double new_vy){
  this->vy = new_vy;
  return;
}

int Thing::get_level(){
  return this->level;
}

void Thing::move(){
  
  if( this->px + this->vx > 0.95 ){
    this->px = 1.9 - this->px;
    this->vx = -this->vx;
  }
  if( this->px + this->vx < 0.05 ){
    this->px = 0.1 - this->px;
    this->vx = -this->vx;
  }
  if( this->py + this->vy > 0.95 ){
    this->py = 1.9 - this->py;
    this->vy = -this->vy;
  }
  if( this->py + this->vy < 0.05 ){
    this->py = 0.1 - this->py;
    this->vy = -this->vy;
  }



  this->px += this->vx;
  this->py += this->vy;
}

void Thing::set_state(int des_state){
  this->state = des_state;
}

int Thing::get_state(){
  return this->state;
}
