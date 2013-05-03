/* Megaman class

Takes inspiration from the classic NES game "Megaman". Has fast movement and a cool aerial movement buff activated by hold "A" during your second jump. Attacks however are fairly weak and shooting has a time constraint. It also has a special down attack which is activated by fastfalling and pressing "B". This class, just as all the other character classes, derives from the BaseCharacter classes.
*/

#ifndef MEGAMAN_H
#define MEGAMAN_H

//#include "SDL.h"
//#include "stdafx.h"
#include "BaseCharacter.h"
#include "Entity.h"


class Megaman : public BaseCharacter{
	public:
		//Constructor
		Megaman() {}
		Megaman(int x, int y);

		//Draw function, redefined to account for aerial
		virtual void drawTo (SDL_Surface *);
		//Behavior on collision is redefined to account for special down move
		virtual void onCollision(Entity *);
		//Move function
		virtual void move();
		
		//Attack functions (sword)
		virtual void Atk();
		virtual void releaseAtk();

		//Aerial attack (movement buff)
		virtual void aerialAtk();

		//Special attack functions (lazour)
		virtual void specialAtk();
		virtual void releaseSpecialAtk();
	private:
		//Special down, only class with it
		void specialDown();

	
};

#endif

