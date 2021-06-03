/*
 * alienblaster.h
 *
 * @author Ryan Morehouse
 * @date May 27, 2018
 * @version 1.0
 *
 * @purpose A class to encapsulate the main execution loop for Alien Blaster.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o alienblaster.o alienblaster.cpp -lalleg -Wall
 */
 
#ifndef ALIENBLASTER_H
#define ALIENBLASTER_H
 
#include <allegro.h>
#include <string>
#include "config.h"
#include "allegrolayer.h"
#include "sprite.h"
#include "bulletsprite.h"
#include "bullethandler.h"
#include "playersprite.h"
#include "crawlersprite.h"
#include "centipede.h"
#include "mappyal.h"
#include "boss.h"
#include "powerup.h"
#include "grabframe.h"
#include "poweruphandler.h"

// window settings
#define WIDTH 640
#define HEIGHT 480
#define WINDOW GFX_AUTODETECT_WINDOWED
#define FULL GFX_AUTODETECT_FULLSCREEN

using namespace std;

// some colors
#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)
#define RED makecol(255,0,0)

// life gauge constants
#define GAUGE_LENGTH 130
#define GAUGE_HEIGHT 14
#define GAUGE_BORDER 2

// a weapon timer
#define RELOAD_TIME 200

// boss movement constants
#define BOSS_X1 100
#define BOSS_Y1 150
#define BOSS_X2 320
#define BOSS_Y2 170
#define BOSS_X3 150
#define BOSS_Y3 300
#define BOSS_X4 400
#define BOSS_Y4 300
#define BOSS_TIME 3000


class AlienBlaster {
  private:
    Config *config;
    AllegroLayer allegro;
  public:
    AlienBlaster(Config *config);
    ~AlienBlaster();

    void runWrapper();
      
    void run();
};

/********************************************
*
* DISPLAY
*
********************************************/

// print a buffer to the screen
void render(BITMAP *buffer);

// load display buffer
void drawSprites(BITMAP *buffer, playersprite *player,
	bullethandler *bullets, poweruphandler *powerups,
	vector<crawlersprite*> *crawlers, 
	vector<centipede*> *centipedes, vector<boss*> *bosses);

void drawGauges(BITMAP *buffer, BITMAP *gauge, BITMAP *healthIcon,
	BITMAP *flameIcon, BITMAP *bazookaIcon,
	playersprite *player);

void displayScreenCard(BITMAP *titleScreen);

void displayInstructions(BITMAP *instructionsScreen);

void displayWin(BITMAP *winScreen);

void displayLose(BITMAP *loseScreen);

/********************************************
*
* MAP FOREGROUND COLLISION DETECTION
*
********************************************/

// test for any collision in a mappy level map
int mapCollision(int x, int y);

// test for collision given a sprite in a mappy level map
int spriteMapCollision(sprite* s, int yoffset);

/******************************************
*
* PLAYER MOVEMENT, MAP SCROLLING, FIRE WEAPONS 
*
*******************************************/

// returns true if player moved & handles weapons fire
bool playerInput(playersprite *player);

// processes player movement w/ map collision resolution
void movePlayer(playersprite *player, int mapyoffset);

// fire weapons
void fire(playersprite *player, bullethandler *bullets);

/******************************************
*
* ENEMIES SPAWNERS
*
*******************************************/

void spawnCrawler(vector<crawlersprite*> *crawlers,
	string crawlerFile, playersprite *player);

void spawnCentipede(vector<centipede*> *centipedes, 
	string centipedeFile, playersprite *player);

void spawnBoss(vector<boss*> *bosses,
	string bossFile, playersprite *player);

/****************************************
*
* ENEMY MOVEMENT & SPRITE SCROLLING
*
******************************************/

void moveCrawlers(vector<crawlersprite*> *crawlers,
	int scroll, int mapyoffset);

void moveCentipedes(vector<centipede*> *centipedes,
	int scroll, int mapyoffset);

void moveBosses(vector<boss*> *bosses,
	int scroll, int mapyoffset);

void movePowerups(poweruphandler *powerups, int scroll);

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
	poweruphandler *powerups, int mapyoffset);


/****************************************
* 
* ENEMY COLLISIONS & PLAYER HEALTH
*
***************************************/

void resolveEnemyCollision(playersprite *player, SAMPLE *hurtSound,
	vector<crawlersprite*> *crawlers,
	vector<centipede*> *centipedes,
	vector<boss*> *bosses);

/*****************************************
*
* POWERUPS COLLISION & RESOLUTION
*
******************************************/

void spawnHealth(poweruphandler *powerups, int mapyoffset);

void spawnFlame(poweruphandler *powerups, int mapyoffset);

void spawnBazooka(poweruphandler *powerups, int mapyoffset);

void spawnRandomPowerup(poweruphandler *powerups, int mapyoffset);

void resolvePowerupCollision(playersprite *player,
	vector<powerup*> *powerups);

#endif
