/*
 * boss.cpp
 *
 * @author Ryan Morehouse
 * @date May 27, 2018
 * @version 1.0
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for the boss in Alien Blaster
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o boss.o boss.cpp -lalleg -Wall
 */
 
#include <allegro.h>
#include <iostream>
#include "boss.h"

// constructor & destructor
boss::boss(string filename, int width, int height,
	int columns)
{
	int i;
	
	// get sprite images
	BITMAP *sheet = load_bitmap(filename.c_str(), NULL);
	for(i=0; i<2; i++)
	{
		images[i] = grabframe(sheet, width, height, 0, 0, 2, i);
	}
	destroy_bitmap(sheet);
	
	// position and animation
	curframe = 0;
	maxframe = 2;
	framecount = 0;
	framedelay = 100;
	setVelocityX(0);
	setVelocityY(0);
	
	travelDelay = BOSS_TRAVEL_DELAY;
	moving = false;
	
	// set head and body health
	health = BOSS_HEALTH;
	
	setWidth(width);
	setHeight(height);
}	
	
boss::~boss() {
	int i;
	for(i=0; i<2; i++)
		destroy_bitmap(images[i]);
}

/************************************************
 *
 * Accessors
 *
 ***********************************************/
 
int boss::getSpeed() {
	return getVelocityX();
}

int boss::getCurframe() {
	return curframe;
}

int boss::getMaxframe() {
	return maxframe;
}

int boss::getFrameCount() {
	return framecount;
}

int boss::getFrameDelay() {
	return framedelay;
}

int boss::getHealth() {
	return health;
}

int boss::getDamage() {
	return BOSS_DAMAGE;
}

int boss::getDestX() {
	return destX;
}

int boss::getDestY() {
	return destY;
}

BITMAP *boss::getImageAt(int index) {
	return images[index];
}

bool boss::isMoving() {
	return moving;
}

/*****************************************
 *
 * SETTERS
 *
 ********************************************/

void boss::setSpeed(int newSpeed) {
	setVelocityX(newSpeed);
}

void boss::restoreHealth() {
	health = BOSS_HEALTH;
}

// places & activates the centipede sprite
void boss::put(int newX, int newY) {
	//place
	setX(newX);
	setY(newY);
	
	// set health & activate
	restoreHealth();
	makeAlive();
}

// set the current destination point for the boss
void boss::setDest(int newX, int newY) {
	destX = newX;
	destY = newY;
}

// getting attacked
void boss::takeDamage(int dmg) {
	health -= dmg;
	
	if(health < 1)
		makeDead();
}

// movement
void boss::move() {
	
	// update position based on new speeds
	if(travelDelay == 0)
	{	
		
		// store some data
		int oldX = getX();
		int oldY = getY();
		
		// set speeds towards destination point
		if(destX > getX())
			setVelocityX(1);
		else
			setVelocityX(-1);
		
		if(destY > getY())
			setVelocityY(1);
		else
			setVelocityY(-1);
		
		// use delays to navigate to points
		setDelayX(abs(getX() - destX) / 70);
		setDelayY(abs(getY() - destY) / 70);
		
		// move sprite
		updatePosition();
		
		// determine if point was passed
		double c1, c2;
		c1 = pow((double)(oldX - destX), 2.0) + pow((double)(oldY - destY), 2.0);
		c2 = pow((double)(oldX - getX()), 2.0) + pow((double)(oldY - getY()), 2.0);
		
		// if destination passed, just stop at destination
		if(c2 >= c1)
		{
			setX(destX);
			setY(destY);
			stop();
			
			// start the travel delay timer
			travelDelay = BOSS_TRAVEL_DELAY;
		}
		
		
	}
	
	else
	{
		travelDelay--;
	}
	
	// update the animation
	if(++framecount > framedelay)
	{
		framecount = 0;
		if(++curframe >= maxframe)
			curframe = 0;
	}
}	
		

void boss::start() {
	setVelocityX(1);
	setVelocityY(1);
}

void boss::stop() {
	setVelocityX(0);
	setVelocityY(0);
	moving = false;
}

// movement with AI
void boss::moveWithAI()
{

	// store some data
	int oldX = getX();
	int oldY = getY();
	
	// set speeds towards destination point
	if(destX > getX())
		setVelocityX(1);
	else
		setVelocityX(-1);
	
	if(destY > getY())
		setVelocityY(1);
	else
		setVelocityY(-1);
	
	// use delays to navigate to points
	setDelayX(abs(getX() - destX) / 70);
	setDelayY(abs(getY() - destY) / 70);
	
	// move sprite
	updatePosition();
	
	// determine if point was passed
	double c1, c2;
	c1 = pow((double)(oldX - destX), 2.0) + pow((double)(oldY - destY), 2.0);
	c2 = pow((double)(oldX - getX()), 2.0) + pow((double)(oldY - getY()), 2.0);
	
	// if destination passed, just stop at destination
	if(c2 >= c1)
	{
		setX(destX);
		setY(destY);
		stop();
		
		travelDelay = BOSS_TRAVEL_DELAY;
		moving = false;
	}
	
	// update the animation
	if(++framecount > framedelay)
	{
		framecount = 0;
		if(++curframe >= maxframe)
			curframe = 0;
	}
}

bool boss::isReadyToUpdateDestination()
{
	if(travelDelay < 1 && moving == false)
	{
		moving = true;
		return true;
	}
	else
	{
		travelDelay--;
		return false;
		
	}
}

// draw the sprite
void boss::draw(BITMAP *buffer)
{
	draw_sprite(buffer, images[curframe], getX(), getY());
}
