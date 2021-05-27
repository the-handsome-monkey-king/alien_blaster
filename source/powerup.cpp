/*
 * powerup.cpp
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
 
#include <allegro.h>
#include "powerup.h"

using namespace std;


// constructor & destructor
powerup::powerup(BITMAP *icon, int powerupType, int x, int y)
{
	type = powerupType;
	image = icon;
	setX(x);
	setY(y);
	setWidth(icon->w);
	setHeight(icon->h);
}	
	
powerup::~powerup()
{
	//
}

// Accessors
int powerup::getPowerup() {
	switch(type) {
	case 0:
		// health powerup
		return HEALTH_RESTORE;
		break;
	case 1:
		// flame ammo
		return FLAME_AMMO;
		break;
	case 2:
		// bazooka ammo
		return BAZOOKA_AMMO;
		break;
	}
	
	// if this point reached, something is wrong
	return -1;	
}

int powerup::getType() {
	return type;
}

BITMAP *powerup::getImage() {
	return image;
}

void powerup::setType(int powerupType) {
	type = powerupType;
}
