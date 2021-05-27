/*
 * centipedesprite.h
 *
 * @author Ryan Morehouse
 * @date May 2, 2018
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for the crawler enemies in Alien Blaster.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o centipede.o centipede.cpp -lalleg -Wall
 */
 
#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#define CENTIPEDE_LENGTH 7
#define CENTIPEDE_HEAD_HEALTH 3
#define CENTIPEDE_SEG_HEALTH 3
#define DEFAULT_CENTIPEDE_SPEED -2
#define CENTIPEDE_X_DELAY 5
#define CENTIPEDE_DAMAGE 10
 
#include <allegro.h>
#include <fstream>
#include "sprite.h"
#include "grabframe.h"

using namespace std;

class centipede: public sprite {
	
	// positioning and animation
	int dir;								// 1 or -1
	int curframe, maxframe;
	int framecount, framedelay;
	
	int headHealth;
	int segHealth[CENTIPEDE_LENGTH];
	
	// animation frames
	BITMAP *headImages[4];
	BITMAP *segmentImages[4];
	
	// body segments
	sprite *segments[CENTIPEDE_LENGTH];
public:
	// constructor & destructor
	centipede(string filename, int width, int height,
		int columns);
	~centipede();
	
	// Accessors
	int getDir();
	int getSpeed();
	int getCurframe(); // for the head
	int getMaxframe();
	int getFrameCount();
	int getFrameDelay();
	int getHeadHealth();
	int getSegHealth(int segment);
	int isSegmentAlive(int segment);
	int getSegX(int seg);
	int getLength();
	int getDamage();
	sprite* getSeg(int index);
	BITMAP *getHeadImageAt(int index);
	BITMAP *getSegmentImageAt(int index);
	
	// Setters
	void setDirection(int newDirection);
	void setSpeed(int newSpeed);
	void restoreHealth();
	void makeSegDead(int index);
	void put(int newX, int newY);			// place centipede sprite
		
	// Getting attacked
	void takeHeadDamage(int dmg);
	void takeSegDamage(int seg, int dmg);
	
	// movement
	void move();
	void stop();

	
	
	// draw the sprite
	void draw(BITMAP *buffer);
};

#endif
