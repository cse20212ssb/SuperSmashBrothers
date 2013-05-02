/* Firebat class

This class takes inspiration from the game StarCraft (the original). His only attack is through the use of his flamethrower. The special is the iconic stimpack, which boosts both the attack speed and the movement speed of the character.  The stimpack lasts a few seconds and when it runs out, the character is stunned. Stimpack is indicated by the yellow icon and the stun is indicated by the red icon. This class, just as all the other character classes, derives from the BaseCharacter classes.
*/ 

#ifndef Firebat_H
#define Firebat_H

#include "SDL.h"
#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "Projectile.h"
#include "Melee.h"

class Firebat : public BaseCharacter{
	public:
		//Constructor
		Firebat() {}
		Firebat(int x, int y);
		//Moves the character
		virtual void move();
		
		//Flame thrower
		virtual void Atk();
		virtual void releaseAtk();
		//Stimpack
		virtual void specialAtk();
		virtual void releaseSpecialAtk(){} //Does nothing
		//Draws character
		virtual void drawTo(SDL_Surface *);

	private:
		SDL_Surface *stimSprite;

	
};

#endif

