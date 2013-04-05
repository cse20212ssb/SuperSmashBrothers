#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "SDL.h"
#include "stdafx.h"
//#include <SDL/SDL.h>
#include "Entity.h"
#include <vector>

using namespace std;

class BaseCharacter : public Entity{
	public:
		BaseCharacter() {}
		BaseCharacter(int, int, int, int);

		//Behavior on collision
		virtual void onCollision(Entity *) {}
		virtual int getID() {return 1;}

		void setMoveDir(int);

		virtual void drawTo(SDL_Surface *);

		virtual void move();
		void jump();
		//If possible to jump
		int jumpable();
		//If it can jump
		void setCanJump(int n) {canJump = n;}
		void fastFallCrouch();
		
		virtual void leftAtk() {}
		virtual void rightAtk() {}
		virtual void upAtk(){}
		virtual void downAtk() {}
		virtual void specialAtk() {}
	
	protected:
		//Keeps track of the animation
		double aniCounter;
		//Keeps track of jumps (max of two)
		int jumpCount;
		int canJump;
		vector<Entity*> projectileList;
};

#endif
