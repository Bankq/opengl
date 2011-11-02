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

#include "bomb.h"
Bomb::Bomb(double x,double y){
  this->px = x;
  this->py = y;
  this->level = -1;
  this->state = ALIVE;
}

void Bomb::display(){
  std::cout << "X: " << this->px << ", ";
  std::cout << "Y: " << this->py;
  std::cout << " | ";
  std::cout << "LEVEL: " << this->level;
  std::cout << " | ";
  std::cout << "STATE: " << this->state;
  std::cout << std::endl;
}

void Bomb::move(){
  this->level++;
}

void Bomb::set_state(int des_state){
  this->state = des_state;
}

int Bomb::get_state(){
  return this->state;
}

double Bomb::get_x(){
  return this->px;
}

double Bomb::get_y(){
  return this->py;
}

int Bomb::get_level(){
  return this->level;
}

void Bomb::add_level(){
  this->level++;
  return;
}