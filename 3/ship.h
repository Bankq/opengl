#include <iostream>

class Ship{
	public:
		// position: 0-1
		float px;
		float py;
		float pz;
		// velocity: 0-1, depend on MAX_VELOCITY
		float vx;
		float vy;
		float vz;

		Ship();
		Ship(float,float,float,float,float,float);
		void move();// move ship one step
		void display(); // output all the information to standard output


};