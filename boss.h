/*
 * boss.h
 *
 * @author Ryan Morehouse
 * @date May 27, 2018
 * @version 1.0
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for the final boss in Alien Blaster.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o boss.o boss.cpp -lalleg -Wall
 */
 
#ifndef BOSS_H
#define BOSS_H

#include <allegro.h>
#include <fstream>
#include <math.h>
#include "sprite.h"
#include "grabframe.h"


using namespace std;

#define BOSS_SPEED 1
#define BOSS_HEALTH 50
#define BOSS_TRAVEL_DELAY 1000
#define BOSS_DAMAGE 10

class boss: public sprite {
	
	// positioning and animation
	int curframe, maxframe;
	int framecount, framedelay;
	int destX, destY;
	
	// destination tracking
	int travelDelay;
	bool moving;
	
	int health;
	
	// animation frames
	BITMAP *images[2];
	
public:
	// constructor & destructor
	boss(string filename, int width, int height,
		int columns);
	~boss();
	
	// Accessors
	int getDir();
	int getSpeed();
	int getCurframe(); // for the head
	int getMaxframe();
	int getFrameCount();
	int getFrameDelay();
	int getHealth();
	int getDamage();
	int getDestX();
	int getDestY();
	bool isMoving();
	BITMAP *getImageAt(int index);
	
	// Setters
	void setSpeed(int newSpeed);
	void restoreHealth();
	void put(int newX, int newY);			// place boss sprite
	void setDest(int newX, int newY);
		
	// Getting attacked
	void takeDamage(int dmg);
	
	// movement
	void move();
	void start();
	void stop();
	
	// movement with AI
	void moveWithAI();
	bool isReadyToUpdateDestination();
	
	// draw the sprite
	void draw(BITMAP *buffer);
};

#endif
