/*
 * alienblaster.cpp
 *
 * @author Ryan Morehouse
 * @date May 27, 2018
 * @version 1.0
 *
 * @purpose The main file for the Alien Blaster engine
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o alienblaster.o alienblaster.cpp -lalleg -Wall
 */
 
#include <allegro.h>
#include <string>
#include <iostream>
#include "alienblaster.h"


/********************************************
*
* CONSTRUCTOR
*
********************************************/

// initialize allegro & set configs
AlienBlaster::AlienBlaster(Config *config) {
  // set configs
  this->config = config;
  
  // once enough allegro code is encapsulated, this can be
  // implmented and tested
  this->allegro = AllegroLayer(config, WIDTH, HEIGHT);

  // defaults to 0
  int fullscreenMode = atoi(config->getOption("fullscreen").c_str());

  // initialize allegro
  allegro_init();
  
  // confiure graphics
  set_color_depth(16);
  if(fullscreenMode == 1) {
    set_gfx_mode(FULL, WIDTH, HEIGHT, 0, 0);
  } else {
    set_gfx_mode(WINDOW, WIDTH, HEIGHT, 0, 0);
  }

  // configure music mode required drivers
  // install allegro audio drivers without midi
  if(install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0) {
    allegro_message("%s", "Error initializing the sound system.");
    exit(1);
  }
  
  // controllers and timer
  install_keyboard();
  install_timer();
  srand(time(NULL));
}

AlienBlaster::~AlienBlaster() {
  // shutdown allegro
  remove_sound();
	allegro_exit();
}


/********************************************
*
* DISPLAY
*
********************************************/

void render(BITMAP *buffer) 
{
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	release_screen();
}

void drawSprites(BITMAP *buffer, playersprite *player,
	bullethandler *bullets, poweruphandler *powerups, 
	vector<crawlersprite*> *crawlers, 
	vector<centipede*> *centipedes, vector<boss*> *bosses)
{
	// draw player, bullets, and enemies on buffer
	player->draw(buffer);
	bullets->draw(buffer);
	powerups->draw(buffer);
	
	unsigned int i;
	// draw crawlers
	if(crawlers->size())
	{
		for(i=0; i<crawlers->size(); i++)
		{
			if(crawlers->at(i)->isAlive())
				crawlers->at(i)->draw(buffer);
		}
	}
	
	// draw centipedes
	if(crawlers->size())
	{
		for(i=0; i<centipedes->size(); i++)
		{
			if(centipedes->at(i)->isAlive())
				centipedes->at(i)->draw(buffer);
		}
	}
	
	// draw boss
	if(bosses->size())
	{
		if(bosses->at(0)->isAlive())
			bosses->at(0)->draw(buffer);
	}
}

void drawGauges(BITMAP *buffer, BITMAP *gauge, BITMAP *healthIcon,
	BITMAP *flameIcon, BITMAP *bazookaIcon,
	playersprite *player) 
{
	
	// determine player health as a percent
	double lifePercent = (double)player->getHealth() / (double)PLAYER_HEALTH;
	// convert health percent into a gauge length
	int healthGaugeLength = lifePercent * (GAUGE_LENGTH - GAUGE_BORDER);
	
	// health icon dimensions
	int iconWidth = healthIcon->w;
	int iconHeight = healthIcon->h;
	
	// gauge placement
	int gaugeX = SCREEN_W - gauge->w - 10;
	int gaugeIconX = SCREEN_W - gauge->w - 20 - iconWidth;
	int gaugeY = 10;
	
	// draw health icon
	stretch_sprite(buffer, healthIcon, gaugeIconX + iconWidth/2, gaugeY,
		iconWidth/2, iconHeight/2);
	
	// draw health gauge
	draw_sprite(buffer, gauge, gaugeX, gaugeY);
	// fill life gauge
	rectfill(buffer, gaugeX + GAUGE_BORDER, gaugeY + GAUGE_BORDER, 
		gaugeX + healthGaugeLength, gaugeY + GAUGE_BORDER + 10, RED);
	
	
	// flame icon dimensions
	iconWidth = flameIcon->w;
	iconHeight = flameIcon->h;
	
	// gauge placement
	gaugeY += 20;
	
	// draw flame icon
	stretch_sprite(buffer, flameIcon, gaugeIconX + iconWidth/2, gaugeY,
		iconWidth/2, iconHeight/2);
	// draw flame gauage
	draw_sprite(buffer, gauge, gaugeX, gaugeY);
	if(player->getFlameAmmo() == 0)
	{
		rectfill(buffer, gaugeX + GAUGE_BORDER, gaugeY + GAUGE_BORDER,
			gaugeX + GAUGE_LENGTH - GAUGE_BORDER, gaugeY + GAUGE_BORDER + 10, BLACK);
	}
	else
	{
		// get flame ammo as a gauge length
		double flamePercent = (double)player->getFlameAmmo() / (double)player->getAmmoMax();
		int flameGaugeLength = flamePercent * (GAUGE_LENGTH - GAUGE_BORDER);
	
		// fill flame gauge
		rectfill(buffer, gaugeX + GAUGE_BORDER, gaugeY + GAUGE_BORDER, 
			gaugeX + flameGaugeLength, gaugeY + GAUGE_BORDER + 10, RED);
	}
	
	// bazooka icon dimensions
	iconWidth = bazookaIcon->w;
	iconHeight = bazookaIcon->h;
	// gauge placement
	gaugeY += 20;
	// draw bazooka icon
	stretch_sprite(buffer, bazookaIcon, gaugeIconX + iconWidth/2, gaugeY,
		iconWidth/2, iconHeight/2);
	// draw bazooka gauage
	draw_sprite(buffer, gauge, gaugeX, gaugeY);
	
	if(player->getBazookaAmmo() == 0)
	{
		rectfill(buffer, gaugeX + GAUGE_BORDER, gaugeY + GAUGE_BORDER,
			gaugeX + GAUGE_LENGTH - GAUGE_BORDER, gaugeY + GAUGE_BORDER + 10, BLACK);
	}
	else
	{
		// get bazooka ammo as a gauge length
		double bazookaPercent = (double)player->getBazookaAmmo() / (double)player->getAmmoMax();
		int bazookaGaugeLength = bazookaPercent * (GAUGE_LENGTH - GAUGE_BORDER);
	
		// fill bazooka gauge
		rectfill(buffer, gaugeX + GAUGE_BORDER, gaugeY + GAUGE_BORDER, 
			gaugeX + bazookaGaugeLength, gaugeY + GAUGE_BORDER + 10, RED);
	}
}

