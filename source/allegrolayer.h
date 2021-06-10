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
#include <map>
#include <string>
#include <vector>
#include "config.h"

class AllegroLayer {
  private:
    // library of BITMAP type sprite images
    std::map<std::string, std::vector<BITMAP*>> sprite_images;

    // this function was written by Jonathan S. Harbour, from the book
    // Game Programming All-in-One.
    BITMAP *grabframe(
        BITMAP *source, int width, int height, 
        int startx, int starty, int columns, int frame);

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
    bool keyEnter();
    bool keyOne();
    bool keyTwo();
    bool keyThree();
    bool keyControl();
    bool keyM();
    bool keyP();
    bool keyH();

    // sprite images
    void registerSpriteImage(std::string name, std::string image_file);
    void registerSpriteSheet(std::string name, std::string image_file,
        int width, int height, int startx, int starty,
        int columns, int frame);


};

#endif
