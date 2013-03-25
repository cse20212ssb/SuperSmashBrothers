//Inherits from the Base Character Class

#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "BaseCharacter.h"

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