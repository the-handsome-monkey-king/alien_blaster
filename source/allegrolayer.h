/*
*   allegrolayer.h
*
*   @author Ryan Morehouse
*   @date June 3, 2021
*
*   @purpose A class to encapsulate the Allegro library.
*
*/

#ifndef ALLEGROLAYER_H
#define ALLEGROLAYER_H

#include <allegro.h>
#include "config.h"

class AllegroLayer {
  public:
    AllegroLayer(Config *config, const int screen_width, const int screen_height);
    ~AllegroLayer();

};

#endif
