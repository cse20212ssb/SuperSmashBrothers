#include "stdafx.h"
#include "Melee.h"
#include "Entity.h"
#include "BaseCharacter.h"
#include <iostream>

using namespace std;

Melee::Melee(int x,int y, int h, int w, int t_type, int dir) : Entity (x, y, h, w) {
	faceDir = dir;
	type = t_type;
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Sword.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
	meleeGone = 0;
	meleeCounter = 0;
}

void Melee::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	if(faceDir == 1)
		src.x = 0;
	else
		src.x = width;

	src.y = 0;
	src.h = height/2;
	src.w = width;

	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.h = 0;
	dst.w = 0;

	meleeCounter++;
	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}

void Melee::onCollision(Entity *obj){
	//How to deal with collisions with the player
	if (obj->getID() == 2) {
		//If collides, cause recoil
		if(faceDir == 1)
			obj->rightRecoil();
		else
			obj->leftRecoil();
	}
}


