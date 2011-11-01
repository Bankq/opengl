#include "bomb.h"
Bomb::Bomb(int x,int y){
  this->px = x;
  this->py = y;
  this->level = 0;
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

int Bomb::get_x(){
  return this->px;
}

int Bomb::get_y(){
  return this->py;
}

int Bomb::get_level(){
  return this->level;
}

void Bomb::add_level(){
  this->level++;
  return;
}