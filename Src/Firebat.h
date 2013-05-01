#ifndef Firebat_H
#define Firebat_H

//#include "SDL.h"
//#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class Firebat : public BaseCharacter{
	public:
		Firebat() {}
		Firebat(int x, int y);

		//Behavior on collision
		virtual void onCollision(Entity *);
		virtual void move();
		virtual int getID() {return 2;}
		
		virtual void Atk();
		virtual void releaseAtk();
		virtual void upAtk() {}
		virtual void downAtk() {}

		virtual void specialAtk();
		virtual void releaseSpecialAtk();
		virtual void drawTo(SDL_Surface *);

	
};

#endif

