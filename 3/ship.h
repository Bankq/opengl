#include <iostream>

class Ship{
	public:
		// position: 0-1
		float px;
		float py;
		float pz;
		// direction vector:
		// [-1 ~ 1]
		float dx;
		float dy;
		float dz;
		// velocity

		float v;

		float vr;
		float angel; // self rotate

		Ship();
		Ship(float,float,float,float,float,float,float,float);
		void move();// move ship one step
		void display(); // output all the information to standard output


};