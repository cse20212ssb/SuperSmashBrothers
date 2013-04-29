#ifndef MEGAMAN_H
#define MEGAMAN_H

//#include "SDL.h"
//#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class Megaman : public BaseCharacter{
	public:
		Megaman() {}
		Megaman(int x, int y);

		//Behavior on collision
		virtual void onCollision(Entity *);
		virtual int getID() {return 2;}
		virtual void drawTo (SDL_Surface *);
		
		virtual void Atk();
		virtual void releaseAtk();

		virtual void aerialAtk();

		virtual void specialAtk();
		virtual void releaseSpecialAtk();


	
};

#endif

