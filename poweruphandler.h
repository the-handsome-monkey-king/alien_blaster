/*
 * poweruphandler.h
 *
 * @author Ryan Morehouse
 * @date May 8, 2018
 *
 * @purpose A sprite handler to manage all powerups for the game
 *		Alien Blaster.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o poweruphandler.o poweruphandler.cpp -lalleg -Wall
 */
 
#ifndef POWERUPHANDLER_H
#define POWERUPHANDLER_H

#include <allegro.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "sprite.h"
#include "powerup.h"

using namespace std;

// audio settings
#define PANNING 128
#define PITCH 1000
#define VOLUME 128

class poweruphandler {
	// powerup images
	BITMAP *images[3];
	
	// powerup sprites
	vector<powerup*> powerups;
	
	// powerup sound effects
	SAMPLE *powerupSound;
	
	
public:
	// constructor & destructor
	poweruphandler(string healthFile, string flameFile, string bazookaFile,
		string soundFile);
	~poweruphandler();
	
	// Accessors
	int getSize();
	powerup *at(int index);
	BITMAP *getImageAt(int index);
	
	// Adding and using powerups
	void add(int powerupType, int x, int y);
	int getPowerupValue(int index);
	int getPowerupType(int index);
	int usePowerup(int index);
	
	// draw powerups
	void draw(BITMAP *buffer);
	
	// powerup noise
	void playNoise();
};

#endif
