/*
   allegrospriteimage.cpp

   @author Ryan Morehouse
   @date June 8, 2021

*/

#include "allegrospriteimage.h"

BITMAP* AllegroSpriteImage::grabFrame(
    BITMAP *source, int width, int height, 
    int startx, int starty, int columns, int frame) {

  BITMAP *temp = create_bitmap(width, height);
  int x = startx + (frame % columns) * width;
  int y = starty + (frame / columns) * width;
  blit(source, temp, x, y, 0, 0, width, height);
  return temp;
}

AllegroSpriteImage::AllegroSpriteImage() {}

AllegroSpriteImage::AllegroSpriteImage(std::string url) {
  BITMAP *b = load_bitmap(url.c_str(), NULL);
  images.push_back(b);
}

AllegroSpriteImage::AllegroSpriteImage(std::string url, 
    int width, int height, int startx, int starty, int columns, int
    total_frames) {

  BITMAP *source = load_bitmap(url.c_str(), NULL);

  for(int i = 0; i < total_frames; i++) {
    images.push_back(grabFrame(source, width, height,
          startx, starty, columns, i));
  }
}

AllegroSpriteImage::~AllegroSpriteImage() {
  for(unsigned int i = 0; i < images.size(); i++) {
    destroy_bitmap(images[i]);
  }
}
