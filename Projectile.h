#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "stdafx.h"
#include "SDL.h"
#include "Entity.h"

class Projectile : public Entity{
	public:
		Projectile() {}
		Projectile(int, int, int, int, int, int);

		virtual void onCollision(Entity *);
		virtual int getID() {return 3;}
		virtual void move();
		
		virtual void drawTo(SDL_Surface *);
};

#endif