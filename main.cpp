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
#include "alienblaster.h"


// window settings
#define WIDTH 640
#define HEIGHT 480
#define WINDOW GFX_AUTODETECT_WINDOWED
#define FULL GFX_AUTODETECT_FULLSCREEN

// some colours
#define WHITE makecol(255,255,255)

int main() {
	
	
	/****************************************
	*
	* INITIALIZE ALLEGRO & CONFIG SETTINGS
	*
	***************************************/
	allegro_init();

	// game config settings
	int fullscreenMode = 0;
	
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
	
	// load configuration file
	ifstream configFile("config.txt");
	
	// parse each configuration setting
	if(configFile.is_open()) {
		for(string text; getline(configFile, text); ) {
			
			int position = text.find(" = ");
			string name = text.substr(0, position);
			string value = text.substr(position+3);
			
			
			// process each config setting
			if(name == "fullscreen")
				fullscreenMode = atoi(value.c_str());
			
			else if(name == "soundtrackFile")
				soundtrackFile = value;
			
			else if(name == "playerSprite")
				playerSprite = value;
			
			else if(name == "playerHurtSound")
				playerHurtSound = value;
			
			else if(name == "laser00")
				laser00 = value;
			
			else if(name == "laser01")
				laser01 = value;
			
			else if(name == "laser02")
				laser02 = value;
			
			else if(name == "laser03")
				laser03 = value;
			
			else if(name == "laser04")
				laser04 = value;
			
			else if(name == "laser05")
				laser05 = value;
			
			else if(name == "laser06")
				laser06 = value;
			
			else if(name == "laser07")
				laser07 = value;
			
			else if(name == "flame00")
				flame00 = value;
			
			else if(name == "flame01")
				flame01 = value;
			
			else if(name == "flame02")
				flame02 = value;
			
			else if(name == "flame03")
				flame03 = value;
			
			else if(name == "flame04")
				flame04 = value;
			
			else if(name == "flame05")
				flame05 = value;
			
			else if(name == "flame06")
				flame06 = value;
			
			else if(name == "flame07")
				flame07 = value;
			
			else if(name == "bazooka00")
				bazooka00 = value;
			
			else if(name == "bazooka01")
				bazooka01 = value;
			
			else if(name == "bazooka02")
				bazooka02 = value;
			
			else if(name == "bazooka03")
				bazooka03 = value;
			
			else if(name == "bazooka04")
				bazooka04 = value;
			
			else if(name == "bazooka05")
				bazooka05 = value;
			
			else if(name == "bazooka06")
				bazooka06 = value;
			
			else if(name == "bazooka07")
				bazooka07 = value;
			
			else if(name == "laserSoundFile")
				laserSoundFile = value;
			
			else if(name == "flameSoundFile")
				flameSoundFile = value;
			
			else if(name == "bazookaSoundFile")
				bazookaSoundFile = value;
			
			else if(name == "impactSoundFile")
				impactSoundFile = value;
			
			else if(name == "bossSprite")
				bossSprite = value;
			
			else if(name == "centipedeSprite")
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
			
			else if(name == "map")
				mapFile = value;
			
			

		}
	}
	
	// pack the bullethandler config settings in a vector
	vector<string> bulletsConfig;
	bulletsConfig.push_back(laser00);
	bulletsConfig.push_back(laser01);
	bulletsConfig.push_back(laser02);
	bulletsConfig.push_back(laser03);
	bulletsConfig.push_back(laser04);
	bulletsConfig.push_back(laser05);
	bulletsConfig.push_back(laser06);
	bulletsConfig.push_back(laser07);
	bulletsConfig.push_back(flame00);
	bulletsConfig.push_back(flame01);
	bulletsConfig.push_back(flame02);
	bulletsConfig.push_back(flame03);
	bulletsConfig.push_back(flame04);
	bulletsConfig.push_back(flame05);
	bulletsConfig.push_back(flame06);
	bulletsConfig.push_back(flame07);
	bulletsConfig.push_back(bazooka00);
	bulletsConfig.push_back(bazooka01);
	bulletsConfig.push_back(bazooka02);
	bulletsConfig.push_back(bazooka03);
	bulletsConfig.push_back(bazooka04);
	bulletsConfig.push_back(bazooka05);
	bulletsConfig.push_back(bazooka06);
	bulletsConfig.push_back(bazooka07);
	bulletsConfig.push_back(laserSoundFile);
	bulletsConfig.push_back(flameSoundFile);
	bulletsConfig.push_back(bazookaSoundFile);
	bulletsConfig.push_back(impactSoundFile);
	vector<string> *bulletsPointer = &bulletsConfig;
	
	// pack the powerups config settings in a vector
	vector<string> powerups;
	powerups.push_back(healthFile);
	powerups.push_back(flameAmmoFile);
	powerups.push_back(bazookaAmmoFile);
	powerups.push_back(powerupSoundFile);
	vector<string> *powerupsPointer = &powerups;
	
	
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
	
	// ensure a whole new game instance is run each time
	while(!key[KEY_ESC]) 
	{
		run(mapFile, playerSprite, playerHurtSound, crawlerSprite, centipedeSprite, bossSprite,
			bulletsPointer, powerupsPointer, soundtrackFile);
	}
	
	// shutdown allegro
	remove_sound();
	allegro_exit();
	return 0;
}
END_OF_MAIN()
