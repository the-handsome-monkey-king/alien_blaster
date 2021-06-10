/*
*   allegrolayer.cpp
*
*   @author Ryan Morehouse
*   @date June 3, 2021
*
*/

#include "allegrolayer.h"

AllegroLayer::AllegroLayer() {}

AllegroLayer::AllegroLayer(Config *config, const int screen_width, const int screen_height) {
  /*
  // initalize allegro
  allegro_init();

  // get fullscreen config, defaults to 0
  int fullscreenMode = atoi(config->getOption("fullscreen").c_str());

  // configure graphics
  set_color_depth(16);
  if(fullscreenMode == 1) {
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screen_width, screen_height, 0, 0);
  } else {
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, screen_width, screen_height, 0, 0);
  }

  // configure music mode required drivers
  // default without midi
  if(install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0) {
    allegro_message("%s", "Error initializing the sound system.");
    exit(1);
  }

  // controllers and timers
  install_keyboard();
  install_timer();
  srand(time(NULL));
  */
}

AllegroLayer::~AllegroLayer() {
  // shutdown allegro
  remove_sound();
  allegro_exit();
}

// controls
bool AllegroLayer::keyESC() {
  if (key[KEY_ESC]) return true;
  return false;
}

bool AllegroLayer::keyUp() {
  if (key[KEY_UP]) return true;
  return false;
}

bool AllegroLayer::keyDown() {
  if (key[KEY_DOWN]) return true;
  return false;
}

bool AllegroLayer::keyLeft() {
  if (key[KEY_LEFT]) return true;
  return false;
}

bool AllegroLayer::keyRight() {
  if (key[KEY_RIGHT]) return true;
  return false;
}

bool AllegroLayer::keySpace() {
  if (key[KEY_SPACE]) return true;
  return false;
}


bool AllegroLayer::keyEnter(){
  if (key[KEY_ENTER]) return true;
  return false;
}

bool AllegroLayer::keyOne(){
  if (key[KEY_1]) return true;
  return false;
}

bool AllegroLayer::keyTwo(){
  if (key[KEY_2]) return true;
  return false;
}

bool AllegroLayer::keyThree(){
  if (key[KEY_3]) return true;
  return false;
}

bool AllegroLayer::keyControl() {
  return (key[KEY_LCONTROL] || key[KEY_RCONTROL]);
}

bool AllegroLayer::keyM(){
  if (key[KEY_M]) return true;
  return false;
}

bool AllegroLayer::keyP(){
  if (key[KEY_P]) return true;
  return false;
}

bool AllegroLayer::keyH(){
  if (key[KEY_H]) return true;
  return false;
}



/*************************

  SPRITE IMAGES

**************************/
BITMAP* AllegroLayer::grabframe(
    BITMAP *source, int width, int height, 
    int startx, int starty, int columns, int frame)
{
	BITMAP *temp = create_bitmap(width, height);
	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;
	blit(source, temp, x, y, 0, 0, width, height);
	return temp;
}

void AllegroLayer::registerSpriteImage(
    std::string name, std::string image_file)
{
  BITMAP *bm = load_bitmap(image_file.c_str(), NULL);
  std::vector<BITMAP*> v;
  v.push_back(bm);
  sprite_images[name] = v;
}

void AllegroLayer::registerSpriteSheet(
    std::string name, std::string image_file,
    int width, int height, int startx, int starty,
    int columns, int total_frames)
{
  std::vector<BITMAP*> v;

  BITMAP *sheet = load_bitmap(image_file.c_str(), NULL);
  for(int i = 0; i < total_frames; i++) {
    v.push_back(grabframe(sheet, width, height, startx, starty, columns, i));
  }

  sprite_images[name] = v;
}
