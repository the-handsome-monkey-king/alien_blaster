/*
 * powerup.h
 *
 * @author Ryan Morehouse
 * @date May 8, 2018
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for powerups in the Alien Blaster game.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o powerup.o powerup.cpp -lalleg -Wall
 */
 
#ifndef POWERUP_H
#define POWERUP_H
 
#include <allegro.h>
#include "sprite.h"

#define HEALTH_RESTORE 10
#define FLAME_AMMO 5
#define BAZOOKA_AMMO 5

using namespace std;

class powerup: public sprite {
	int type;
	BITMAP *image;
	
public:
	// constructor & destructor
	powerup(BITMAP *icon, int powerupTyp, int x, int y);
	~powerup();
	
	// Accessors
	int getPowerup();
	int getType();
	BITMAP *getImage();
	
	// Setters
	void put(int newX, int newY);
	void setType(int powerupType);
};

#endif
