/* Platform class

This is the platform class, which is used to create platforms for the program. It derives from the entity
class and utilizes a few simple functions from entity to draw the platforms and determine if an object
collided with the platform. Since platforms don't move, they don't shift during collisions.

*/

#ifndef PLATFORM_H
#define PLATFORM_H

//#include "stdafx.h"
//#include "SDL.h"
#include <SDL/SDL.h>
#include "Entity.h"

using namespace std;

class Platform : public Entity {
	public:
		Platform(){} //Constructor
		virtual ~Platform() {} //Destructor
		Platform(int, int, int, int); //Non-default constructor
	
		//No behavior on collision
		virtual void onCollision(Entity *) {}
		virtual int getID() {return 1;}
		
		virtual void drawTo(SDL_Surface *) {}
};
					
#endif
