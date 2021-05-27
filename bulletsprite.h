/*
 * bulletsprite.h
 *
 * @author Ryan Morehouse
 * @date May 1, 2018
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for bullets in the Alien Blaster game.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o bulletsprite.o bulletsprite.cpp -lalleg -Wall
 */
 
#ifndef BULLETSPRITE_H
#define BULLETSPRITE_H
 
#include <allegro.h>
#include "sprite.h"

using namespace std;

class bulletsprite: public sprite {
	// positioning and animation
	int dir;
	int speed;
	int currentWeapon;
public:
	// constructor & destructor
	bulletsprite();
	~bulletsprite();
	
	// Accessors
	int getDir();
	int getSpeed();
	int getWeapon();
	
	// Setters
	void setDirection(int direction);
	void setWeapon(int weapon);
	void launch(int weapon, int direction, int newX, int newY);
};

#endif
