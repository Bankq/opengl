/*************************************************
* Author: Hang Qian
* Email: hq577780@sju.edu
* 
* This is the homework 3 of CSC630-Interactive 
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

#include "ship.h"

Ship::Ship(){
	this->px = 0.0;
	this->py = 0.0;
	this->pz = 0.0;

	this->dx = 0.0;
	this->dy = 0.0;
	this->dz = 0.0;

	this->v = 0.0;

	this->angle = 0.0;
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

	this->angle = 0.0;
}

void Ship::move(){
	// translation move
	this->px += this->v * this->dx;
	this->py += this->v * this->dy;
	this->pz += this->v * this->dz;
	// rotate move
	angle += vr;
	if( angle > 360){
		angle -= 360;
	}
}

void Ship::display(){
	printf("------ SHIP -------\n");
	printf("Position:(%.2f, %.2f, %.2f)\n",this->px, this->py, this->pz);
	printf("Direction:(%.2f, %.2f, %.2f)\n", this->dx, this->dy, this->dz);
	printf("Velocity:%.2f, Rotate Velocity:%.2f\n",this->v, this->vr);
	printf("-------------------\n");
}
