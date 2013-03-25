#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "stdafx.h"
#include "SDL.h"
#include "string"

using namespace std;

class BaseCharacter{
public:
	BaseCharacter(void);
	virtual SDL_Surface *getSprite();
	virtual int getHeight();
	virtual int getWidth();
	virtual int getSrcX();
	virtual int getSrcY();
	virtual int getDstX();
	virtual int getDstY();
	virtual void moveLeft();
	virtual void moveRight(); 
	virtual void jump();
	virtual void leftAtk();
	virtual void rightAtk();
	virtual void upAtk();
	virtual void downAtk();
	virtual void specialAtk();
	virtual void checkPosition(); //Ensure character isn't going off screen with move or jump
	virtual void animate(string);
	
private:
	SDL_Surface *sprite;
};

#endif

