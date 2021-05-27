/*
 * bullethandler.h
 *
 * @author Ryan Morehouse
 * @date May 1, 2018
 *
 * @purpose A sprite handler to manage all bullets for the game
 *		Alien Blaster.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o bullethandler.o bullethandler.cpp -lalleg -Wall
 */
 
#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <allegro.h>
#include <fstream>
#include <iostream>
#include "bulletsprite.h"

#define MAX_BULLETS 10
#define LASER_DMG 1
#define FLAME_DMG 2
#define BAZOOKA_DMG 5

using namespace std;

// audio settings
#define PANNING 128
#define PITCH 1000
#define VOLUME 128



class bullethandler {
	// bullet images
	BITMAP *images[3][8];
	
	//bullets
	bulletsprite *bullets[MAX_BULLETS];
	
	// bullet reload timing
	int reloadTimer;
	
	// game world boundaries
	int mapOffsetX;
	int mapOffsetY;
	
	// weapon sound effects
	SAMPLE *laserSound;
	SAMPLE *flameSound;
	SAMPLE *bazookaSound;
	SAMPLE *impactSound;
	
	
public:
	// bullets
	// public to facilitate collision detection code
	
	
	// constructor & destructor
	bullethandler(
		string laser00, string laser01, string laser02, string laser03,
		string laser04, string laser05, string laser06, string laser07,
		string flame00, string flame01, string flame02, string flame03,
		string flame04, string flame05, string flame06, string flame07,
		string bazooka00, string bazooka01, string bazooka02, string bazooka03,
		string bazooka04, string bazooka05, string bazooka06, string bazooka07,
		int xoffset, int yoffset, string laserSoundFile, string flameSoundFile,
		string bazookaSoundFile, string impactSoundFile);
	~bullethandler();
	
	// Accessors
	int getMaxBullets();
	int isAlive(int index);
	int getReloadTime();
	int getDamage(int index);
	bulletsprite *at(int index);
	
	// movement
	void fire(int weapon, int direction, int x, int y,
		int playerWidth, int playerHeight);
	void updateBullets(int scroll);
	
	// impact noise
	void playImpactNoise();
	
	// draw the bullets
	void draw(BITMAP *buffer);
};

#endif
