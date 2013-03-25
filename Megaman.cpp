#include "stdafx.h"
#include "Megaman.h"


Megaman::Megaman(){
	//Create the starting sprite for character
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanStand.bmp");
	//Establish the width and height of character
	int width = 85;
	int height = 102;
	//Establish Source
	srcX = 0;
	srcY = 0;
	//Establish position
	dstX = 200;
	dstY = 340;
	//Establish counter
	aniCounter = 0;
}


SDL_Surface *Megaman::getSprite(){
	return sprite;
};

int Megaman::getHeight(){return height;};

int Megaman::getWidth(){return width;};

int Megaman::getSrcX(){return srcX;};

int Megaman::getSrcY(){return srcY;};

int Megaman::getDstX(){return dstX;};

int Megaman::getDstY(){return dstY;};

void Megaman::moveLeft(){
	dstX -= 10;
	animate("left");
};

void Megaman::moveRight(){
	dstX += 10;
	aniCounter++;
	animate("right");
};

void Megaman::jump(){
};

void Megaman::leftAtk(){};

void Megaman::rightAtk(){};

void Megaman::upAtk(){};

void Megaman::downAtk(){};

void Megaman::specialAtk(){};

void Megaman::checkPosition(){

};

void Megaman::animate(string action){
	if(action == "right"){
		switch(aniCounter){
			case 2:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR1.bmp");
				break;
			case 4:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR2.bmp");
				break;
			case 5: 
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR3.bmp");
				break;
			case 7:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR4.bmp"); 
				break;
			case 9:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR5.bmp");
				break;
			case 11:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanStand.bmp");
				aniCounter = 0;
				break;
		}
	}
};