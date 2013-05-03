/* Leprechaun class
Taken from our beloved Notre Dame. The Leprechaun throws footballs of mass destruction that cause massive knockback. Because he's a real man, he don't need no melee weapon and punches people. In addition to that, he does not flinch, meaning he is impervious to knockbacks. This class, just as all the other character classes, derives from the BaseCharacter classes.
*/
#ifndef LEPRECHAUN_H
#define LEPRECHAUN_H

//#include "SDL.h"
//#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class Leprechaun : public BaseCharacter{
	public:
		//Constructor
		Leprechaun() {}
		Leprechaun(int x, int y);

		//Behavior on collision, that is, when he collides with the ground
		virtual void onCollision(Entity *);
		//Draw function redefined to account for football throwing animation
		virtual void drawTo(SDL_Surface *);
		//Movment
		virtual void move();
		
		//Attack functions
		virtual void Atk();
		virtual void releaseAtk();
		//Special functions
		virtual void specialAtk();
		virtual void releaseSpecialAtk();
	private:
		//Creates the football
		void createSpecialAtk();
		//Reflects if the football is being thrown or not
		int isThrow;

	
};

#endif