void displayScreenCard(BITMAP *titleScreen) 
{
	render(titleScreen);
	
	// wait out a held-down key
	while(key[KEY_ENTER]) {
		// WAIT
		
		// ESC always exits
		if(key[KEY_ESC])
			exit(0);
	}
	
	// clear keyboard input buffer
	clear_keybuf();
	
	// wait for player to press enter
	while(!key[KEY_ENTER])
	{
		// wait
		
		// ESC always exits
		if(key[KEY_ESC])
			exit(0);
	}
}

// void displayInstructions(BITMAP *instructionsScreen);
// void displayWin(BITMAP *winScreen);
// void displayLose(BITMAP *loseScreen);


/********************************************
*
* MAP FOREGROUND COLLISION DETECTION
*
********************************************/

int mapCollision(int x, int y) {
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}

int spriteMapCollision(sprite* s, int yoffset) {
	int spriteX = s->getX();
	int spriteY = s->getY() + yoffset;
	int spriteW = s->getWidth();
	int spriteH = s->getHeight();
	
	// return true if any corner has a collision
	if(mapCollision(spriteX, spriteY) ||
		mapCollision(spriteX + spriteW, spriteY) ||
		mapCollision(spriteX + spriteW, spriteY + spriteH) ||
		mapCollision(spriteX, spriteY + spriteH))
	{
		return 1;
	}
	
	// otherwise, return 0
	return 0;
}


/******************************************
*
* PLAYER MOVEMENT, MAP SCROLLING, FIRE WEAPONS 
*
*******************************************/

// returns true if player moved
bool playerInput(playersprite *player)
{
	// process player weapon input
	if(key[KEY_1])
		player->setWeapon(0);
	if(key[KEY_2])
		player->setWeapon(1);
	if(key[KEY_3])
		player->setWeapon(2);
	
	// reset movement flag
	bool moved = false;
	
	
	// player movement input
	if(key[KEY_UP] && key[KEY_RIGHT]) 
	{
		moved = true;
		player->setDirection(1);
	}
	else if(key[KEY_UP] && key[KEY_LEFT])
	{
		moved = true;
		player->setDirection(7);
	}
	else if(key[KEY_DOWN] && key[KEY_RIGHT])
	{
		moved = true;
		player->setDirection(3);
	}
	else if(key[KEY_DOWN] && key[KEY_LEFT])
	{
		moved = true;
		player->setDirection(5);
	}
	else if(key[KEY_UP])
	{
		moved = true;
		player->setDirection(0);
	}
	else if(key[KEY_RIGHT])
	{
		moved = true;
		player->setDirection(2);
	}
	else if(key[KEY_DOWN])
	{
		moved = true;
		player->setDirection(4);
	}
	else if(key[KEY_LEFT])
	{
		moved = true;
		player->setDirection(6);
	}
	
	return moved;
}

// move the player w/ map collision resolution
void movePlayer(playersprite *player, int mapyoffset)
{
	int oldX = player->getX();
	int oldY = player->getY();
	
	// adjust player x,y
	player->move();
	
	// keep player x in the screen
	if(player->getX() < 0)
		player->setX(0);
	else if(player->getX() > SCREEN_W - player->getWidth())
		player->setX(SCREEN_W - player->getWidth());
	
	// keep player y in the screen
	if(player->getY() < 0)
		player->setY(0);
	if(player->getY() > SCREEN_H - player->getHeight())
		player->setY(SCREEN_H - player->getHeight());
	
	if(spriteMapCollision(player, mapyoffset))
	{
		player->setX(oldX);
		player->setY(oldY);
	}
}

// fire weapons
void fire(playersprite *player, bullethandler *bullets)
{
	// check weapon
	int weapon = player->getWeapon();
	bool enoughAmmo = false;
	
	// ensure enough ammo for weapon
	switch(weapon) {
	case 0:
		// laser, always enough ammo
		enoughAmmo = true;
		break;
	case 1:
		// flamer
		if(player->getFlameAmmo() > 0)
		{
			player->spendFlameAmmo();
			enoughAmmo = true;
		}
		break;
	case 2:
		// bazooka
		if(player->getBazookaAmmo() > 0)
		{
			player->spendBazookaAmmo();
			enoughAmmo = true;
		}
		break;
	}
	
	if(enoughAmmo)
	{
		bullets->fire(weapon, player->getDir(), 
				player->getX() + player->getWidth()/2, 
				player->getY() + player->getHeight()/2,
				player->getWidth(), player->getHeight());
	}
}

