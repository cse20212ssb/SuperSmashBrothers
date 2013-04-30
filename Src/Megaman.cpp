#include "stdafx.h"
#include "Megaman.h"
#include <iostream>

#define WALKING 0
#define AERIAL 1

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
				//No longer fastfalling or ghost or aerial
				isFastFall = 0;
				isGhost = 0;
				isAerial = 0;
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
	else if (B->getID() == 4 && !isGhost) {
		velX = B->getFaceDir() * 1.5;
		velY = -3;
		isGhost = 1;
	}
	//Projectile
	else if (B->getID() == 5) {
		velX += B->getVelX() * .1;
	}	
	//SpecDown Proj
	else if (B->getID() == 6) {
		velX = 7 * B->getVelX() * .5;
		velY = -7 * B->getVelX() * .2;
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

void Megaman::aerialAtk() {
	isAerial = 1;
}

void Megaman::Atk(){
	if (jumpCount > 1)
		aerialAtk();
	else {
		Melee *sword;
		//Create a new sword and add it to list
		if(faceDir == 1)
			//Ignore position here, actually set in move function
			sword = new Melee(posX + width, posY + 15, 13, 28, 0, faceDir);
		else
			sword = new Melee(posX, posY + 15, 13, 28, 0, faceDir);

		meleeList.push_back(sword);
		isAtk = 1;
	}
}

void Megaman::releaseAtk(){
	isAtk = 0;
	isAerial = 0;
	for(int i = 0; i < meleeList.size(); i++)
		meleeList[i] -> setIsGone(1);
	aniCounter[AERIAL] = 0;
}

//Draws onto specified surface
void Megaman::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	
	if (isGhost && jumpCount == 0)
		src.x = 5 * width;
	//if in air
	else if (jumpCount > 0 || velY > 3 || velY < -3) {
		if (isAerial) {
			int numOfSprites = 4;
			int timePerSprite = 5;
			if (aniCounter[AERIAL] > numOfSprites * timePerSprite) 
				aniCounter[AERIAL] = 0;
			int frame = aniCounter[AERIAL] / timePerSprite;

			if (frame == 0) src.x = 10 * width;
			else if (frame == 1) src.x = 11 * width;
			else if (frame == 2) src.x = 12 * width;
			else src.x = 4 * width;
		
			aniCounter[AERIAL]++;
		}
		//If jumping and special attacking
		else if (isAtk || isSpecial) src.x = width * 17;
		else src.x = 4 * width;
		
	}
	//if on ground
	else if (moveDir != 0) {
		int numOfSprites = 4;
		int timePerSprite = 10;
		if (aniCounter[WALKING] > numOfSprites * timePerSprite)
			aniCounter[WALKING] = 0;
		int frame = aniCounter[WALKING] / timePerSprite;
		
		if (frame == 1) src.x = width * 2;
		else if (frame == 2) src.x = width * 3;
		else if (frame == 3) src.x = width * 2;
		else src.x = width;
		//If running and special attacking
		if (isSpecial || isAtk) src.x += width * 13;

		aniCounter[WALKING]++;
	}
	else {
		aniCounter[WALKING] = 0;
		//If standing and special attacking
		if (isSpecial || isAtk){
			src.x = width * 9;
		}
		else{
			src.x = 0;
		}
	}

	//If left or right
	if (faceDir == 1 && !isAerial) src.y = 33;
	else src.y = 0;

	src.w = width;
	src.h = height;
	
	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.h = 0;
	dst.w = 0;

	//Loop through all projectiles and provide movement
	for(int i = 0; i < projectileList.size(); i++){
		projectileList[i] -> drawTo(surf);
	}
	

	//Loop through melee and provide display
	for(int i = 0; i < meleeList.size(); i++){
		meleeList[i] -> drawTo(surf);
	}

	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}
