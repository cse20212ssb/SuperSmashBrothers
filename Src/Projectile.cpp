#include "stdafx.h"
#include "Projectile.h"

using namespace std;

Projectile::Projectile(int x,int y, int h, int w, int t_vel, int t_type) : Entity (x, y, h, w) {
	velX = t_vel;
	type = t_type;
	sprite = SDL_LoadBMP("../Images/Sprites/Projectiles.bmp");

}

void Projectile::drawTo(SDL_Surface *surf) {
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

void Projectile::onCollision(Entity *obj){
}

void Projectile::move() {
	posX += velX;
}

//Make sure to clear/free the projectiles
