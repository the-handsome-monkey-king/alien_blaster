/*
 * sprite.cpp
 * 
 * @author Ryan Morehouse
 * @date May 1, 2018
 *
 * @purpose A class to contain all the data and baisc behaviours of Sprites
 * in Alien Blaster. The concept for this class is largely taken from
 * the Sprite class from Game Programming All-in-One by Jonathan S. Harbour.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o sprite.o sprite.cpp sprite.h -lalleg -Wall
 */

#include <allegro.h>
#include <math.h>
#include "sprite.h"

sprite::sprite() {
	alive = 0;
	x = 0;
	y = 0;
	xVelocity = 0;
	yVelocity = 0;
	xdelay = 0;
	ydelay = 0;
	xcount = 0;
	ycount = 0;
}

sprite::~sprite() {
}

/**********************************************************
 *
 * Accessor Functions
 *
 ********************************************************/
 
// returns 1 if alive, 0 if not
int sprite::isAlive() {
	return alive;
}

int sprite::getX() {
	return x;
}

int sprite::getY() {
	return y;
}

int sprite::getWidth() {
	return width;
}

int sprite::getHeight() {
	return height;
}

int sprite::getVelocityX() {
	return xVelocity;
}

int sprite::getVelocityY() {
	return yVelocity;
}

int sprite::getDelayX() {
	return xdelay;
}

int sprite::getDelayY() {
	return ydelay;
}

int sprite::getCountX() {
	return xcount;
}

int sprite::getCountY() {
	return ycount;
}


/*******************************************************
 *
 * Setter Functions
 *
 ******************************************************/
 
void sprite::makeAlive() {
	alive = 1;
}

void sprite::makeDead() {
	alive = 0;
}

void sprite::setX(int newX) {
	x = newX;
}

void sprite::setY(int newY) {
	y = newY;
}

void sprite::setWidth(int newWidth) {
	width = newWidth;
}

void sprite::setHeight(int newHeight) {
	height = newHeight;
}

void sprite::setVelocityX(int newVelocity) {
	xVelocity = newVelocity;
}

void sprite::setVelocityY(int newVelocity) {
	yVelocity = newVelocity;
}

void sprite::setDelayX(int newDelay) {
	xdelay = newDelay;
}

void sprite::setDelayY(int newDelay) {
	ydelay = newDelay;
}

void sprite::setCountX(int newCount) {
	xcount = newCount;
}

void sprite::setCountY(int newCount) {
	ycount = newCount;
}


	
/*********************************************************
 *
 * Behvaiour Functions
 *
 * These following functions encapsulate the basic behvaiours
 * of the sprite class.
 *
 *********************************************************/

void sprite::updatePosition() {
	// update x
	if(++xcount > xdelay) {
		xcount = 0;
		x += xVelocity;
	}
	
	// update y
	if(++ycount > ydelay) {
		ycount = 0;
		y += yVelocity;
	}
}

// determine if a given point (x,y) falls within this sprite's boundaries
int sprite::inside(int x, int y, int left, int top, int right, int bottom) {
	if(x > left && x < right && y > top && y < bottom)
		return 1;
	else
		return 0;
}

// check for collission with another sprite
int sprite::collided(sprite *other, int shrink) {
	// get dimensions
	int thisWidth = (int)x + width;
	int thisHeight = (int)y + height;
	int otherWidth = (int)other->x + other->width;
	int otherHeight = (int)other->y + other->height;
	
	if(	
		inside((int)x, (int)y, (int)other->x+shrink, 
			(int)other->y+shrink, otherWidth-shrink, otherHeight-shrink) ||
		inside((int)x, thisHeight,  (int)other->x+shrink,
			(int)other->y+shrink, otherWidth-shrink, otherHeight-shrink) ||
		inside(thisWidth, (int)y,  (int)other->x+shrink,
			(int)other->y+shrink, otherWidth-shrink, otherHeight-shrink) ||
		inside(thisWidth, thisHeight,  (int)other->x+shrink,
			(int)other->y+shrink, otherWidth-shrink, otherHeight-shrink))
		return 1;

	else
		return 0;
}
