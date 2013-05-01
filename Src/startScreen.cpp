#include "SDL.h"
#include "stdafx.h"
#include "startScreen.h"

using namespace std;

void startScreen::draw() {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 400;
	src.h = 550;

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = 0;
	dst.h = 0;

	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);
	SDL_Flip(screen);
}

startScreen::startScreen(SDL_Surface *surf) {
	map = SDL_LoadBMP("Images/Misc/mainscreen2.bmp");

	screen = surf;

	sel = -1;
}
