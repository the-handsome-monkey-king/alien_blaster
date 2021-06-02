/*
 * main.cpp
 *
 * @author Ryan Morehouse
 * @date May 28, 2018
 *
 * @purpose A primary execution point for the game Alien Blaster. This
 * program will initialize allegro and instantiate the game class, which
 * encapsulates the rest of the game code.
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) main.o: sprite.o playersprite.o bulletsprite.o bullethandler.o crawlersprite.o centipede.o mappyal.o boss.o powerup.o alienblaster.o grabframe.o poweruphandler.o

 */
 
#include <allegro.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "config.h"
#include "alienblaster.h"


// window settings
#define WIDTH 640
#define HEIGHT 480
#define WINDOW GFX_AUTODETECT_WINDOWED
#define FULL GFX_AUTODETECT_FULLSCREEN

// some colours
#define WHITE makecol(255,255,255)

// config file location
std::string const config_url = "config.txt";


int main() {
	
	
	/****************************************
	*
	* INITIALIZE ALLEGRO & CONFIG SETTINGS
	*
	***************************************/
	
	// load configuration file (Config class)
  Config config(config_url);

	AlienBlaster game = AlienBlaster(&config);
	
	game.runWrapper();

	return 0;
}
END_OF_MAIN()
