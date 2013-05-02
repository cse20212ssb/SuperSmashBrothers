#ifndef Firebat_H
#define Firebat_H

#include "SDL.h"
#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class Firebat : public BaseCharacter{
	public:
		Firebat() {}
		Firebat(int x, int y);;
		virtual void move();
		
		virtual void Atk();
		virtual void releaseAtk();

		virtual void specialAtk();
		virtual void releaseSpecialAtk();
		virtual void drawTo(SDL_Surface *);

	private:
		SDL_Surface *stimSprite;

	
};

#endif

