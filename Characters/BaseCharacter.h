#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include <SDL/SDL.h>
#include "Entity.h"
//#include "stdafx.h"
//#include "SDL.h"
//#include "string"

using namespace std;

class BaseCharacter : public Entity{
	public:
		BaseCharacter(int, int, int, int);
		virtual SDL_Surface *getSprite();

		virtual void setMoveDir(int);

		virtual void drawTo(SDL_Surface *);

		virtual void move();
		virtual void jump();
		
		virtual void leftAtk();
		virtual void rightAtk();
		virtual void upAtk();
		virtual void downAtk();
		virtual void specialAtk();
	
	protected:
		//Keeps track of the animation
		double aniCounter;
};

#endif

