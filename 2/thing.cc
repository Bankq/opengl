#include "thing.h"


Thing::Thing(int level,int w_unit, int h_unit){
  this->px = my_rand(0.05 * w_unit, 0.95 * w_unit);
  this->py = my_rand(0.05 * h_unit, 0.95 * h_unit);
  this->vx = my_rand(-0.025 * w_unit, 0.025 * w_unit);
  this->vy = my_rand(-0.025 * h_unit, 0.025 * h_unit);
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
  this->px += this->vx;
  this->py += this->vy;
}

void Thing::set_state(int des_state){
  this->state = des_state;
}

int Thing::get_state(){
  return this->state;
}
