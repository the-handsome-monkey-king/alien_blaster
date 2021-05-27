/*
 * playersprite.cpp
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
 
#include <allegro.h>
#include "playersprite.h"

using namespace std;


// constructor & destructor
playersprite::playersprite(string filename, int width, int height,
	int columns)
{
	int i;
	
	// get sprite images
	BITMAP *sheet = load_bitmap(filename.c_str(), NULL);
	for(i=0; i<47; i++)
		images[i] = grabframe(sheet, width, height, 0, 0, 8, i);
	destroy_bitmap(sheet);
	
	// position and animation
	dir = 0;
	speed = 2;
	animdir = 1;
	curframe = 2;
	framecount = 0;
	framedelay = 100;
	
	// health and damage
	health = PLAYER_HEALTH;
	graceTimer = 0;
	
	// set current weapon to laser
	weapon = 0;
	
	// set current extra ammos to 0
	flameAmmo = 0;
	bazookaAmmo = 0;
	
	isAlive();
	setWidth(width);
	setHeight(height);
	setDelayX(5);
	setDelayY(5);
}	
	
playersprite::~playersprite() {
	int i;
	for(i=0; i<47; i++)
		if(images[i]) destroy_bitmap(images[i]);
}

// Accessors
int playersprite::getDir() {
	return dir;
}

int playersprite::getSpeed() {
	return speed;
}

int playersprite::getAnimdir() {
	return animdir;
}

int playersprite::getCurframe() {
	return curframe;
}

int playersprite::getFrameCount() {
	return framecount;
}

int playersprite::getFrameDelay() {
	return framedelay;
}

int playersprite::getHealth() {
	return health;
}

int playersprite::getGraceTime() {
	return graceTimer;
}

int playersprite::getWeapon() {
	return weapon;
}

int playersprite::getFlameAmmo() {
	return flameAmmo;
}

int playersprite::getBazookaAmmo() {
	return bazookaAmmo;
}

int playersprite::getAmmoMax() {
	return AMMO_MAX;
}

// setters

void playersprite::setCurframe(int newFrame) {
	curframe = newFrame;
}

// movement
void playersprite::setDirection(int newDirection) {
	dir = newDirection;
}

void playersprite::move() {
	
	// determine curframes based on weapon
	updateCurframe();
	
	// determine speeds based on direction
		
	// update animation frame and speeds based on direction
	switch(dir) 
	{
		case 0:
			// North
			setVelocityX(0);
			setVelocityY(-speed);
			break;
			
		case 1:
			// NE
			setVelocityX(speed);
			setVelocityY(-speed);
			break;
			
		case 2:
			// East
			setVelocityX(speed);
			setVelocityY(0);
			break;
			
		case 3:
			// SE
			setVelocityX(speed);
			setVelocityY(speed);
			break;
			
		case 4:
			// South
			setVelocityX(0);
			setVelocityY(speed);
			break;
			
		case 5:
			// SW
			setVelocityX(-speed);
			setVelocityY(speed);
			break;
			
		case 6:
			// West
			setVelocityX(-speed);
			setVelocityY(0);
			break;
			
		case 7:
			// NW
			setVelocityX(-speed);
			setVelocityY(-speed);
			break;
	}
		
		
	
	// update sprite position based on new speeds
	updatePosition();
	
	// update the animation
	if(++framecount > framedelay)
	{
		framecount = 0;
		animdir *= -1;
	}
}	

void playersprite::put(int newX, int newY) {
	setX(newX);
	setY(newY);
}

// behaviour
void playersprite::updateCurframe() {
	// determine curframes based on weapon
	switch(weapon) {
	// laser
	case 0:
		
		// update animation frame and speeds based on direction
		switch(dir) 
		{
			case 0:
				// North
				if(animdir == 1) {
					curframe = 2;
				} else {
					curframe = 10;
				}

				break;
				
			case 1:
				// NE
				if(animdir == 1)
					curframe = 3;
				else
					curframe = 11;

				break;
				
			case 2:
				// East
				if(animdir == 1)
					curframe = 1;
				else
					curframe = 9;

				break;
				
			case 3:
				// SE
				if(animdir == 1)
					curframe = 6;
				else
					curframe = 14;

				break;
				
			case 4:
				// South
				if(animdir == 1)
					curframe = 5;
				else
					curframe = 13;

				break;
				
			case 5:
				// SW
				if(animdir == 1)
					curframe = 7;
				else
					curframe = 15;

				break;
				
			case 6:
				// West
				if(animdir == 1)
					curframe = 0;
				else
					curframe = 8;

				break;
				
			case 7:
				// NW
				if(animdir == 1)
					curframe = 4;
				else
					curframe = 12;

				break;
		}
		break;
		
	// flamer 32
	case 1:
		// update animation frame and speeds based on direction
		switch(dir) 
		{
			case 0:
				// North
				if(animdir == 1) {
					curframe = 34;
				} else {
					curframe = 42;
				}

				break;
				
			case 1:
				// NE
				if(animdir == 1)
					curframe = 35;
				else
					curframe = 43;
				
				break;
				
			case 2:
				// East
				if(animdir == 1)
					curframe = 33;
				else
					curframe = 41;
				
				break;
				
			case 3:
				// SE
				if(animdir == 1)
					curframe = 37;
				else
					curframe = 45;

				break;
				
			case 4:
				// South
				if(animdir == 1)
					curframe = 5;
				else
					curframe = 13;

				break;
				
			case 5:
				// SW
				if(animdir == 1)
					curframe = 38;
				else
					curframe = 46;

				break;
				
			case 6:
				// West
				if(animdir == 1)
					curframe = 32;
				else
					curframe = 40;

				break;
				
			case 7:
				// NW
				if(animdir == 1)
					curframe = 36;
				else
					curframe = 44;

				break;
		}
		break;
		
	// bazooka 16
	case 2:
		
		// update animation frame and speeds based on direction
		switch(dir) 
		{
			case 0:
				// North
				if(animdir == 1) 
					curframe = 16;
				else
					curframe = 24;

				break;
				
			case 1:
				// NE
				if(animdir == 1)
					curframe = 19;
				else
					curframe = 27;

				break;
				
			case 2:
				// East
				if(animdir == 1)
					curframe = 21;
				else
					curframe = 29;

				break;
				
			case 3:
				// SE
				if(animdir == 1)
					curframe = 20;
				else
					curframe = 28;

				break;
				
			case 4:
				// South
				if(animdir == 1)
					curframe = 17;
				else
					curframe = 25;

				break;
				
			case 5:
				// SW
				if(animdir == 1)
					curframe = 22;
				else
					curframe = 30;

				break;
				
			case 6:
				// West
				if(animdir == 1)
					curframe = 18;
				else
					curframe = 26;

				break;
				
			case 7:
				// NW
				if(animdir == 1)
					curframe = 23;
				else
					curframe = 31;

				break;
		}
		break;
	}
}

void playersprite::setWeapon(int newWeapon) {
	weapon = newWeapon;
	updateCurframe();
}

void playersprite::getFlameAmmo(int ammo) {
	flameAmmo += ammo;
}

void playersprite::getBazookaAmmo(int ammo) {
	bazookaAmmo += ammo;
}

void playersprite::spendFlameAmmo() {
	flameAmmo--;
	if(flameAmmo < 0)
		flameAmmo = 0;
}

void playersprite::spendBazookaAmmo() {
	bazookaAmmo--;
	if(bazookaAmmo < 0)
		bazookaAmmo = 0;
}

// health & damage
void playersprite::takeDamage(int damage)
{
	if(graceTimer == 0)
	{
		health -= damage;
		graceTimer = GRACE_TIME;
	
		if(health < 1)
			makeDead();
	}
}

void playersprite::heal(int life) {
	health += life;
	
	// can't go above starting max
	if(health > PLAYER_HEALTH)
		health = PLAYER_HEALTH;
}

void playersprite::advanceGraceTimer() {
	graceTimer--;
	
	// just in case
	if(graceTimer < 0)
		graceTimer = 0;
}

// draw the sprite
void playersprite::draw(BITMAP *buffer)
{
	if(graceTimer > 0)
	{
		// flicker while invincible
		if((graceTimer % 5) == 0)
			draw_sprite(buffer, images[curframe], getX(), getY());
	}
	else
		draw_sprite(buffer, images[curframe], getX(), getY());
}
