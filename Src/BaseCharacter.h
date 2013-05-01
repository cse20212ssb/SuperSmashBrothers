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
		virtual int getID() {return 2;}
		virtual void drawTo(SDL_Surface *){}

		virtual void move();
		void jump();
		//If possible to jump
		int jumpable();
		void fastFall();
		
		virtual void Atk() {}
		virtual void releaseAtk() {}
		virtual void upAtk(){}
		virtual void downAtk() {}
		virtual void specialAtk() {}
		virtual void releaseSpecialAtk() {}
		vector<Entity*> getProjectileList() {return projectileList;}
		vector<Entity*> getMeleeList() {return meleeList;}

		void removeProj(int);
		void removeMelee(int);
		void offScreen();
		virtual void recoil(){};

	protected:
		//Keeps track of jumps (max of two)
		int jumpCount;
		vector<Entity*> projectileList;
		vector<Entity*> meleeList;
		int isJump;
		int isFastFall;
		int isAtk;
		int isSpecial;
		int isSpecDown;
		int isGhost;
};

#endif
