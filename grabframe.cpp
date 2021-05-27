/*
 * grabframe.cpp
 *
 * @author Jonathan S. Harbour, from the book Game Programming All-in-One
 * @date May 1, 2018
 *
 * @purpose A function that grabs a sprite from a spritesheet. 
 *
 * *** Compile Instructions (Linux) ***
 * 1) make
 * - OR -
 * 1) g++ -c -o grabframe.o grabframe.cpp -lalleg -Wall
 */

#include <allegro.h>
#include "grabframe.h"

BITMAP *grabframe(BITMAP *source, int width, int height,
						int startx, int starty, int columns, int frame)
{
	BITMAP *temp = create_bitmap(width, height);
	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;
	blit(source, temp, x, y, 0, 0, width, height);
	return temp;
}

