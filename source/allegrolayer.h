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
    // constructors
    AllegroLayer();
    AllegroLayer(Config *config, const int screen_width, const int screen_height);
    ~AllegroLayer();

    // controls
    bool keyESC();
    bool keyUp();
    bool keyDown();
    bool keyLeft();
    bool keyRight();
    bool keySpace();

};

#endif
