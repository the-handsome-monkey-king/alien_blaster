/*
 * bullethandler.cpp
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
 
#include <allegro.h>
#include <string>
#include "bullethandler.h"


/*****************************************************
 *
 * Constructor & Destructor
 *
 ******************************************************/
 
bullethandler::bullethandler(
		string laser00, string laser01, string laser02, string laser03,
		string laser04, string laser05, string laser06, string laser07,
		string flame00, string flame01, string flame02, string flame03,
		string flame04, string flame05, string flame06, string flame07,
		string bazooka00, string bazooka01, string bazooka02, string bazooka03,
		string bazooka04, string bazooka05, string bazooka06, string bazooka07,
		int xoffset, int yoffset, string laserSoundFile, string flameSoundFile,
		string bazookaSoundFile, string impactSoundFile)
{
	
	
	int i, j;
	
	// get bullet images
	// laser
	images[0][0] = load_bitmap(laser00.c_str(), NULL);
	images[0][1] = load_bitmap(laser01.c_str(), NULL);
	images[0][2] = load_bitmap(laser02.c_str(), NULL);
	images[0][3] = load_bitmap(laser03.c_str(), NULL);
	images[0][4] = load_bitmap(laser04.c_str(), NULL);
	images[0][5] = load_bitmap(laser05.c_str(), NULL);
	images[0][6] = load_bitmap(laser06.c_str(), NULL);
	images[0][7] = load_bitmap(laser07.c_str(), NULL);
	
	// bazooka
	images[1][0] = load_bitmap(flame00.c_str(), NULL);
	images[1][1] = load_bitmap(flame01.c_str(), NULL);
	images[1][2] = load_bitmap(flame02.c_str(), NULL);
	images[1][3] = load_bitmap(flame03.c_str(), NULL);
	images[1][4] = load_bitmap(flame04.c_str(), NULL);
	images[1][5] = load_bitmap(flame05.c_str(), NULL);
	images[1][6] = load_bitmap(flame06.c_str(), NULL);
	images[1][7] = load_bitmap(flame07.c_str(), NULL);
	
	
	// flame thrower
	images[2][0] = load_bitmap(bazooka00.c_str(), NULL);
	images[2][1] = load_bitmap(bazooka01.c_str(), NULL);
	images[2][2] = load_bitmap(bazooka02.c_str(), NULL);
	images[2][3] = load_bitmap(bazooka03.c_str(), NULL);
	images[2][4] = load_bitmap(bazooka04.c_str(), NULL);
	images[2][5] = load_bitmap(bazooka05.c_str(), NULL);
	images[2][6] = load_bitmap(bazooka06.c_str(), NULL);
	images[2][7] = load_bitmap(bazooka07.c_str(), NULL);
	
	// check images
	for(i=0; i<3; i++)
	{
		for(j=0; j<8; j++) 
		{
			if(!images[i][j])
			{
				allegro_message("Failed to load images[%d][%d]", i, j);
				exit(1);
			}
		}
	}
		
		
	
	// initialize the bullet sprites
	for(i=0; i<MAX_BULLETS; i++)
	{
		bullets[i] = new bulletsprite();
		
	}
	
	// set the reload timer
	reloadTimer = 0;
	
	// set the map boundaries
	mapOffsetX = xoffset;
	mapOffsetY = yoffset;
	
	// get the sound effects
	laserSound = load_sample(laserSoundFile.c_str());
	if(!laserSound)
	{
		allegro_message("%s", "Failure to load laser sound.");
		exit(1);
	}
	
	flameSound = load_sample(flameSoundFile.c_str());
	if(!flameSound)
	{
		allegro_message("%s", "Failure to load flame sound.");
		exit(1);
	}
	
	bazookaSound = load_sample(bazookaSoundFile.c_str());
	if(!bazookaSound)
	{
		allegro_message("%s", "Failure to load bazooka sound.");
		exit(1);
	}
	
	impactSound = load_sample(impactSoundFile.c_str());
	if(!bazookaSound)
	{
		allegro_message("%s", "Failure to load bazooka sound.");
		exit(1);
	}
}

bullethandler::~bullethandler() {
	int i, j;
	
	// destroy bitmaps
	for(i=0; i<3; i++)
		for(j=0; j>8; j++)
			if(images[i][j]) destroy_bitmap(images[i][j]);
		
	// destroy bullet sprites
	for(i=0; i<MAX_BULLETS; i++)
		if(bullets[i]) delete bullets[i];
	
	// destroy sound samples
	if(laserSound)
		destroy_sample(laserSound);
	
	if(flameSound)
		destroy_sample(flameSound);
	
	if(bazookaSound)
		destroy_sample(bazookaSound);
	
	if(impactSound)
		destroy_sample(impactSound);
	
	
}

/********************************************
 * 
 * ACCESSORS
 *
 *******************************************/
int bullethandler::getMaxBullets() {
	return MAX_BULLETS;
}