/******************************************
*
* SPAWN ENEMIES
*
*******************************************/

void spawnCrawler(
	vector<crawlersprite*> *crawlers, 
	string crawlerFile, playersprite *player)
{
	// make a new sprite
	crawlers->push_back(new crawlersprite(crawlerFile.c_str(), 32, 32, 4));
	
	// place sprite randomly
	crawlers->back()->put(
		rand() % (SCREEN_W - crawlers->back()->getWidth()),
		rand() % (SCREEN_H - crawlers->back()->getHeight()));
	
	// if the sprite collides with the player, put it somewhere else
	while(player->collided(crawlers->back(), 10))
	{
		// place sprite randomly
		crawlers->back()->put(
			rand() % (SCREEN_W - crawlers->back()->getWidth()),
			rand() % (SCREEN_H - crawlers->back()->getHeight()));
	}
	
	// ensure sprite is alive
	crawlers->back()->makeAlive();
}

void spawnCentipede(vector<centipede*> *centipedes, 
	string centipedeFile, playersprite *player)
{
	// make a new sprite
	centipedes->push_back(new centipede(centipedeFile.c_str(), 32, 21, 8));
	
	// place sprite randomly
	centipedes->back()->put(
		rand() % (SCREEN_W - centipedes->back()->getWidth()),
		rand() % (SCREEN_H - centipedes->back()->getHeight()));
	
	// if the sprite collides with the player, put it somewhere else
	while(player->collided(centipedes->back(), 10))
	{
		centipedes->back()->put(
			rand() % (SCREEN_W - centipedes->back()->getWidth()),
			rand() % (SCREEN_H - centipedes->back()->getHeight()));
	}
	
	// ensure sprite is alive
	centipedes->back()->makeAlive();
}

void spawnBoss(vector<boss*> *bosses,
	string bossFile, playersprite *player)
{
	bosses->push_back(new boss(bossFile.c_str(), 137, 86, 2));
	bosses->back()->put(
		rand() % (SCREEN_W - bosses->back()->getWidth()),
		rand() % (SCREEN_H - bosses->back()->getHeight()));
	
	// if the sprite collides with the player, put it somewhere else
	while(player->collided(bosses->back(), 10))
	{
		bosses->back()->put(
		rand() % (SCREEN_W - bosses->back()->getWidth()),
		rand() % (SCREEN_H - bosses->back()->getHeight()));
	}
	
	// set initial destination for boss
	bosses->back()->setDest(BOSS_X1, BOSS_Y1);
}

/****************************************
*
* ENEMY MOVEMENT
*
******************************************/

void moveCrawlers(vector<crawlersprite*> *crawlers,
	int scroll, int mapyoffset)
{
	int unsigned i;
	if(!crawlers->empty())
	{
		for(i=0; i<crawlers->size(); i++)
		{
			if(crawlers->at(i)->isAlive())
			{
				crawlersprite *cs = crawlers->at(i);
				// first apply any map scrolling
				cs->setY(cs->getY() + scroll);
				
				// store previous values
				int oldX = crawlers->at(i)->getX();
				int oldY = crawlers->at(i)->getY();
				
				// move sprite
				crawlers->at(i)->testmove();
				
				// determine & resolve map foreground collisions
				if(spriteMapCollision(crawlers->at(i), mapyoffset))
				{
					crawlers->at(i)->setX(oldX);
					crawlers->at(i)->setY(oldY);
					crawlers->at(i)->bounce();
				}
			}
		}
	}
}

void moveCentipedes(vector<centipede*> *centipedes,
	int scroll, int mapyoffset)
{
	unsigned int i, j;
	if(!centipedes->empty())
	{
		for(i=0; i<centipedes->size(); i++)
		{
				
			if(centipedes->at(i)->isAlive())
			{
				centipede *c = centipedes->at(i);
				
				// first apply any map scrolling
				c->setY(c->getY() + scroll);
			
				// just kill it if it's scrolled past
				if(c->getY() > SCREEN_H)
					c->makeDead();
				
				// otherwise proceed
				else
				{
					// apply scroll to rest of body
					for(j=0; j<(unsigned)centipedes->at(i)->getLength(); j++)
					{
						sprite *s = centipedes->at(i)->getSeg(j);
						s->setY(s->getY() + scroll);
					}
					
					// move the entire centipede normally
					centipedes->at(i)->move();
				}
			}
		}
	}
}

void moveBosses(vector<boss*> *bosses, playersprite *player, int scroll, int mapyoffset)
{
	if(!bosses->empty())
	{
		if(bosses->at(0)->isAlive())
		{
			/** Version 1.0 movement
			if(bosses->at(0)->getX() == BOSS_X1 && bosses->at(0)->getY() == BOSS_Y1)
			{
				bosses->at(0)->setDest(BOSS_X2, BOSS_Y2);
			}
			else if(bosses->at(0)->getX() == BOSS_X2 && bosses->at(0)->getY() == BOSS_Y2)
			{
				bosses->at(0)->setDest(BOSS_X3, BOSS_Y3);
			}
			else if(bosses->at(0)->getX() == BOSS_X3 && bosses->at(0)->getY() == BOSS_Y3)
			{
				bosses->at(0)->setDest(BOSS_X4, BOSS_Y4);
			}
			else if(bosses->at(0)->getX() == BOSS_X4 && bosses->at(0)->getY() == BOSS_Y4)
			{
				bosses->at(0)->setDest(BOSS_X1, BOSS_Y1);
			}
			
			bosses->at(0)->move();
			**/
			
			// version 2.0 movement
			if(bosses->at(0)->isReadyToUpdateDestination())
			{
				// set destination to player's current location
				bosses->at(0)->setDest(player->getX(), player->getY());
			}
			
			// move boss if ready
			if(bosses->at(0)->isMoving())
				bosses->at(0)->moveWithAI();
			
				
				
		}
	}
}

