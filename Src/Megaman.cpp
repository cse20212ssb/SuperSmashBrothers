#include "stdafx.h"
#include "Megaman.h"
#include <iostream>

using namespace std;

//height and width are constant to Megaman
Megaman::Megaman(int x, int y) : BaseCharacter(x, y, 33, 31){
	//Load sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Megaman.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
}

void Megaman::onCollision(Entity *B) {
	//Platform
	if (B->getID() == 3) {
		//If bottom border is in a certain range of the platform
		if (velY > 0 && getBot() > B->getTop() - 5 && getBot() < (B->getBot() + B->getTop()) / 2) {
			if (!isSpecDown) {
				//Gives the character a "bounce"
				if (velY > 3)
					velY = -velY / 5;
				else
					velY = 0;
				jumpCount = 0;
				posY = B->getTop() - height;
				//No longer fastfalling
				isFastFall = 0;
				//No longer ghost
				isGhost = 0;
			}
			else {
				//Special Down projectiles created
				velY = 0;
				posY = B->getTop() - height;
				Projectile *pj0 = new Projectile(posX + width/2, posY + 25, 6, 12, 3, 2);
				Projectile *pj1 = new Projectile(posX + width/2 - 10, posY + 25, 6, 12, -3, 1);
				projectileList.push_back(pj0);
				projectileList.push_back(pj1);
				isSpecDown = 0;
				isFastFall = 0;
			}
		}
	}
	//Melee
	else if (B->getID() == 5 && !isGhost) {
		if (B->getLeft() > getLeft())
			velX -= 1.5;
		else if (B->getRight() < getRight())
			velX += 1.5;
		velY -= 5;
		isGhost = 1;
	}		
	
	/*
	//Other Character
	if (B->getID() == 2) {
		addVelX(-B->getVelX() / 10);
		addVelY(-B->getVelY() / 10);
	}
	*/
}

void Megaman::specialAtk() {
	int vel = faceDir * 10;

	Projectile *pj;
	//Create a new projectile and add it to list
	if (!isFastFall) {
		if(faceDir == 1)
			pj = new Projectile(posX + width, posY + 15, 6, 12, vel, 0);
		else
			pj = new Projectile(posX, posY + 15, 6, 12, vel, 0);
		projectileList.push_back(pj);
		isSpecial = 1;
	}
	else
		isSpecDown = 1;
}

void Megaman::releaseSpecialAtk() {
	isSpecial = 0;
}

void Megaman::Atk(){
	Melee *sword;
	//Create a new sword and add it to list
	if(faceDir == 1){
		sword = new Melee(posX + width, posY + 45, 13, 28, 0, faceDir);
	}
	else{
		sword = new Melee(posX, posY + 25, 13, 28, 0, faceDir);
	}

	meleeList.push_back(sword);
	isAtk = 1;
}

void Megaman::releaseAtk(){
	isAtk = 0;
	for(int i = 0; i < meleeList.size(); i++)
		meleeList[i] -> setIsGone(1);
	//cout << "getMeleeGone = " << getMeleeGone() << endl;
}
