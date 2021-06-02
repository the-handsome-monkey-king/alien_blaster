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
	
	// soundtrack midi
	string soundtrackFile = "";
	
	// player sprite
	string playerSprite;
	
	// player hurt sound
	string playerHurtSound;
	
	// enemy sprite images
	string bossSprite, centipedeSprite, crawlerSprite;
	
	// weapon sprite images and sounds
	string laser00, laser01, laser02, laser03, laser04, laser05, laser06, laser07;
	string flame00, flame01, flame02, flame03, flame04, flame05, flame06, flame07;
	string bazooka00, bazooka01, bazooka02, bazooka03, bazooka04, bazooka05, bazooka06, bazooka07;
	string laserSoundFile, flameSoundFile, bazookaSoundFile, impactSoundFile;
	
	// powerup images and sounds
	string healthFile, flameAmmoFile, bazookaAmmoFile;
	string powerupSoundFile;
	
	// mappy level map
	string mapFile;
	
	// load configuration file (Config class)
  Config config(config_url);

  // load configuation file (legacy)
	ifstream configFile("config.txt");
	
	// parse each configuration setting
	if(configFile.is_open()) {
		for(string text; getline(configFile, text); ) {
			
			int position = text.find(" = ");
      std::string name = text.substr(0, position);
      std::string value = text.substr(position+3);
			
			
			if(name == "centipedeSprite")
				centipedeSprite = value;
			
			else if(name == "crawlerSprite")
				crawlerSprite = value;
			
			else if(name == "healthPowerup")
				healthFile = value;
			
			else if(name == "flameAmmoFile")
				flameAmmoFile = value;
			
			else if(name == "bazookaAmmoFile")
				bazookaAmmoFile = value;
			
			else if(name == "powerupSoundFile")
				powerupSoundFile = value;
			
		}
	}
	
	// pack the powerups config settings in a vector
	vector<string> powerups;
	powerups.push_back(healthFile);
	powerups.push_back(flameAmmoFile);
	powerups.push_back(bazookaAmmoFile);
	powerups.push_back(powerupSoundFile);
	vector<string> *powerupsPointer = &powerups;
	
	AlienBlaster game = AlienBlaster(&config);
	
	game.runWrapper(crawlerSprite, centipedeSprite, powerupsPointer);

	return 0;
}
END_OF_MAIN()
