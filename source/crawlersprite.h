/*
 * crawlersprite.h
 *
 * @author Ryan Morehouse
 * @date May 2, 2018
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for the crawler enemies in Alien Blaster
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o crawlersprite.o crawlersprite.cpp -lalleg -Wall
 */
 
#ifndef CRAWLERSPRITE_H
#define CRAWLERSPRITE_H
 
#include <allegro.h>
#include <fstream>
#include "sprite.h"
#include "grabframe.h"

using namespace std;

#define CRAWLER_DAMAGE 5

class crawlersprite: public sprite {
	
	// positioning and animation
	int dir;
	int speed;
	int animdir;
	int curframe;
	int framecount, framedelay;
	
	// animation frames
	BITMAP *images[8];
public:
	// constructor & destructor
	crawlersprite(string filename, int width, int height,
		int columns);
	~crawlersprite();
	
	// Accessors
	int getDir();
	int getSpeed();
	int getAnimdir();
	int getCurframe();
	int getFrameCount();
	int getFrameDelay();
	BITMAP *getImageAt(int index);
	int getDamage();
	
	// movement
	void move();
	void testmove();		// just bounces around for testing purposes
	void stop();
	void updateSpeed();
	void control(int direction);
	void put(int newX, int newY);
	void bounce();
	
	// automatic animation
	void updateAnimation();
	
	// draw the sprite
	void draw(BITMAP *buffer);
};

#endif
