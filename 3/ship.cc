#include "ship.h"

Ship::Ship(){
	this->px = 0.0;
	this->py = 0.0;
	this->pz = 0.0;
	this->vx = 0.0;
	this->vy = 0.0;
	this->vz = 0.0;
}

Ship::Ship(float px, float py, float pz, 
		   float vx, float vy, float vz){
	this->px = px;
	this->py = py;
	this->pz = pz;

	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
}

void Ship::move(){
	this->px += this->vx;
	this->py += this->vy;
	this->pz += this->vz;
}

void Ship::display(){
	printf("---------------");
	printf("X:%.2f, Y:%.2f, Z:%.2f\n",this->px, this->py, this->pz);
	printf("VX:%.2f, Z:%.2f,Z:%.2f\n", this->vx, this->vy, this->vz);
	printf("---------------");
}
