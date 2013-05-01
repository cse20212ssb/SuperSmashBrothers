#include "stdafx.h"
#include "BigSmoke.h"
#include <iostream>

using namespace std;

//height and width are constant to BigSmoke
BigSmoke::BigSmoke(int x, int y) : BaseCharacter(x, y, 30, 33){
	//Load sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/BigSmoke/BigSmoke.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
}

void BigSmoke::onCollision(Entity *B) {
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
				Projectile *pj0 = new Projectile(posX + width/2, posY + 25, 6, 12, 3, 2,1);
				Projectile *pj1 = new Projectile(posX + width/2 - 10, posY + 25, 6, 12, -3, 1,1);
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

void BigSmoke::specialAtk() {
	int vel = faceDir * 10;

	Projectile *pj;
	//Create a new projectile and add it to list
	if (!isFastFall) {
		if(faceDir == 1)
			pj = new Projectile(posX + width, posY + 15, 6, 12, vel, 0, 1);
		else
			pj = new Projectile(posX, posY + 15, 6, 12, vel, 0, 1);
		projectileList.push_back(pj);
		isSpecial = 1;
	}
	else
		isSpecDown = 1;
}

void BigSmoke::releaseSpecialAtk() {
	isSpecial = 0;
}

void BigSmoke::Atk(){
	Melee *sword;
	//Create a new sword and add it to list
	if(faceDir == 1){
		sword = new Melee(posX + width, posY + 40, 18, 28, 1, faceDir);
	}
	else{
		sword = new Melee(posX, posY + 25, 18, 28, 1, faceDir);
	}

	meleeList.push_back(sword);
	isAtk = 1;
}

void BigSmoke::releaseAtk(){
	isAtk = 0;
	for(int i = 0; i < meleeList.size(); i++)
		meleeList[i] -> setIsGone(1);
	//cout << "getMeleeGone = " << getMeleeGone() << endl;
}

//Draws onto specified surface
void BigSmoke::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	
	if (isGhost && jumpCount == 0)
		src.x = 5 * width;
	//if in air
	else if (jumpCount > 0 || velY > 3) {
		src.x = 4 * width;
		//If jumping and special attacking
		if (isAtk || isSpecial) src.x += width * 8;
	}
	//if on ground
	else if (moveDir != 0) {
		if (aniCounter > 40)
			aniCounter = 0;
		int frame = aniCounter / 10;
		
		if (frame == 1) src.x = width * 2;
		else if (frame == 2) src.x = width * 3;
		else if (frame == 3) src.x = width * 2;
		else src.x = width;
		//If running and special attacking
		if (isSpecial || isAtk) src.x += width * 8;
	}
	else {
		//If standing and special attacking
		if (isSpecial || isAtk){
			src.x = width * 7;
		}
		else{
			src.x = 0;
		}
	}

	//If left or right
	if (faceDir == 1) src.y = 33;
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
