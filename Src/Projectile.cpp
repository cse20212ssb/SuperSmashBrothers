#include "stdafx.h"
#include "Projectile.h"
#include <iostream>

using namespace std;

Projectile::Projectile(int x,int y, int h, int w, int t_vel, int t_faceDir, int t_type, SDL_Surface *t_sprite) : Entity (x, y, h, w) {
	velX = t_vel;
	type = t_type;
	faceDir = t_faceDir;
	if (type == 0) //Normal Projectiles
		ID = 5;
	else if (type == 1) //SpecDown Projectiles
		ID = 6;

	sprite  = t_sprite;
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
	isGone = 0;
}

void Projectile::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	if (faceDir == 1)
		src.x = 0;
	else
		src.x = width;
	src.y = type * height;

	src.h = height;
	src.w = width;

	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.h = 0;
	dst.w = 0;

	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}

void Projectile::onCollision(Entity *obj){
	isGone = 1;
}

void Projectile::move() {
	if (type == 0)
		posX += velX;
	else if (type == 1 || type == 2) {
		posX += velX;
		velX *= .9;
		if (velX < .3 && velX > 0) isGone = 1;
		if (velX > -.3 && velX < 0) isGone = 1;
	}
	else if (type == 3 || type == 4) {
		posX += velX;
		velX *= .7;
		if (velX < .3 && velX > 0) isGone = 1;
		if (velX > -.3 && velX < 0) isGone = 1;
	}
}
