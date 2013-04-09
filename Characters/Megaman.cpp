#include "../stdafx.h"
#include "Megaman.h"
#include <iostream>

Megaman::Megaman(int x, int y) : BaseCharacter(x, y, 58, 50){
	//Create the sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Mega.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 255, 255) );
	/*
	//Establish the width and height of character
	width = 23;
	height = 30;
	//Establish position
	posX = 200;
	posY = 380;
	*/
}

void Megaman::onCollision(Entity *B) {
	if (B->getID() == 3) { //Platform
		if (velY > 0 && getBot() > B->getTop() - 1 && getBot() < (B->getBot() + B->getTop()) / 2) {
			velY = 0;
			canJump = 1;
			posY = B->getTop() - height;
		}
	}
}

void Megaman::leftAtk(){}

void Megaman::rightAtk(){}

void Megaman::upAtk(){}

void Megaman::downAtk(){}

void Megaman::specialAtk(){}

void Megaman::checkPosition(){}
