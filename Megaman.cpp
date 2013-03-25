#include "stdafx.h"
#include "Megaman.h"


Megaman::Megaman(){
	//Create the starting sprite for character
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanStand.bmp");
	//Establish the width and height of character
	width = 85;
	height = 102;
	srcX = 5;
	srcY = 5;
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
	aniCounter++;
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

void Megaman::stopMove(){
	aniCounter = 0;
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanStand.bmp");
}

void Megaman::animate(string action){
	if(action == "right"){
		switch(aniCounter){
			case 3:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR1.bmp");
				break;
			case 6:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR2.bmp");
				break;
			case 9: 
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR3.bmp");
				break;
			case 12:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR4.bmp"); 
				break;
			case 15:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR5.bmp");
				break;
			case 18:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR6.bmp");
				break;
			case 21:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR7.bmp");
				break;
			case 24:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR8.bmp");
				break;
			case 27:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR9.bmp");
				break;
			case 30:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanR10.bmp");
				aniCounter = 0;
				break;
		}
	}
	else if(action == "left"){
		switch(aniCounter){
			case 3:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL1.bmp");
				break;
			case 6:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL2.bmp");
				break;
			case 9: 
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL3.bmp");
				break;
			case 12:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL4.bmp"); 
				break;
			case 15:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL5.bmp");
				break;
			case 18:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL6.bmp");
				break;
			case 21:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL7.bmp");
				break;
			case 24:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL8.bmp");
				break;
			case 27:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL9.bmp");
				break;
			case 30:
				sprite = SDL_LoadBMP("Images/Sprites/Megaman/MegamanL10.bmp");
				aniCounter = 0;
				break;
		}
	}
};