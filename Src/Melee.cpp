#include "stdafx.h"
#include "Melee.h"
#include <iostream>

using namespace std;

Melee::Melee(int x,int y, int h, int w, int t_type, int dir) : Entity (x, y, h, w) {
	faceDir = dir;
	if(t_type == 0){
		sprite = SDL_LoadBMP("Images/Sprites/Megaman/Sword.bmp");
	}
	else if(t_type == 1){
		sprite = SDL_LoadBMP("Images/Sprites/BigSmoke/Bat.bmp");
	}
	else
		sprite = SDL_LoadBMP("Images/Sprites/Megaman/Sword.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
	isGone = 0;
	counter = 0;

}

void Melee::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	if(faceDir == 1)
		src.x = 0;
	else
		src.x = width;
	src.y = 0;
	src.h = height;
	src.w = width;

	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.h = 0;
	dst.w = 0;
	if (counter >= 20)
		isGone = 1;
	counter++;
	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}

void Melee::onCollision(Entity *obj){

}


