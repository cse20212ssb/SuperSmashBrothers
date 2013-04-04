#ifndef PLATFORM_H
#define PLATFORM_H

//#include "stdafx.h"
//#include "SDL.h"
#include "Entity.h"
#include <SDL/SDL.h>

using namespace std;

class Platform : public Entity {
	public:
		Platform() {}
		Platform(int, int, int, int, int);

		virtual void onCollision(Entity *) {}
		virtual int getID() {return 3;}
		
		virtual void drawTo(SDL_Surface *);
};
					
#endif
