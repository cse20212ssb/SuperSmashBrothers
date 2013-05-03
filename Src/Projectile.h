/* Projectile class

This is the projectile class, which is registered through pressing the B button. Each character has unique
projectiles: Megaman has a buster shot, Big Smoke has a bullet, and Leprechaun has a football. The projectile
begins with a velocity and will be deleted once it leaves the screen or collides with an object.

*/

#ifndef PROJECTILE_H
#define PROJECTILE_H

//#include "stdafx.h"
//#include "SDL.h"
#include <SDL/SDL.h>
#include "Entity.h"

using namespace std;

class Projectile : public Entity{
	public:
		Projectile() {} //Constructor
		Projectile(int, int, int, int, int, int, int, SDL_Surface *); //Non-default constructor

		virtual void onCollision(Entity *); //Defines collision behavior
		virtual int getID() {return ID;} //Returns the type of projectile
		virtual void move(); //Moves the projectile by adding velocity
		
		virtual void drawTo(SDL_Surface *); //Renders the projectile on the screen
	private:
		//Projectile IDS
		//Megaman: 0
		//Big Smoke: 1
		//Leprechaun: 2
		int ID;
		int type;

};

#endif
