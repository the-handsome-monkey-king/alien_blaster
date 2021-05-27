/*
 * playersprite.h
 *
 * @author Ryan Morehouse
 * @date May 1, 2018
 *
 * @purpose An extension for the sprite class to be used specifically
 * 	for the Alien Blaster game.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o playersprite.o playersprite.cpp -lalleg -Wall
 */
 
#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H
 
#include <allegro.h>
#include <fstream>
#include "sprite.h"
#include "grabframe.h"

using namespace std;

#define PLAYER_HEALTH 100
#define AMMO_MAX 20
#define GRACE_TIME 1000

class playersprite: public sprite {
	
	// positioning and animation
	int dir;
	int speed;
	int animdir;
	int curframe;
	int framecount, framedelay;
	
	// health and damage
	int health;
	int graceTimer;
	
	// current weapon
	int weapon;
	
	// weapon ammo
	int flameAmmo, bazookaAmmo;
	
	// animation frames
	BITMAP *images[47];
public:
	// constructor & destructor
	playersprite(string filename, int width, int height,
		int columns);
	~playersprite();
	
	// Accessors
	int getDir();
	int getSpeed();
	int getAnimdir();
	int getCurframe();
	int getFrameCount();
	int getFrameDelay();
	int getHealth();
	int getGraceTime();
	int getWeapon();
	int getFlameAmmo();
	int getBazookaAmmo();
	int getAmmoMax();
	
	// Setters
	void setCurframe(int newFrame);
	
	// movement
	void setDirection(int newDirection);
	void move();
	void put(int newX, int newY);
	
	// behaviour
	void updateCurframe();
	void setWeapon(int newWeapon);
	void getFlameAmmo(int ammo);
	void getBazookaAmmo(int ammo);
	void spendFlameAmmo();
	void spendBazookaAmmo();
	
	// health & damage
	void takeDamage(int damage);
	void heal(int life);
	void advanceGraceTimer();
	
	// draw the sprite
	void draw(BITMAP *buffer);
};

#endif