void movePowerups(poweruphandler *powerups, int scroll)
{
	int i;
	
	if(powerups->getSize() > 0)
	{
		for(i=0; i<powerups->getSize(); i++)
		{
			if(powerups->at(i)->isAlive())
			{
				powerups->at(i)->setY(powerups->at(i)->getY() + scroll);
				
				// just kill it if it's scrolled past
				if(powerups->at(i)->getY() > SCREEN_H)
					powerups->usePowerup(i);
			}
		}
	}
}
			
			


/******************************************
*
* BULLET COLLISIONS AND RESOLUTION
*
******************************************/

void resolveBulletCollisions(
	bullethandler *bullets, int maxBullets,
	vector<crawlersprite*> *crawlers,
	vector<centipede*> *centipedes,
	vector<boss*> *bosses,
	poweruphandler *powerups, int mapyoffset) 
{
	unsigned int i, j, k;
	bool hasCollided;
	
	// foreach bullet
	for(i=0; i<(unsigned)maxBullets; i++)
	{
		// loop flag
		hasCollided = false;
		
		// if the bullet is alive
		if(bullets->at(i)->isAlive())
		{
			if(crawlers->size())
			{
				// foreach crawlersprite
				for(j=0; j<crawlers->size(); j++)
				{
					// if the crawlersprite is alive
					if(crawlers->at(j)->isAlive())
					{
						// if there is a collision
						if(bullets->at(i)->collided(crawlers->at(j), 0))
						{
							// kill bullet and sprite
							bullets->at(i)->makeDead();
							crawlers->at(j)->makeDead();
							
							// play the impact noise
							bullets->playImpactNoise();
							
							// set the collision flag
							hasCollided = true;
							
							// break the foreach crawlersprite loop
							break;
						}
					}
				} 
			} // end crawlers check
			
			// if there has been a collision, skip remaining
			// enemy sprite checks
			if(hasCollided)
				continue;
			
			
			if(centipedes->size())
			{
				// foreach centipede sprite
				for(j=0; j<centipedes->size(); j++)
				{
					// if the centipede is alive
					if(centipedes->at(j)->isAlive())
					{
						// if there is a head collision
						if(bullets->at(i)->collided(centipedes->at(j), 0))
						{
							// deal weapon damage to head
							int damage = bullets->getDamage(i);
							centipedes->at(j)->takeHeadDamage(damage);
								
							// kill the bullet
							bullets->at(i)->makeDead();
							
							// play the impact noise
							bullets->playImpactNoise();
							
							// set the collision flag
							hasCollided = true;
							
							// spawn a powerup
							if(!centipedes->at(j)->isAlive())
								spawnRandomPowerup(powerups, mapyoffset);
							
							// break the foreach centipede loop
							break;
						}
						
						// if there is no collision with head, check segments
						else
						{
							// foreach segment
							for(k=0; k<(unsigned)centipedes->at(j)->getLength(); k++)
							{
								// if the segment is alive
								if(centipedes->at(j)->getSeg(k)->isAlive())
								{
									// if there is a segment collision
									if(bullets->at(i)->collided(centipedes->at(j)->getSeg(k), 0))
									{
										// deal weapon damage to segment
										int damage = bullets->getDamage(i);
										centipedes->at(j)->takeSegDamage(k, damage);
										
										// kill the bullet
										bullets->at(i)->makeDead();
										
										// play the impact noise
										bullets->playImpactNoise();
										
										// set the collision flag
										hasCollided = true;
										
										// if the segment is dead, chance to drop a powerup
										if(!centipedes->at(j)->getSeg(k)->isAlive())
											if(rand() % 10 > 5)
												spawnRandomPowerup(powerups, mapyoffset);
										
										// break the foreach segment loop
										break;
									}
								}
							} // end foreach segment loop
							
							
						}
					}
					
					// if a collision detected, break the foreach centipede loop
					if(hasCollided)
						break;
					
				}
			} // end centipede loop
			
			
			// if a collision detected, skip to next bullet
			if(hasCollided)
				continue;
			
			// if the boss is alive
			if(bosses->size())
			{
				if(bosses->at(0)->isAlive())
				{
					// if there is a collision
					if(bullets->at(i)->collided(bosses->at(0), 0))
					{
						int damage = bullets->getDamage(i);
						bosses->at(0)->takeDamage(damage);
						
						// kill the bullet
						bullets->at(i)->makeDead();
						
						// play the impact noise
						bullets->playImpactNoise();
					}
				}
			}
				
			
		} // end if bullet is alive
	} // end foreach bullet loop
}


/****************************************
* 
* ENEMY COLLISION & PLAYER HEALTH
*
***************************************/

