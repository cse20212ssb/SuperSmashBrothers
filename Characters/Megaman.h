#ifndef MEGAMAN_H
#define MEGAMAN_H

//#include "SDL.h"
//#include "stdafx.h"
#include "BaseCharacter.h"
#include "../Entity.h"

class Megaman : public BaseCharacter{
	public:
		Megaman() {}
		Megaman(int x, int y);
		//virtual SDL_Surface *getSprite();

		virtual void onCollision(Entity *);
		virtual int getID() {return 2;}
		
		virtual void leftAtk();
		virtual void rightAtk();
		virtual void upAtk();
		virtual void downAtk();
		virtual void specialAtk();

		virtual void checkPosition(); //Ensure character isn't going off screen with move or jump
	
};

#endif
