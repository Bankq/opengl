#include "ship.h"

Ship::Ship(){
	this->px = 0.0;
	this->py = 0.0;
	this->pz = 0.0;

	this->dx = 0.0;
	this->dy = 0.0;
	this->dz = 0.0;

	this->v = 0.0;

	this->angel = 0.0;
	this->vr = 0.0;
}

Ship::Ship(float px, float py, float pz, 
		   float dx, float dy, float dz,
		   float v, float vr){
	this->px = px;
	this->py = py;
	this->pz = pz;

	this->dx = dx;
	this->dy = dy;
	this->dz = dz;

	this->v = v;

	this->vr = vr;

	this->angel = 0.0;
}

void Ship::move(){
	// translation move
	this->px += this->v * this->dx;
	this->py += this->v * this->dy;
	this->pz += this->v * this->dz;
	// rotate move
	angel += vr;
	if( angel > 360){
		angel -= 360;
	}
}

void Ship::display(){
	printf("---------------\n");
	printf("Position:(%.2f, %.2f, %.2f)\n",this->px, this->py, this->pz);
	printf("Direction:(%.2f, %.2f, %.2f)\n", this->dx, this->dy, this->dz);
	printf("Velocity:%.2f, Rotate Velocity:%.2f\n",this->v, this->vr);
	printf("---------------\n");
}
