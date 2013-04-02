//#include "stdafx.h"
#include "Megaman.h"

Megaman::Megaman() : BaseCharacter(200, 380, 120, 100){
	//Create the sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Mega.bmp");
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

void Megaman::leftAtk(){};

void Megaman::rightAtk(){};

void Megaman::upAtk(){};

void Megaman::downAtk(){};

void Megaman::specialAtk(){};

void Megaman::checkPosition(){};
