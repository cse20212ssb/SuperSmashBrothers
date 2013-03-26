//Inherits from the Base Character Class

#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "BaseCharacter.h"

<<<<<<< HEAD
class Megaman:BaseCharacter{
public:
	Megaman();
	SDL_Surface *getSprite();
	int getHeight();
	int getWidth();
	int getSrcX();
	int getSrcY();
	int getDstX();
	int getDstY();
	void moveLeft(); //Moves character left (accepts x-coordinate position)
	void moveRight();
	void jump();
	void leftAtk();
	void rightAtk();
	void upAtk();
	void downAtk();
	void specialAtk();
	void checkPosition(); //Ensure character isn't going off screen with move or jump
	void animate(string);

private:
	//Length and width variables are used to determine hitbox
	int height;
	int width;
	//The original location
	int srcX;
	int srcY;
	//The destination location
	int dstX;
	int dstY;
	SDL_Surface *sprite;
	//Counter for animation length
	int aniCounter;
	
};

#endif
=======
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
>>>>>>> chan
