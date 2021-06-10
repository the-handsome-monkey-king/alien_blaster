/*
   allegrospriteimage.h

   @author Ryan Morehouse
   @date June 9, 2021

   @purpose To encapsulate the BITMAP type used in allegro
   for sprite instances.

*/

#ifndef ALLEGROSPRITEIMAGE_H
#define ALLEGROSPRITEIMAGE_H

#include <allegro.h>
#include <vector>
#include <string>
#include <fstream>

class AllegroSpriteImage {
  private:
    std::vector<BITMAP*> images;

    // This method written by Jonathan S. Harbour, in his book
    // Game Programming All-in-One.
    // grabs a single sprite from spritesheet as a BITMAP*
    BITMAP* grabFrame(BITMAP *source, int width, int height,
        int startx, int starty, int columns, int frame);
  public:
    AllegroSpriteImage();

    // for a single-image sprite
    // url of sprite image
    AllegroSpriteImage(std::string url);

    // for a multi-image sprite using a sprite sheet
    // url of sprite image
    // width and height of individual sprite in pixels
    // beginning x and y coords in sprite sheet
    // # of columns in sprite sheet
    // how many frames in total
    AllegroSpriteImage(std::string url, int width, int height,
        int startx, int starty, int columns, int total_frames);
    ~AllegroSpriteImage();
};

#endif
