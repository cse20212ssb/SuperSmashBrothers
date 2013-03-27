//Inherits from the Base Character Class

#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "BaseCharacter.h"

class Megaman : public BaseCharacter{
	public:
		Megaman();
		virtual SDL_Surface *getSprite();
		virtual void setSprite(SDL_Surface*);
		virtual int getHeight();
		virtual int getWidth();
		virtual int getX();
		virtual int getY();
		virtual void setMoveDir(int);
		virtual void move();
		virtual SDL_Rect getSrc();
		virtual int isStanding();
		virtual int getAniCounter();
		virtual void setAniCounter(int);
		virtual void jump();
		virtual void leftAtk();
		virtual void rightAtk();
		virtual void upAtk();
		virtual void downAtk();
		virtual void specialAtk();
		virtual void checkPosition(); //Ensure character isn't going off screen with move or jump
	
};

#endif
