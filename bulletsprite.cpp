/*
 * bulletsprite.cpp
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
 
#include <allegro.h>
#include "bulletsprite.h"

using namespace std;


// constructor & destructor
bulletsprite::bulletsprite()
{
	// position and animation
	dir = 0;
	speed = 6;
	currentWeapon = 0;
	
	makeDead();
	setDelayX(5);
	setDelayY(5);
}	
	
bulletsprite::~bulletsprite()
{
	//
}

// Accessors
int bulletsprite::getDir() {
	return dir;
}

int bulletsprite::getSpeed() {
	return speed;
}

int bulletsprite::getWeapon() {
	return currentWeapon;
}

void bulletsprite::setDirection(int direction) {
	dir = direction;
}

void bulletsprite::setWeapon(int weapon) {
	currentWeapon = weapon;
}

void bulletsprite::launch(int weapon, int direction, int newX, int newY) {
	dir = direction;
	currentWeapon = weapon;
	makeAlive();
	setX(newX);
	setY(newY);
	
	// set speeds based on direction
	switch(dir) {
	case 0:
		// North
		setVelocityX(0);
		setVelocityY(-speed);
		break;
		
	case 1:
		// NE
		setVelocityX(speed);
		setVelocityY(-speed);
		break;
		
	case 2:
		// East
		setVelocityX(speed);
		setVelocityY(0);
		break;
		
	case 3:
		// SE
		setVelocityX(speed);
		setVelocityY(speed);
		break;
		
	case 4:
		// South
		setVelocityX(0);
		setVelocityY(speed);
		break;
		
	case 5:
		// SW
		setVelocityX(-speed);
		setVelocityY(speed);
		break;
		
	case 6:
		// West
		setVelocityX(-speed);
		setVelocityY(0);
		break;
		
	case 7:
		// NW
		setVelocityX(-speed);
		setVelocityY(-speed);
		break;
	}
}	
