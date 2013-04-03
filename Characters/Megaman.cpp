//#include "stdafx.h"
#include "Megaman.h"
#include <iostream>

Megaman::Megaman(int x, int y) : BaseCharacter(x, y, 60, 50){
	//Create the sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Mega.bmp");
	inAir = 1;
	/*
	//Establish the width and height of character
	width = 23;
	height = 30;
	//Establish position
	posX = 200;
	posY = 380;
	*/
	//Establish counter
}

void Megaman::onCollision(Entity *B) {
	if (B->getID() == 3) { //Platform
		velY = 0;
		inAir = 0;
		posY = B->getTop() - height;
	}
}

void Megaman::leftAtk(){};

void Megaman::rightAtk(){};

void Megaman::upAtk(){};

void Megaman::downAtk(){};

void Megaman::specialAtk(){};

void Megaman::checkPosition(){};
