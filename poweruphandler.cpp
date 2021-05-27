/*
 * poweruphandler.cpp
 *
 * @author Ryan Morehouse
 * @date May 1, 2018
 *
 * @purpose A sprite handler to manage all powerups for the game
 *		Alien Blaster.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o poweruphandler.o poweruphandler.cpp -lalleg -Wall
 */
 
#include <allegro.h>
#include <string>
#include "poweruphandler.h"


/*****************************************************
 *
 * Constructor & Destructor
 *
 ******************************************************/
 
poweruphandler::poweruphandler(string healthFile, string flameFile, string bazookaFile,
		string soundFile)
{
	
	
	int i;
	
	// get images
	// health
	images[0] = load_bitmap(healthFile.c_str(), NULL);
	// flame ammo
	images[1] = load_bitmap(flameFile.c_str(), NULL);
	// bazooka ammo
	images[2] = load_bitmap(bazookaFile.c_str(), NULL);
	
	// check images
	for(i=0; i<3; i++)
	{
		if(!images[i])
		{
			allegro_message("Failed to load images");
			exit(1);
		}
	}
	
	// get the sound effect
	powerupSound = load_sample(soundFile.c_str());
	if(!powerupSound)
	{
		allegro_message("%s", "Failure to load powerup sound.");
		exit(1);
	}
}

poweruphandler::~poweruphandler() {
	unsigned int i;
	
	// destroy bitmaps
	for(i=0; i<3; i++)
		if(images[i]) destroy_bitmap(images[i]);
	
	// destroy sprites
	if(!powerups.empty())
	{
		for(i=0; i<powerups.size(); i++)
		{
			if(powerups.at(i))
				delete powerups.at(i);
		}
	}
		
	// destroy sound sample
	if(powerupSound)
		destroy_sample(powerupSound);
	
}

/********************************************
 * 
 * ACCESSORS
 *
 *******************************************/
int poweruphandler::getSize() {
	return powerups.size();
}

powerup *poweruphandler::at(int index) {
	return powerups.at(index);
}

BITMAP *poweruphandler::getImageAt(int index) {
	return images[index];
}

/**************************************
*
* ADDING & USING POWERUPS
*
**************************************/

// adding and using powerups
void poweruphandler::add(int powerupType, int x, int y) {
	// new powerup
	powerups.push_back(new powerup(images[powerupType], powerupType, x, y));
	
	// make it alive
	powerups.back()->makeAlive();
}

// just get the value for this powerup
int poweruphandler::getPowerupValue(int index) {
	return powerups.at(index)->getPowerup();
}

// just the powerup type for one
int poweruphandler::getPowerupType(int index) {
	return powerups.at(index)->getType();
}

// use and delete this powerup
int poweruphandler::usePowerup(int index) {
	int value = getPowerupValue(index);
	
	// make this powerup dead
	powerups.at(index)->makeDead();
	
	// return the value
	return value;
}


/****************************************************
 * 
 * DISPLAY & SOUND
 *
 *****************************************************/
 
void poweruphandler::draw(BITMAP *buffer)
{
	unsigned int i;
	if(!powerups.empty())
	{
		for(i=0; i<powerups.size(); i++)
		{
			if(powerups.at(i)->isAlive()) 
			{
				draw_sprite(buffer, 
					powerups.at(i)->getImage(), powerups.at(i)->getX(),
					powerups.at(i)->getY());
			}
		}
	}
}

void poweruphandler::playNoise() {
	play_sample(powerupSound, VOLUME, PANNING, PITCH, false);
}
	
		
