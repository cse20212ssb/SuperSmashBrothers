/* Map Select class

This is the map select class and is used for the user to select between two maps.
It is similar to the character select class, but doesn't use a linked list because
there are only two entries. Instead an index is set to 1 or 0 to indicate the
selected map and the location of the cursor.

*/


//#include "SDL.h"
//#include "stdafx.h"
#include "MapSelect.h"
#include <iostream>

using namespace std;

//This function draws the mapSelect bmp onto the screen
void MapSelect::draw() {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 400;
	src.h = 550;

	SDL_Rect dst;
	dst.x = index * 400; //There are two maps and the screen is of width 800
	dst.y = 0;
	dst.w = 0;
	dst.h = 0;

	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);
	SDL_BlitSurface(sprite, &src, screen, &dst); //Select Square
	SDL_Flip(screen);
}

//This is the constructor and establishes all the sprites and references the bitmaps that will be drawn
MapSelect::MapSelect(SDL_Surface *surf) {
	map = SDL_LoadBMP("Images/Misc/MapSelect.bmp");
	sprite = SDL_LoadBMP("Images/Misc/MapSelBox.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );

	screen = surf;

	sel = -1;
	index = 0;
}

//The deconstructor
MapSelect::~MapSelect() {
	cout << "Closing MapSelect" << endl;
	SDL_FreeSurface(map);
	SDL_FreeSurface(sprite);
	cout << "Closed" << endl;
}

