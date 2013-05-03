/* Melee class

This is the melee class, which is similar to the projectile class without initial movement. The melee
class features four IDs to create unique melee behavior and animations for each character. Megaman
has a character ID of 0, Big Smoke 1, Leprechaun 3, and Firebat 4. Melee have a specified hitbox
in front of the character for collision detection. When an object collides with melee, it will
recoil further than when it colides with a projectile

*/


#ifndef MELEE_H
#define MELEE_H

//#include "stdafx.h"
//#include "SDL.h"
#include <SDL/SDL.h>
#include "Entity.h"

using namespace std;

//Constructor
class Melee : public Entity{
	public:
		Melee();
		Melee(int, int, int, int, int, SDL_Surface *);

		virtual void onCollision(Entity *);
		virtual int getID() {return 2;}
		virtual void drawTo(SDL_Surface *);

	private:
		int counter;
};

#endif
