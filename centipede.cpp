/*
 * centipede.cpp
 *
 * @author Ryan Morehouse
 * @date May 2, 2018
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for the centipede enemies in Alien Blaster
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o centipede.o centipede.cpp -lalleg -Wall
 */
 
#include <allegro.h>
#include <iostream>
#include "centipede.h"

// constructor & destructor
centipede::centipede(string filename, int width, int height,
	int columns)
{
	int i;
	
	// get sprite images
	BITMAP *sheet = load_bitmap(filename.c_str(), NULL);
	for(i=0; i<4; i++)
	{
		headImages[i] = grabframe(sheet, width, height, 0, 0, 8, i);
		segmentImages[i] = grabframe(sheet, width, height, 0, 0, 8, i+4);
	}
	destroy_bitmap(sheet);
	
	// position and animation
	dir = -1;
	curframe = 0;
	maxframe = 4;
	framecount = 0;
	framedelay = 100;
	setVelocityX(DEFAULT_CENTIPEDE_SPEED);
	
	// set head and body health
	headHealth = 0;
	for(i=0; i<CENTIPEDE_LENGTH; i++)
		segHealth[i] = 0;
	
	setWidth(width);
	setHeight(height);
	setDelayX(CENTIPEDE_X_DELAY);
	
	// initialize each body segment
	for(i=0; i<7; i++)
	{
		segments[i] = new sprite();
		segments[i]->setVelocityX(DEFAULT_CENTIPEDE_SPEED);
		segments[i]->setDelayX(CENTIPEDE_X_DELAY);
		segments[i]->setWidth(segmentImages[0]->w);
		segments[i]->setHeight(segmentImages[0]->h);
	}
}	
	
centipede::~centipede() {
	int i;
	for(i=0; i<CENTIPEDE_LENGTH; i++)
		delete segments[i];
	
	for(i=0; i<4; i++)
	{
		if(headImages[i]) destroy_bitmap(headImages[i]);
		if(segmentImages[i]) destroy_bitmap(segmentImages[i]);
	}
}

/************************************************
 *
 * Accessors
 *
 ***********************************************/
 
int centipede::getDir() {
	return dir;
}

int centipede::getSpeed() {
	return getVelocityX();
}

int centipede::getCurframe() {
	return curframe;
}

int centipede::getMaxframe() {
	return maxframe;
}

int centipede::getFrameCount() {
	return framecount;
}

int centipede::getFrameDelay() {
	return framedelay;
}

int centipede::getHeadHealth() {
	return headHealth;
}

int centipede::getSegHealth(int segment) {
	return segHealth[segment];
}

int centipede::isSegmentAlive(int segment) {
	if(segment == 0)
		return isAlive();
	
	else
		return segments[segment-1]->isAlive();
}

BITMAP *centipede::getHeadImageAt(int index) {
	return headImages[index];
}

BITMAP *centipede::getSegmentImageAt(int index) {
	return segmentImages[index];
}

int centipede::getSegX(int seg) {
	return segments[seg]->getX();
}

sprite* centipede::getSeg(int index) {
	return segments[index];
}

int centipede::getLength() {
	return CENTIPEDE_LENGTH;
}

int centipede::getDamage() {
	return CENTIPEDE_DAMAGE;
}

/*****************************************
 *
 * SETTERS
 *
 ********************************************/

void centipede::setDirection(int newDirection) {
	dir = newDirection;
	
	
	if(newDirection > 0)
		setSpeed(DEFAULT_CENTIPEDE_SPEED * -1);
	
	else
		setSpeed(DEFAULT_CENTIPEDE_SPEED);
}

void centipede::setSpeed(int newSpeed) {
	int i;
	
	setVelocityX(newSpeed);
	for(i=0; i<CENTIPEDE_LENGTH; i++)
		segments[i]->setVelocityX(newSpeed);
}

void centipede::restoreHealth() {
	headHealth = CENTIPEDE_HEAD_HEALTH;
	
	int i;
	for(i=0; i<CENTIPEDE_LENGTH; i++)
	{
		segHealth[i] = CENTIPEDE_SEG_HEALTH;
	}
}

void centipede::makeSegDead(int index) {
	segments[index]->makeDead();
}

// places & activates the centipede sprite
void centipede::put(int newX, int newY) {
	int i;
	
	// set health
	restoreHealth();
	
	//place & activate head
	setX(newX);
	setY(newY);
	makeAlive();
	
	//place & activate body
	if(dir > 0)
	{
		for(i=0; i<CENTIPEDE_LENGTH; i++)
		{
			int offset = getWidth()*(i+1);
			segments[i]->setX(newX - offset);
			segments[i]->setY(newY);
			segments[i]->makeAlive();
		}
	}
	
	else // left <- right
	{
		for(i=0; i<CENTIPEDE_LENGTH; i++)
		{
			int offset = getWidth()*(i+1);
			segments[i]->setX(newX + offset);
			segments[i]->setY(newY);
			segments[i]->makeAlive();
		}
	}
}

// getting attacked
void centipede::takeHeadDamage(int dmg) {
	headHealth -= dmg;
	
	if(headHealth < 1)
		makeDead();
}

void centipede::takeSegDamage(int seg, int dmg) {
	segHealth[seg] -= dmg;
	
	if(segHealth[seg] < 1)
		makeSegDead(seg);
}
		

// movement
void centipede::move() {
	
	int i;
	
	// update head position based on new speeds
	updatePosition();
	
	// update segment positions
	for(i=0; i<CENTIPEDE_LENGTH; i++)
		segments[i]->updatePosition();
	
	// head warp behaviour
	if(dir > 0) // left -> right
	{
		if(getX() > SCREEN_W)
			setX(0);
	}
	
	else // left <- right
	{
		if(getX() < 0)
			setX(SCREEN_W);
	}
	
	// segments warp behaviour
	for(i=0; i< CENTIPEDE_LENGTH; i++)
	{
		if(segments[i]->isAlive())
		{
			if(dir > 0) // left -> right
			{
				if(segments[i]->getX() > SCREEN_W)
					segments[i]->setX(0);
			}
			
			else
			{
				if(segments[i]->getX() < 0)
					segments[i]->setX(SCREEN_W);
			}
		}
	}
	
	// update the animation
	if(++framecount > framedelay)
	{
		framecount = 0;
		if(++curframe >= maxframe)
			curframe = 0;
	}
}	

void centipede::stop() {
	setVelocityX(0);
	
	int i;
	for(i=0; i< CENTIPEDE_LENGTH; i++)
		segments[i]->setVelocityX(0);
}


// draw the sprite
void centipede::draw(BITMAP *buffer)
{
	int i;
	
	// draw head
	if(dir > 0)
		draw_sprite_h_flip(buffer, headImages[curframe], getX(), getY());
	else
		draw_sprite(buffer, headImages[curframe], getX(), getY());
	
	// segments may be out of bounds when the centipede
	// is first added to map, just don't draw them
	for(i=0; i<CENTIPEDE_LENGTH; i++)
	{
		if(segments[i]->isAlive())
		{
			if(!(segments[i]->getX() < 0 || segments[i]->getX() > SCREEN_W))
			{
				if(dir > 0)
				{
					draw_sprite_h_flip(buffer, segmentImages[curframe], 
						segments[i]->getX(), segments[i]->getY());
				}
				else
				{
					draw_sprite(buffer, segmentImages[curframe], 
						segments[i]->getX(), segments[i]->getY());
				}
			}
		}
	}
}
