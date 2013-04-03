#ifndef BASECHARACTER_H
#define BASECHARACTER_H

//#include "SDL.h"
//#include "stdafx.h"
#include <SDL/SDL.h>
#include "../Entity.h"

using namespace std;

class BaseCharacter : public Entity{
	public:
		BaseCharacter() {}
		BaseCharacter(int, int, int, int);

		virtual void onCollision(Entity *) {}
		virtual int getID() {return 1;}

		void setMoveDir(int);

		virtual void drawTo(SDL_Surface *);

		void move();
		void jump();
		int jumpable() {return canJump;}
		
		virtual void leftAtk() {}
		virtual void rightAtk() {}
		virtual void upAtk(){}
		virtual void downAtk() {}
		virtual void specialAtk() {}
	
	protected:
		//Keeps track of the animation
		double aniCounter;
		//If in air == 1
		int canJump;
};

#endif