void resolveEnemyCollision(playersprite *player, SAMPLE *hurtSound,
	vector<crawlersprite*> *crawlers,
	vector<centipede*> *centipedes,
	vector<boss*> *bosses)
{
	if(player->getGraceTime() > 0)
	{
		// advance timer
		player->advanceGraceTimer();
	}
	
	// otherwise, check for enemy collisions
	else
	{
		unsigned int i,j;
		// crawlers
		if(crawlers->size() > 0)
		{
			// foreach crawler
			for(i=0; i<crawlers->size(); i++)
			{
				if(crawlers->at(i)->isAlive())
				{
					// if collision detected
					if(player->collided(crawlers->at(i), 0))
					{
						if(player->getGraceTime() == 0)
						{
							player->takeDamage(crawlers->at(i)->getDamage());
							play_sample(hurtSound, VOLUME + 100, PANNING, PITCH, false);
						}
					}
				}
			}
		} // end crawlers 
		
		// foreach centipede
		if(centipedes->size() > 0)
		{
			for(i=0; i<centipedes->size(); i++)
			{
				// if centipede is alive
				if(centipedes->at(i)->isAlive())
				{
					// if head collision detected
					if(player->collided(centipedes->at(i), 0))
					{
						player->takeDamage(centipedes->at(i)->getDamage());
						play_sample(hurtSound, VOLUME +100, PANNING, PITCH, false);
					}
					
					// foreach segment
					for(j=0; j<(unsigned)centipedes->at(i)->getLength(); j++)
					{
						// if segment is alive
						if(centipedes->at(i)->getSeg(j)->isAlive())
						{
							// if segment collision detected
							if(player->collided(centipedes->at(i)->getSeg(j), 0))
							{
								player->takeDamage(centipedes->at(i)->getDamage());
								play_sample(hurtSound, VOLUME +100, PANNING, PITCH, false);
							}
						}
					} // end foreach segment
				}
			} 
		} // end centipedes
		
		// boss
		if(bosses->size() > 0)
		{
			if(player->collided(bosses->at(0), 0))
			{
				player->takeDamage(bosses->at(0)->getDamage());
				play_sample(hurtSound, VOLUME +100, PANNING, PITCH, false);
			}
		} // end boss
		
	}
}

/*****************************************
*
* POWERUPS COLLISION & RESOLUTION
*
******************************************/

void spawnHealth(poweruphandler *powerups, int mapyoffset)
{
	powerups->add(0, 
		rand() % SCREEN_W, 
		rand() % SCREEN_H);
	
	// ensure it doesn't spawn on a foreground tile
	while(spriteMapCollision(
		powerups->at(powerups->getSize() -1), mapyoffset))
	{
		powerups->at(powerups->getSize() -1)->setX(rand() % SCREEN_W);
		powerups->at(powerups->getSize() -1)->setY(rand() % SCREEN_H);
	}
			
}

void spawnFlame(poweruphandler *powerups, int mapyoffset)
{
	powerups->add(1, 
		rand() % SCREEN_W, 
		rand() % SCREEN_H);
	
	// ensure it doesn't spawn on a foreground tile
	while(spriteMapCollision(
		powerups->at(powerups->getSize() -1), mapyoffset))
	{
		powerups->at(powerups->getSize() -1)->setX(rand() % SCREEN_W);
		powerups->at(powerups->getSize() -1)->setY(rand() % SCREEN_H);
	}
}

void spawnBazooka(poweruphandler *powerups, int mapyoffset)
{
	powerups->add(2, 
		rand() % SCREEN_W, 
		rand() % SCREEN_H);
	
	// ensure it doesn't spawn on a foreground tile
	while(spriteMapCollision(
		powerups->at(powerups->getSize() -1), mapyoffset))
	{
		powerups->at(powerups->getSize() -1)->setX(rand() % SCREEN_W);
		powerups->at(powerups->getSize() -1)->setY(rand() % SCREEN_H);
	}
}

void spawnRandomPowerup(poweruphandler *powerups, int mapyoffset) 
{
	int randomType = (rand() % 4) -1;
	switch(randomType) {
	case 0:
		spawnHealth(powerups, mapyoffset);
		break;
	case 1:
		spawnFlame(powerups, mapyoffset);
		break;
	case 2:
		spawnBazooka(powerups, mapyoffset);
		break;
	}
}

void resolvePowerupCollision(playersprite *player,
	poweruphandler *powerups)
{
	int i;
	
	if(powerups->getSize() > 0)
	{
		for(i=0; i< powerups->getSize(); i++)
		{ 
			if(powerups->at(i)->isAlive() && player->collided(powerups->at(i), 0))
			{
				// get powerup type
				int type = powerups->getPowerupType(i);
				
				// get powerup value
				int value = powerups->usePowerup(i);
				
				switch(type) {
				case 0:
					// health
					player->heal(value);
					break;
				case 1:
					// flame ammo
					player->getFlameAmmo(value);
					break;
				case 2:
					// bazooka ammo
					player->getBazookaAmmo(value);
					break;
				}
				
				// play a sound
				powerups->playNoise();
				
				// only pick up one at a time
				return;
			}
		}
	}
}


					

/**************************************
*
* RUN THE GAME
*
****************************************/

// temp wrapper to encapsulate controls within game
// and to buffer changes made to run()
void AlienBlaster::runWrapper()
      
{
  while(isPlayerQuitGame() == false)
	{
		run();
	}
}

