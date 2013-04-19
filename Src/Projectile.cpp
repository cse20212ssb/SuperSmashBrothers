#include "stdafx.h"
#include "Projectile.h"
#include <iostream>

using namespace std;

Projectile::Projectile(int x,int y, int h, int w, int t_vel, int t_type) : Entity (x, y, h, w) {
	velX = t_vel;
	type = t_type;
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Projectiles.bmp");
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
	//How to deal with collisions with the player
	if (obj->getID() == 2) {
		//If bottom border is in a certain range of the platform
		if ((posX > obj->getLeft() && posX < obj->getRight()) && (posY < obj->getBot() && posY > obj->getTop())) {
			cout << "posX: " << posX << " obj left: " << obj->getLeft() << " obj Right: " << obj->getRight() <<endl;
			cout << "posY: " << posY << " obj bot: " << obj->getBot() << " obj Top: " << obj->getTop() <<endl;
			isGone = 1;		
			cout << "onCollision isGone is " << isGone << endl;
		}
	}
	if (obj->getID() == 3) {
		//If bottom border is in a certain range of the platform
		if ((posX > obj->getLeft() && posX < obj->getRight()) && (posY < obj->getBot() && posY > obj->getTop())) {
			cout << "posX: " << posX << " obj left: " << obj->getLeft() << " obj Right: " << obj->getRight() <<endl;
			cout << "posY: " << posY << " obj bot: " << obj->getBot() << " obj Top: " << obj->getTop() <<endl;
			isGone = 1;		
			cout << "onCollision isGone is " << isGone << endl;
		}
	}
}

void Projectile::move() {
	posX += velX;
}

//Make sure to clear/free the projectiles
