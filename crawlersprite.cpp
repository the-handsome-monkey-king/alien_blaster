/*
 * crawlersprite.cpp
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
 
#include <allegro.h>
#include "crawlersprite.h"

// constructor & destructor
crawlersprite::crawlersprite(string filename, int width, int height,
	int columns)
{
	int i;
	
	// get sprite images
	BITMAP *sheet = load_bitmap(filename.c_str(), NULL);
	for(i=0; i<8; i++)
		images[i] = grabframe(sheet, width, height, 0, 0, 4, i);
	destroy_bitmap(sheet);
	
	// position and animation
	dir = 0;
	speed = 2;
	animdir = 1;
	curframe = 0;
	framecount = 0;
	framedelay = 100;
	
	setWidth(width);
	setHeight(height);
	setDelayX(5);
	setDelayY(5);
}	
	
crawlersprite::~crawlersprite() {
	int i;
	for(i=0; i<8; i++)
		if(images[i]) destroy_bitmap(images[i]);
}

// Accessors
int crawlersprite::getDir() {
	return dir;
}

int crawlersprite::getSpeed() {
	return speed;
}

int crawlersprite::getAnimdir() {
	return animdir;
}

int crawlersprite::getCurframe() {
	return curframe;
}

int crawlersprite::getFrameCount() {
	return framecount;
}

int crawlersprite::getFrameDelay() {
	return framedelay;
}

BITMAP *crawlersprite::getImageAt(int index) {
	return images[index];
}

int crawlersprite::getDamage() {
	return CRAWLER_DAMAGE;
}

// halt all movement
void crawlersprite::stop() {
	setVelocityX(0);
	setVelocityY(0);
}

// re-establish speed based on dir
void crawlersprite::updateSpeed() {
	switch(dir) {
	case 0:
		setVelocityX(0);
		setVelocityY(-speed);
		break;
		
	case 1:
		setVelocityX(speed);
		setVelocityY(-speed);
		break;
		
	case 2:
		setVelocityX(speed);
		setVelocityY(0);
		break;
		
	case 3:
		setVelocityX(speed);
		setVelocityY(speed);
		break;
		
	case 4:
		setVelocityX(0);
		setVelocityY(speed);
		break;
		
	case 5:
		setVelocityX(-speed);
		setVelocityY(speed);
		break;
		
	case 6:
		setVelocityX(-speed);
		setVelocityY(0);
		break;
		
	case 7:
		setVelocityX(-speed);
		setVelocityY(-speed);
		break;
	}
}


// test movement without kill if pass
void crawlersprite::testmove() {
	
	updateSpeed();
	updatePosition();
	updateAnimation();
	
	// otherwise, bounce sprite
	bool bounced = false;
	if(getX() < 0)
	{
		setX(0);
		bounced = true;
	}
	if(getX() > SCREEN_W - getWidth())
	{
		setX(SCREEN_W - getWidth());
		bounced = true;
	}
	if(getY() < 0)
	{
		setY(0);
		bounced = true;
	}
	if(getY() > SCREEN_H - getHeight())
	{
		setY(SCREEN_H - getHeight());
		bounced = true;
	}
	
	if(bounced)
		bounce();
}
	
	
// movement with input controls
void crawlersprite::control(int direction) {
	
	// update animation frame and speeds based
	// on direction
	switch(direction) {
	case 0:
		// North
		if(animdir == 1) {
			curframe = 3;
		} else {
			curframe = 7;
		}
		
		setVelocityX(0);
		setVelocityY(-speed);
		break;
		
	case 1:
		// NE
		if(animdir == 1)
			curframe = 1;
		else
			curframe = 5;
		
		setVelocityX(speed);
		setVelocityY(-speed);
		break;
		
	case 2:
		// East
		if(animdir == 1)
			curframe = 1;
		else
			curframe = 5;
		
		setVelocityX(speed);
		setVelocityY(0);
		break;
		
	case 3:
		// SE
		if(animdir == 1)
			curframe = 1;
		else
			curframe = 5;
		
		setVelocityX(speed);
		setVelocityY(speed);
		break;
		
	case 4:
		// South
		if(animdir == 1)
			curframe = 0;
		else
			curframe = 4;
		
		setVelocityX(0);
		setVelocityY(speed);
		break;
		
	case 5:
		// SW
		if(animdir == 1)
			curframe = 2;
		else
			curframe = 6;
		
		setVelocityX(-speed);
		setVelocityY(speed);
		break;
		
	case 6:
		// West
		if(animdir == 1)
			curframe = 2;
		else
			curframe = 6;
		
		setVelocityX(-speed);
		setVelocityY(0);
		break;
		
	case 7:
		// NW
		if(animdir == 1)
			curframe = 2;
		else
			curframe = 6;
		
		setVelocityX(-speed);
		setVelocityY(-speed);
		break;
	}
	
	// update sprite position based on new speeds
	updatePosition();
	
	// note the current direction
	dir = direction;
	
	// update the animation
	if(++framecount > framedelay)
	{
		framecount = 0;
		animdir *= -1;
	}
}	

void crawlersprite::put(int newX, int newY) {
	setX(newX);
	setY(newY);
}

void crawlersprite::bounce() {
	dir = rand()%9 -1;
}

void crawlersprite::updateAnimation() {
	
	switch(dir) {
	case 0:
		// North
		if(animdir == 1) {
			curframe = 3;
		} else {
			curframe = 7;
		}
		break;
		
	case 1:
		// NE
		if(animdir == 1)
			curframe = 1;
		else
			curframe = 5;
		break;
		
	case 2:
		// East
		if(animdir == 1)
			curframe = 1;
		else
			curframe = 5;
		break;
		
	case 3:
		// SE
		if(animdir == 1)
			curframe = 1;
		else
			curframe = 5;
		break;
		
	case 4:
		// South
		if(animdir == 1)
			curframe = 0;
		else
			curframe = 4;
		break;
		
	case 5:
		// SW
		if(animdir == 1)
			curframe = 2;
		else
			curframe = 6;
		break;
		
	case 6:
		// West
		if(animdir == 1)
			curframe = 2;
		else
			curframe = 6;
		break;
		
	case 7:
		// NW
		if(animdir == 1)
			curframe = 2;
		else
			curframe = 6;
		break;
	}
	
	// update the framecount
	if(++framecount > framedelay)
	{
		framecount = 0;
		animdir *= -1;
	}
}

// draw the sprite
void crawlersprite::draw(BITMAP *buffer)
{
	draw_sprite(buffer, images[curframe], getX(), getY());
}
