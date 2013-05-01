#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "SDL.h"
#include "stdafx.h"
//#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"
#include "Jukebox.h"
#include <vector>

using namespace std;

class BaseCharacter : public Entity{
	public:
		BaseCharacter() {}
		BaseCharacter(int, int, int, int);
		virtual ~BaseCharacter();

		//Behavior on collision
		virtual void onCollision(Entity *) {}
		virtual int getID() {return 2;}
		virtual void drawTo(SDL_Surface *){}

		virtual void move() {}
		void jump();
		//If possible to jump
		int jumpable();
		void fastFall();
		
		virtual void Atk() {}
		virtual void releaseAtk() {}
		
		virtual void aerialAtk() {}

		virtual void specialAtk() {}
		virtual void releaseSpecialAtk() {}

		vector<Entity*> getProjectileList() {return projectileList;}
		vector<Entity*> getMeleeList() {return meleeList;}

		void removeProj(int);
		void removeMelee(int);
		void offScreen();

	protected:
		//Audio for class
		Jukebox sfx;
		//Keeps track of jumps (max of two)
		int jumpCount;
		vector<Entity*> projectileList;
		vector<Entity*> meleeList;
		//States of the object
		int isJump;
		int isFastFall;
		int isAtk;
		int isSpecial;
		int isSpecDown;
		int isGhost;
		int isAerial;
};

#endif
