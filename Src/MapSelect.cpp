//#include "SDL.h"
//#include "stdafx.h"
#include "MapSelect.h"

using namespace std;

void MapSelect::draw() {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 400;
	src.h = 550;

	SDL_Rect dst;
	dst.x = index * 400;
	dst.y = 0;
	dst.w = 0;
	dst.h = 0;

	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);
	SDL_BlitSurface(sprite, &src, screen, &dst); //Select Square
	SDL_Flip(screen);
}

MapSelect::MapSelect(SDL_Surface *surf) {
	map = SDL_LoadBMP("Images/Maps/MapSelect.bmp");
	sprite = SDL_LoadBMP("Images/Maps/Selection.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );

	screen = surf;

	sel = -1;
	index = 0;
}

MapSelect::~MapSelect() {
	SDL_FreeSurface(map);
	SDL_FreeSurface(sprite);
}
