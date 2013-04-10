//#include "stdafx.h"
#include "Megaman.h"
#include <iostream>
#include "Projectile.h"
#include "Entity.h"

//height and width are constant to Megaman
Megaman::Megaman(int x, int y) : BaseCharacter(x, y, 31, 32){
	//Load sprite sheet
	sprite = SDL_LoadBMP("../Images/Sprites/Megaman/RightMovement.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
}

void Megaman::onCollision(Entity *B) {
	//Platform
	if (B->getID() == 3) {
		//If bottom border is in a certain range of the platform
		if (velY > 0 && getBot() > B->getTop() - 5 && getBot() < (B->getBot() + B->getTop()) / 2) {
		//if (velY > 0 && getBot() > B->getTop() - 7 && getBot() < B->getTop() + 7) {
			if (velY > 3)
				velY = -velY / 10;
			else
				velY = 0;
			jumpCount = 0;
			canJump = 1;
			posY = B->getTop() - height;
		}
	}
	
	/*
	//Other Character
	if (B->getID() == 2) {
		addVelX(-B->getVelX() / 10);
		addVelY(-B->getVelY() / 10);
	}
	*/
}


void Megaman::specialAtk(){
	int vel = 12;
	if(dir == 1)
		vel = 12;
	else if(dir == -1)
		vel = -12;

	Projectile *pj = new Projectile(posX, posY+25, 25, 25, vel, 0);
	projectileList.push_back(pj);
	isSpecial = 1;
}

/*
void Megaman::setSprite(int dir){
	if(dir == 1)
		sprite = SDL_LoadBMP("Images/Sprites/Megaman/RightMovement.bmp");
	else if(dir == -1)
		sprite = SDL_LoadBMP("Images/Sprites/Megaman/LeftMovement.bmp");
} */

void Megaman::leftAtk(){}

void Megaman::rightAtk(){}

void Megaman::upAtk(){}

void Megaman::downAtk(){}

void Megaman::checkPosition(){}
