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
		float angle; // self rotate

		Ship();
		Ship(float,float,float,float,float,float,float,float);
		void move();// move ship one step
		void display(); // output all the information to standard output


};