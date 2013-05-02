#ifndef LEPRECHAUN_H
#define LEPRECHAUN_H

#include "SDL.h"
#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class Leprechaun : public BaseCharacter{
	public:
		Leprechaun() {}
		Leprechaun(int x, int y);

		//Behavior on collision
		virtual void onCollision(Entity *);
		virtual void drawTo(SDL_Surface *);
		virtual void move();
		
		virtual void Atk();
		virtual void releaseAtk();

		virtual void specialAtk();
		virtual void releaseSpecialAtk();
	private:
		void createSpecialAtk();
		int isThrow;

	
};

#endif
