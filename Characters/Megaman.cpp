//#include "stdafx.h"
#include "Megaman.h"

Megaman::Megaman() {
	moveDir = 0;
	//Create the sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Mega.bmp");
	//Establish the width and height of character
	width = 23;
	height = 30;
	//Establish position
	posX = 200;
	posY = 380;
	//Establish counter
	aniCounter = 0;
}


SDL_Surface *Megaman::getSprite(){
	return sprite;
};

void Megaman::setSprite(SDL_Surface* newSprite) {
	sprite = newSprite;
}

int Megaman::getHeight(){return height;};

int Megaman::getWidth(){return width;};

int Megaman::getX(){return posX;};

int Megaman::getY(){return posY;};

void Megaman::setMoveDir(int dir) {
	moveDir = dir;
}

void Megaman::move() {
	if (moveDir > 0) {
		posX += moveDir * 4;
		aniCounter++;
		if (aniCounter == 20)
			aniCounter = 0;
	}
	if (moveDir == 0) //If movement has stopped, animation reset
		aniCounter = 0;
}

SDL_Rect Megaman::getSrc() {
	SDL_Rect src;
	if (moveDir == 0) {
		src.x = 58;
		src.y = 0;
		src.h = 78;
		src.w = 57;
	}
	else if (moveDir == 1) {
		src.x = (2 + aniCounter/5) * 58;
		src.y = 0;
		src.h = 78;
		src.w = 57;
		
	}
	return src;
}

int Megaman::isStanding() {
	if (moveDir == 0)
		return 1;
	return 0;
}

int Megaman::getAniCounter(){
	return aniCounter;
}

void Megaman::setAniCounter(int value) {
	aniCounter = value;
}

void Megaman::jump(){};

void Megaman::leftAtk(){};

void Megaman::rightAtk(){};

void Megaman::upAtk(){};

void Megaman::downAtk(){};

void Megaman::specialAtk(){};

void Megaman::checkPosition(){};
