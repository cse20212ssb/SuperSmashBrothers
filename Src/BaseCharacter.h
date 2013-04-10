#ifndef BASECHARACTER_H
#define BASECHARACTER_H

//#include "SDL.h"
//#include "stdafx.h"
#include <SDL/SDL.h>
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
		
		virtual void drawTo(SDL_Surface *);

		virtual void move();
		void jump();
		//If possible to jump
		int jumpable();
		//If it can jump
		void setCanJump(int n) {canJump = n;}
		void fastFallCrouch();
		
		//virtual void animate(int);
		
		virtual void Atk();
		virtual void releaseAtk();
		virtual void upAtk(){}
		virtual void downAtk() {}
		virtual void specialAtk() {}
		virtual void releaseSpecialAtk();
		
		//virtual void setSprite(int) {}
		
		//void setDir(int n) {dir = n;}

	protected:
		//Keeps track of jumps (max of two)
		int dir;
		int jumpCount;
		int canJump;
		vector<Entity*> projectileList;
		//Determines the type of movement
		int moveType;
		int isDecrementing;
		int isJump;
		int isAtk;
		int isSpecial;
};

#endif
