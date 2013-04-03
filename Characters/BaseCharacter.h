#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include <SDL/SDL.h>
#include "../Entity.h"
//#include "stdafx.h"
//#include "SDL.h"
//#include "string"

using namespace std;

class BaseCharacter : public Entity{
	public:
		BaseCharacter() {}
		BaseCharacter(int, int, int, int);
		SDL_Surface *getSprite();

		virtual void onCollision(Entity *) {}
		virtual int getID() {return 1;}

		void setMoveDir(int);

		virtual void drawTo(SDL_Surface *);

		void move();
		void jump();
		
		virtual void leftAtk() {}
		virtual void rightAtk() {}
		virtual void upAtk(){}
		virtual void downAtk() {}
		virtual void specialAtk() {}
	
	protected:
		//Keeps track of the animation
		double aniCounter;
		//If in air == 1
		int inAir;
};

#endif