void AlienBlaster::run()
{
	
	// INITIATE GAME RESOURCES
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
	clear(buffer);
	
	// get the title, intro, help, and gameover screens
	BITMAP *titleScreen = load_bitmap("screens/title.bmp", NULL);
	if(!titleScreen)
	{
		allegro_message("Failed to load title card");
		exit(1);
	}
	
	BITMAP *intro01Screen = load_bitmap("screens/intro01.bmp", NULL);
	if(!intro01Screen)
	{
		allegro_message("Failed to load intro01 card");
		exit(1);
	}
	
	BITMAP *intro02Screen = load_bitmap("screens/intro02.bmp", NULL);
	if(!intro02Screen)
	{
		allegro_message("Failed to load intro02 card");
		exit(1);
	}
	
	BITMAP *helpScreen = load_bitmap("screens/instructions.bmp", NULL);
	if(!helpScreen)
	{
		allegro_message("Failed to load help card");
		exit(1);
	}
	
	BITMAP *winScreen = load_bitmap("screens/win.bmp", NULL);
	if(!winScreen)
	{
		allegro_message("Failed to load win screen card");
		exit(1);
	}
	
	BITMAP *loseScreen = load_bitmap("screens/lose.bmp", NULL);
	if(!loseScreen)
	{
		allegro_message("Failed to load lose screen card");
		exit(1);
	}
	
	
	// a counter
	unsigned int i;
	
	// load the mappy game map
  
	MapLoad((char*)this->config->getOption("map").c_str());
	
	// map scroll coordinates
	int mapHeight = mapheight * mapblockheight;
	int BOTTOM = mapHeight - SCREEN_H;
	int mapyoffset = BOTTOM;
	
	
	// initialize and place player
	playersprite player(
      this->config->getOption("playerSprite").c_str(), 32, 32, 8);
	playersprite *playerPointer = &player;
	int x = SCREEN_W/2;
	int y = SCREEN_H/2 +10;
	player.put(x,y);
	player.makeAlive();
	
	// load the player injury sound
	SAMPLE* playerHurtSound = load_sample(
      this->config->getOption("playerHurtSound").c_str());
	if(!playerHurtSound)
	{
		allegro_message("Couldn't load playerHurtSound");
		exit(1);
	}
	
	
	// store position & movement data
	bool moved;
	int scroll;
	
	// bullethandler, pointer, and maxBullets
	bullethandler bullets(
		// laser sprite images
    this->config->getOption("laser00"),
    this->config->getOption("laser01"),
    this->config->getOption("laser02"),
    this->config->getOption("laser03"),
    this->config->getOption("laser04"),
    this->config->getOption("laser05"),
    this->config->getOption("laser06"),
    this->config->getOption("laser07"),
		// flame sprite images
    this->config->getOption("flame00"),
    this->config->getOption("flame01"),
    this->config->getOption("flame02"),
    this->config->getOption("flame03"),
    this->config->getOption("flame04"),
    this->config->getOption("flame05"),
    this->config->getOption("flame06"),
    this->config->getOption("flame07"),
		// bazooka sprite images
    this->config->getOption("bazooka00"),
    this->config->getOption("bazooka01"),
    this->config->getOption("bazooka02"),
    this->config->getOption("bazooka03"),
    this->config->getOption("bazooka04"),
    this->config->getOption("bazooka05"),
    this->config->getOption("bazooka06"),
    this->config->getOption("bazooka07"),
		// xy offsets, leave 0
		0, 0,
		// bullet sounds
    this->config->getOption("laserSoundFile"),
    this->config->getOption("flameSoundFile"),
    this->config->getOption("bazookaSoundFile"),
    this->config->getOption("impactSoundFile")
  );
	
	bullethandler *bulletsPointer = &bullets;
	unsigned int maxBullets = bullets.getMaxBullets();
	
	// a weapon fire rate timer
	int reloadTimer = 0;
	
	
	
	// enemy sprites, handlers, & pointers
	vector<crawlersprite*> crawlers;
	vector<crawlersprite*> *crawlersPointer = &crawlers;
	vector<centipede*> centipedes;
	vector<centipede*> *centipedesPointer = &centipedes;
	vector<boss*> bosses;
	vector<boss*> *bossesPointer = &bosses;
	
	// a timer for boss crawler spawning
	int bossTimer = 0;
	
	// a flag if the player dies
	bool playerDead = false;
	
	// a flag if the player wins
	bool playerWon = false;
	
	// enemy spawn point flags
	bool spawnpoint01 = false;
	bool spawnpoint02 = false;
	bool spawnpoint03 = false;
	bool spawnpoint04 = false;
	bool spawnpoint05 = false;
	bool spawnpoint06 = false;
	bool bossspawnpoint = false;

	
	// powerups
	poweruphandler powerups(
      this->config->getOption("healthPowerup"),
      this->config->getOption("flameAmmoFile"),
      this->config->getOption("bazookaAmmoFile"),
      this->config->getOption("powerupSoundFile"));
	poweruphandler *powerupsPointer = &powerups;
	

	// Life and ammo gauge resources
	BITMAP *gauge = load_bitmap("images/lifegauge.bmp", NULL);
	BITMAP *healthIcon = load_bitmap(
      this->config->getOption("healthPowerup").c_str(), NULL);
	BITMAP *flameIcon = load_bitmap(
      this->config->getOption("flameAmmoFile").c_str(), NULL);
	BITMAP *bazookaIcon = load_bitmap(
      this->config->getOption("bazookaAmmoFile").c_str(), NULL);
	
	// get the soundtrack
	SAMPLE *soundtrack = load_sample(
      this->config->getOption("soundtrackFile").c_str());
	if(!soundtrack)
	{
		allegro_message("Couldn't load soundtrack");
		exit(1);
	}
	
	
	/*******************************************
	*
	* GAME INTRO
	*
	*******************************************/
	// initialize this particular game
	displayScreenCard(titleScreen);
	displayScreenCard(intro01Screen);
	displayScreenCard(intro02Screen);
	
	/********************************************
	*
	* NEW GAME LOOP
	*
	*******************************************/
	int musicVoice = play_sample(soundtrack, VOLUME, PANNING, PITCH, true);
	
	// music toggle
	bool musicOn = true;
	
	while(isPlayerQuitGame() == false)
	{
		clear(buffer);
		
		// if the player has one, display the win screen
		if(playerWon)
		{
			render(winScreen);
			stop_sample(soundtrack);
			
			// wait for player to press enter
			while(!key[KEY_ENTER])
			{
				// wait
				
				// ESC always exits
				if(key[KEY_ESC])
					exit(0);
			}
			
			// break game loop
			break;
		}
		
		// if the player is dead, display the death screen
		if(playerDead)
		{
			render(loseScreen);
			stop_sample(soundtrack);
			
			// wait for player to press enter
			while(!key[KEY_ENTER])
			{
				// wait
				
				// ESC always exits
				if(key[KEY_ESC])
					exit(0);
			}
			
			// break game loop
			break;
		}
			
		
		// listen for instructions request
		if((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_H])
		{			
			
			render(helpScreen);
			voice_stop(musicVoice);
			
			// wait for player to press enter
			while(!key[KEY_ENTER])
			{
				// wait
				
				// ESC always exits
				if(key[KEY_ESC])
					exit(0);
			}
			
			// skip rest of loop
			continue;
		}
			
		
		/**************************************
		 *
		 * PLAYER CONTROLS
		 *
		 ****************************************/
		
		// reset movement flag
		moved = false;
		
		// listen for music toggle
		if((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_M])
		{
			if(musicOn)
			{
				stop_sample(soundtrack);
				musicOn = false;
			}
			else
			{
				play_sample(soundtrack, VOLUME, PANNING, PITCH, true);
				musicOn = true;
			}
		}
		
		// process player weapon input
		moved = playerInput(playerPointer);

		
		/******************************************
		*
		* PLAYER MOVEMENT, MAP SCROLLING, FIRE WEAPONS 
		*
		*******************************************/
		 
		// process detected player movement
		scroll = 0;
		if(moved)
		{
			movePlayer(playerPointer, mapyoffset);
			
			// map scrolling 
			if(mapyoffset > 0)
			{
				if(player.getY() < (SCREEN_H/2 - 10))
				{
					scroll = (SCREEN_H/2 - 10) - player.getY();
					player.setY(SCREEN_H/2 - 10);
					mapyoffset -= scroll;
				}
			}
			
			// keep from scrolling too high
			if(mapyoffset < 0)
				mapyoffset = 0;
			
			// keep from scrolling too low
			if(mapyoffset > BOTTOM)
				mapyoffset = BOTTOM;
		}
		
		// weapons fire
		if(reloadTimer > 0)
			reloadTimer--;
		
		else if(reloadTimer == 0)
		{
			if(key[KEY_SPACE])
			{
				fire(playerPointer, bulletsPointer);
				reloadTimer = RELOAD_TIME;
			}
		}
		
		
		
		
			
		/**************************************
		*
		* BULLET & ENEMY & POWERUP MOVEMENT & SCROLLING
		*
		*****************************************/ 
				
		// bullet movement
		bullets.updateBullets(scroll);
		
		// crawler movement
		moveCrawlers(crawlersPointer, scroll, mapyoffset);
		
		// centipede movement
		moveCentipedes(centipedesPointer, scroll, mapyoffset);
		
		// boss movement
		moveBosses(bossesPointer, playerPointer, scroll, mapyoffset);
		
		// powerups
		movePowerups(powerupsPointer, scroll);
			

		/**************************************
		* 
		* SPAWN POINTS
		*
		**************************************/
		
		// spawn some crawlers near beginning
		if(!spawnpoint01 && (mapyoffset <= BOTTOM - 50))
		{
			for(i=0; i<10; i++)
				spawnCrawler(crawlersPointer, this->config->getOption("crawlerSprite"), playerPointer);
			
			spawnFlame(powerupsPointer, mapyoffset);
			spawnBazooka(powerupsPointer, mapyoffset);
			
			spawnpoint01 = true;
		}
		
		// spawn some centipedes soon after
		else if(!spawnpoint02 && (mapyoffset <= BOTTOM - 150))
		{
			for(i=0; i<10; i++)
				spawnCrawler(crawlersPointer, this->config->getOption("crawlerSprite"), playerPointer);
			
			for(i=0; i<3; i++)
				spawnCentipede(centipedesPointer, this->config->getOption("centipedeSprite"), playerPointer);
			
			spawnpoint02 = true;
		}
		
		// spawn a swarm of crawlers
		else if(!spawnpoint03 && (mapyoffset <= 5 * BOTTOM / 6))
		{
			for(i=0; i<20; i++)
				spawnCrawler(crawlersPointer, this->config->getOption("crawlerSprite"), playerPointer);
			
			spawnpoint03 = true;
		}
		
		// spawn a swarm of crawlers
		else if(!spawnpoint04 && (mapyoffset <= 4 * BOTTOM / 6))
		{
			for(i=0; i<20; i++)
				spawnCrawler(crawlersPointer, this->config->getOption("crawlerSprite"), playerPointer);
			
			for(i=0; i<3; i++)
				spawnCentipede(centipedesPointer, this->config->getOption("centipedeSprite"), playerPointer);
			
			spawnpoint04 = true;
		}
		
		else if(!spawnpoint05 && (mapyoffset <= 3 * BOTTOM / 6))
		{
			for(i=0; i<20; i++)
				spawnCrawler(crawlersPointer, this->config->getOption("crawlerSprite"), playerPointer);
			
			for(i=0; i<6; i++)
				spawnCentipede(centipedesPointer, this->config->getOption("centipedeSprite"), playerPointer);
			
			spawnpoint05 = true;
		}
		
		else if(!spawnpoint06 && (mapyoffset <= 2 * BOTTOM / 6))
		{
			for(i=0; i<10; i++)
				spawnCrawler(crawlersPointer, this->config->getOption("crawlerSprite"), playerPointer);
			
			for(i=0; i<3; i++)
				spawnCentipede(centipedesPointer, this->config->getOption("centipedeSprite"), playerPointer);
			
			spawnpoint06 = true;
		}
		
		else if(!bossspawnpoint && (mapyoffset < 10))
		{
			spawnBoss(bossesPointer, this->config->getOption("bossSprite"), playerPointer);
			bossspawnpoint = true;
		}
		
		else if(bossspawnpoint)
		{
			if(bossTimer > 0)
				bossTimer--;
			
			else if(bossTimer == 0)
			{
				for(i=0; i<10; i++)
					spawnCrawler(crawlersPointer, this->config->getOption("crawlerSprite"), playerPointer);
				
				spawnCentipede(centipedesPointer, this->config->getOption("centipedeSprite"), playerPointer);
				
				bossTimer = BOSS_TIME;
			}
		}
			
		/******************************************
		*
		* BULLET COLLISIONS AND RESOLUTION
		*
		******************************************/
		
		resolveBulletCollisions(bulletsPointer, maxBullets,
			crawlersPointer, centipedesPointer, bossesPointer,
			powerupsPointer, mapyoffset);
		
		
		/****************************************
		* 
		* ENEMY COLLISION & PLAYER HEALTH
		*
		***************************************/
		
		resolveEnemyCollision(playerPointer, playerHurtSound, crawlersPointer,
			centipedesPointer, bossesPointer);
		
		/************************************
		*
		* POWERUPS
		*
		**************************************/
		
		resolvePowerupCollision(playerPointer, powerupsPointer);
		
		
		/****************************************
		 *
		 * DRAW EVERYTHING
		 *
		 ****************************************/
		 
		 // draw background tiles of map
		MapDrawBG(buffer, 0, mapyoffset, 0, 0, SCREEN_W, SCREEN_H);
		
		// draw foreground tiles of map
		MapDrawFG(buffer, 0, mapyoffset, 0, 0, SCREEN_W, SCREEN_H, 0);
		
		// draw all the sprites
		drawSprites(buffer, playerPointer, bulletsPointer, powerupsPointer,
			crawlersPointer, centipedesPointer, bossesPointer);
		
		// draw health & ammo gauges
		drawGauges(buffer, gauge, healthIcon, flameIcon,
			bazookaIcon, playerPointer);

		/*
		// print some stats
		textprintf_ex(buffer, font, 0, 10, WHITE, -1,
			"Player Health: %d, x,y: %d,%d isAlive %d",
			player.getHealth(), player.getX(), player.getY(), player.isAlive());
		textprintf_ex(buffer, font, 0, 20, WHITE, -1,
			"Grace Timer: %d", player.getGraceTime());
		textprintf_ex(buffer, font, 0, 30, WHITE, -1,
			"Flame: %d, Bazooka: %d", player.getFlameAmmo(), player.getBazookaAmmo());
			*/
		
		// blit buffer to screen
		render(buffer);
		
		// if the boss is dead, set the player won flag
		if(!bosses.empty())
			playerWon = (bosses.at(0)->getHealth() < 1);
		
		// if the player is dead, set flag
		playerDead = (player.getHealth() < 1);
		
	} // END ESC KEY GAME LOOP

	// cleanup
	if(crawlers.size() > 0)
		for(i=0; i<crawlers.size(); i++)
			delete crawlers.at(i);
	
	if(centipedes.size() > 0)
		for(i=0; i<centipedes.size(); i++)
			delete centipedes.at(i);
	
	if(bosses.size() > 0)
		delete bosses.at(0);

	
	
	// destroy icon bitmaps
	destroy_bitmap(buffer);
	destroy_bitmap(gauge);
	destroy_bitmap(healthIcon); 
	destroy_bitmap(flameIcon);
	destroy_bitmap(bazookaIcon);
	
	// destroy game screen cards
	destroy_bitmap(titleScreen); 
	destroy_bitmap(intro01Screen);
	destroy_bitmap(intro02Screen);
	destroy_bitmap(helpScreen);
	destroy_bitmap(winScreen);
	destroy_bitmap(loseScreen);
	
	// destroy soundtrack sample
	destroy_sample(soundtrack);
	destroy_sample(playerHurtSound);
	MapFreeMem();
}

// Has the player requested to quit the game?
bool AlienBlaster::isPlayerQuitGame() {
  return allegro.keyESC();
}
	
	
	
