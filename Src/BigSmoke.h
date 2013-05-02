/* Big Smoke class
Inspriation for this class was taken from Grand Theft Auto: San Andreas. While he has a lower move speed and small jump, he enjoys the use of his Tec9, which allows him to shoot projectiles without constraint. This class, just as all the other character classes, derives from the BaseCharacter classes.
*/

#ifndef BIGSMOKE_H
#define BIGSMOKE_H

#include "SDL.h"
#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class BigSmoke : public BaseCharacter{
	public:
		//Constructor
		BigSmoke() {}
		BigSmoke(int x, int y);

		//Draws to specified surface
		virtual void drawTo(SDL_Surface *);
		//Moves the character
		virtual void move();
		
		//Normal attack functions
		virtual void Atk();
		virtual void releaseAtk();
		//Special attack functions
		virtual void specialAtk();
		virtual void releaseSpecialAtk();

	
};

#endif

