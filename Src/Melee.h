#ifndef MELEE_H
#define MELEE_H

//#include "stdafx.h"
//#include "SDL.h"
#include <SDL/SDL.h>
#include "Entity.h"

using namespace std;

class Melee : public Entity{
	public:
		Melee();
		Melee(int, int, int, int, int, int);

		virtual void onCollision(Entity *);
		virtual int getID() {return 4;}
		virtual void drawTo(SDL_Surface *);

	private:
		int counter;
};

#endif
