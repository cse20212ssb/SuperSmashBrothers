//#include "stdafx.h"
#include "Platform.h"

using namespace std;

Platform::Platform(int x,int y, int h, int w, int size) : Entity (x, y, h, w) {
	if (size == 0)
		sprite = SDL_LoadBMP("Images/Maps/platform_small.bmp");
	else if (size == 1)
		sprite = SDL_LoadBMP("Images/Maps/platform_big.bmp");
	SDL_SetColorKey(getSprite(),SDL_SRCCOLORKEY,SDL_MapRGB(getSprite()->format, 255, 0, 0));
}

void Platform::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	src.x = 0; 
	src.y = 0;
	src.h = height;
	src.w = width;

	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.h = 0;
	dst.w = 0;

	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}

