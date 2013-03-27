#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include <SDL/SDL.h>
//#include "stdafx.h"
//#include "SDL.h"
//#include "string"

using namespace std;

class BaseCharacter{
	public:
		BaseCharacter(){}
		virtual SDL_Surface *getSprite(){}
		virtual void setSprite(SDL_Surface*){}
		virtual int getHeight(){}
		virtual int getWidth(){}
		virtual int getX(){}
		virtual int getY(){}
		virtual void setMoveDir(int){}
		virtual void move(){}
		virtual SDL_Rect getSrc() {}
		virtual int isStanding(){}
		virtual int getAniCounter(){}
		virtual void setAniCounter(int){}
		virtual void jump(){}
		virtual void leftAtk(){}
		virtual void rightAtk(){}
		virtual void upAtk(){}
		virtual void downAtk(){}
		virtual void specialAtk(){}
		virtual void checkPosition(){} //Ensure character isn't going off screen with move or jump
	
	protected:
		SDL_Surface *sprite;
		//Movement direction
		int moveDir;
		//Length and width variables are used to determine hitbox
		int height;
		int width;
		//The location
		int posX;
		int posY;
		//Keeps track of the animation
		int aniCounter;
};

#endif

