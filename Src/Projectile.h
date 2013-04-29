#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "stdafx.h"
#include "SDL.h"
//#include <SDL/SDL.h>
#include "Entity.h"

using namespace std;

class Projectile : public Entity{
	public:
		Projectile() {}
		Projectile(int, int, int, int, int, int);

		virtual void onCollision(Entity *);
		virtual int getID() {return 4;}
		virtual void move();
		
		virtual void drawTo(SDL_Surface *);
	private:
		int type;

};

#endif
