/*
 * sprite.h
 *
 * @author Ryan Morehouse
 * @date May 1, 2018
 *
 * @purpose A header file for the Sprite class. Inspiration for this
 * class was taken from sprite.cpp from Game Programming All-in-One by
 * Jonathan S. Harbour.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o sprite.o sprite.cpp sprite.h -lalleg -Wall
 */
 
#ifndef SPRITE_H
#define SPRITE_H

#include <allegro.h>

class sprite {
private:
	int alive;
	int x,y;
	int width, height;
	int xVelocity, yVelocity;
	int xdelay, ydelay;
	int xcount, ycount;
	
public:
	sprite();
	~sprite();
	
	// accessors
	int isAlive();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getVelocityX();
	int getVelocityY();
	int getDelayX();
	int getDelayY();
	int getCountX();
	int getCountY();
	
	
	// setters
	void makeAlive();
	void makeDead();
	void setX(int newX);
	void setY(int newY);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setVelocityX(int newVelocity);
	void setVelocityY(int newVelocity);
	void setDelayX(int newDelay);
	void setDelayY(int newDelay);
	void setCountX(int newCount);
	void setCountY(int newCount);
	
	// behaviour
	void updatePosition();
	int inside(int x, int y, int left, int top, int right, int bottom);
	int collided(sprite *other, int shrink);
};

#endif
	
