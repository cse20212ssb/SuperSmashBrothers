#ifndef BIGSMOKE_H
#define BIGSMOKE_H

#include "SDL.h"
#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class BigSmoke : public BaseCharacter{
	public:
		BigSmoke() {}
		BigSmoke(int x, int y);

		//Behavior on collision
		virtual void onCollision(Entity *);
		virtual int getID() {return 2;}
		virtual void drawTo(SDL_Surface *);
		virtual void move();
		
		virtual void Atk();
		virtual void releaseAtk();

		virtual void specialAtk();
		virtual void releaseSpecialAtk();

	
};

#endif

