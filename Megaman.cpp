//#include "stdafx.h"
#include "Megaman.h"

Megaman::Megaman() {
	moveDir = 0;
	//Create the starting sprite for character
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanStand.bmp");
	//Establish the width and height of character
	int width = 85;
	int height = 102;
	//Establish position
	posX = 200;
	posY = 340;
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
	if (moveDir != 0) {
		posX += moveDir * 10;
		aniCounter++;
	}
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
