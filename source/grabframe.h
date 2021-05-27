/*
 * grabframe.h
 *
 * @author Jonathan S. Harbour, from the book Game Programming All-in-One
 * @date May 1, 2018
 *
 * @purpose A function that grabs a sprite from a spritesheet. 
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o grabframe.o grabframe.cpp
 */

#ifndef GRABFRAME_H
#define GRABFRAME_H

#include <allegro.h>

BITMAP *grabframe(BITMAP *source, int width, int height,
						int startx, int starty, int columns, int frame);

#endif
