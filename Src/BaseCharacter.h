/* BaseCharacter class
Is the base for all character classes. This class contains the basic information of a class, such as  whether or not 
it's attacking or which direction it's facing, as well as some basic functions, such as jump(). Some of these classes 
are updated further in its derived classes, if the vision of the new class requires us to do so. The BaseCharacter 
class derives from the Entity class, which hold information such as position and hitboxes. 
*/

#ifndef BASECHARACTER_H
#define BASECHARACTER_H

//#include "SDL.h"
//#include "stdafx.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"
#include "Jukebox.h"
#include <vector>

using namespace std;

class BaseCharacter : public Entity{
	public:
		//Constructors
		BaseCharacter() {}
		BaseCharacter(int, int, int, int);
		//Deconstructor
		virtual ~BaseCharacter();

		//Standard behavior on collision
		virtual void onCollision(Entity *);
		//Draw to specified surface
		virtual void drawTo(SDL_Surface *){}

		//Move, also used as a frame ticker
		virtual void move() {}
		//Jump function
		void jump();
		//If possible to jump
		int jumpable();
		//"Fastfall", that is, fall really fast
		void fastFall();
		
		//Functions that are defined in the derived classes
		virtual void Atk() {}
		virtual void releaseAtk() {}
		virtual void aerialAtk() {}
		virtual void specialAtk() {}
		virtual void releaseSpecialAtk() {}

		//Returns the vectors containting projectiles and melees
		vector<Entity*> getProjectileList() {return projectileList;}
		vector<Entity*> getMeleeList() {return meleeList;}

		void removeProj(int);
		void removeMelee(int);
		void offScreen();

	protected:
		SDL_Surface *meleeSprite;
		SDL_Surface *projSprite;
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
		int isRest;
};

#endif
