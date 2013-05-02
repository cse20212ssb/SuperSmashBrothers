#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "SDL.h"
#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"


class Megaman : public BaseCharacter{
	public:
		Megaman() {}
		Megaman(int x, int y);

		virtual void drawTo (SDL_Surface *);
		virtual void onCollision(Entity *);
		virtual void move();
		
		virtual void Atk();
		virtual void releaseAtk();

		virtual void aerialAtk();

		virtual void specialAtk();
		virtual void releaseSpecialAtk();
	private:
		void specialDown();

	
};

#endif