int bullethandler::isAlive(int index) {
	return bullets[index]->isAlive();
}

int bullethandler::getReloadTime() {
	return reloadTimer;
}

bulletsprite *bullethandler::at(int index) {
	return bullets[index];
}

int bullethandler::getDamage(int index) {
	int weapon = bullets[index]->getWeapon();
	if(weapon == 1)
		return FLAME_DMG;
	else if(weapon == 2)
		return BAZOOKA_DMG;
	
	// if this point just treat as a laser
	return 1;
}


/***********************************************
 * 
 * BEHAVIOURS
 *
 ***********************************************/

void bullethandler::fire(int weapon, int direction, int x, int y,
	int playerWidth, int playerHeight) 
{
	// additional offset for larger flame bullet sprites 
	if(weapon == 1)
	{
		// determine offset based on player sprite direction
		switch(direction){
		case 0:
			// North
			y -= 2*playerHeight;
			break;
			
		case 1:
			// NE
			//x += playerWidth;
			y -= playerHeight;
			//break;
			
		case 2:
			// East
			//x += playerWidth;
			break;
			
		case 3:
			// SE
			//x += playerWidth;
			//y += playerHeight;
			break;
			
		case 4: 
			// South
			//y += playerHeight;
			break;
			
		case 5:
			// SW
			x -= playerWidth;
			//y += playerHeight;
			break;
			
		case 6:
			// West
			x -= 2*playerWidth;
			break;
			
		case 7:
			// NW
			x -= playerWidth;
			y -= playerHeight;
			break;
		}
	}
	
	// additional offset for very large bazooka bullet sprites 
	else if(weapon == 2) {
		// determine offset based on player sprite direction
		switch(direction){
		case 0:
			// North
			y -= playerHeight;
			x -= playerWidth;
			break;
			
		case 1:
			// NE
			//x += playerWidth;
			y -= playerHeight;
			//break;
			
		case 2:
			// East
			//x += playerWidth;
			y -= playerHeight/2;
			break;
			
		case 3:
			// SE
			//x += playerWidth;
			//y += playerHeight;
			break;
			
		case 4: 
			// South
			x -= playerWidth/2;
			break;
			
		case 5:
			// SW
			x -= playerWidth;
			//y += playerHeight;
			break;
			
		case 6:
			// West
			x -= playerWidth;
			y -= playerHeight/2;
			break;
			
		case 7:
			// NW
			x -= playerWidth;
			y -= playerHeight;
			break;
		}
		
	}
	
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(!bullets[i]->isAlive()) {
			
			// fire this bullet
			bullets[i]->launch(weapon, direction, x, y);
			
			// fire appropriate bullet for weapon
			switch(weapon) {
				
			// laser
			case 0:
				// adjust bullet sprite width and height
				bullets[i]->setWidth(images[0][direction]->w);
				bullets[i]->setHeight(images[0][direction]->h);
				
				// play the laser sound
				play_sample(laserSound, VOLUME, PANNING, PITCH, false);
				break;
				
			// flamer
			case 1:
				// adjust bullet sprite width and height
				bullets[i]->setWidth(images[1][direction]->w);
				bullets[i]->setHeight(images[1][direction]->h);
				
				// play the flamer sound
				play_sample(flameSound, VOLUME, PANNING, PITCH, false);
				break;
				
			// bazooka
			case 2:
				// adjust bullet sprite width and height
				bullets[i]->setWidth(images[2][direction]->w);
				bullets[i]->setHeight(images[2][direction]->h);
				
				// play the bazooka sound
				play_sample(bazookaSound, VOLUME, PANNING, PITCH, false);
				break;
			}
			
			break;
		}
	}
	
}

void bullethandler::updateBullets(int scroll)
{
	int i;
	
	// update position of each live bullet
	for(i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i]->isAlive())
		{
			bullets[i]->updatePosition();
			
			// apply map scroll if any
			if(scroll > 0)
				bullets[i]->setY(bullets[i]->getY() + scroll);
		}
	}
	
	// kill bullets that have left the screen
	for(i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i]->getX() < 0 ||
			bullets[i]->getX() > SCREEN_W - mapOffsetX ||
			bullets[i]->getY() < 0 ||
			bullets[i]->getY() > SCREEN_H - mapOffsetY)
		{
			bullets[i]->makeDead();
		}
	}
		
		
	
	// increment reload timer
	if(reloadTimer > 0)
		reloadTimer--;
}

void bullethandler::playImpactNoise() {
	play_sample(impactSound, VOLUME, PANNING, PITCH, false);
}


/****************************************************
 * 
 * DISPLAY
 *
 *****************************************************/
 
void bullethandler::draw(BITMAP *buffer)
{
	int i;
	for(i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i]->isAlive()) 
		{
			draw_sprite(buffer, 
				images[bullets[i]->getWeapon()][bullets[i]->getDir()], 
				bullets[i]->getX(), bullets[i]->getY());
		}
	}
}
	
		
