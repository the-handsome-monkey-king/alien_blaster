/*
*   allegrolayer.cpp
*
*   @author Ryan Morehouse
*   @date June 3, 2021
*
*/

#include "allegrolayer.h"

AllegroLayer::AllegroLayer(Config *config, const int screen_width, const int screen_height) {
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
}

AllegroLayer::~AllegroLayer() {
  // shutdown allegro
  remove_sound();
  allegro_exit();
}
