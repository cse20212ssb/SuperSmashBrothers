//#include "stdafx.h"
#include "Firebat.h"
#include <iostream>

#define WALKING 0
#define AERIAL 1

using namespace std;

//height and width are constant to Firebat
Firebat::Firebat(int x, int y) : BaseCharacter(x, y, 30, 31){
	//Load sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/Firebat/Firebat.bmp");
	projSprite = NULL;
	meleeSprite = SDL_LoadBMP("Images/Sprites/Firebat/fire.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 0, 255, 0) );
	SDL_SetColorKey(meleeSprite, SDL_SRCCOLORKEY, SDL_MapRGB(meleeSprite->format, 0, 255, 0) );
}

//Movement in both x and y directions
void Firebat::move() {	
	maxVelX = 3;
	if (moveDir != 0 && !isGhost) {
		accelX = .33 * moveDir;
	}
	else {
		double accelResist = .25;
		if (isGhost) accelResist = 0;
		if (velX > 0) accelX = -accelResist;
		if (velX < 0) accelX = accelResist;
		if (velX < 1 && velX > -1) {
			velX = 0;
			accelX = 0;
		}
	}

	accelY = 0.3;

	velX += accelX;
	velY += accelY;

	if (velX > maxVelX) velX = maxVelX;
	if (velX < -maxVelX) velX = -maxVelX;
	if (velY > maxVelY) velY = maxVelY;
	if (velY < -maxVelY) velY = -maxVelY;

	posX += velX;
	posY += velY;

	updateBorders();
	offScreen();

	//Loop through all projectiles and provide movement
	for(int i = 0; i < projectileList.size(); i++){
		projectileList[i]->move();
		projectileList[i]->updateBorders();
		if (projectileList[i]->getRight() > 800 || projectileList[i]->getLeft() < 0 || projectileList[i]->getIsGone())
			removeProj(i);
	}

	//Loop through all melee of player 1
	for(int i = 0; i < meleeList.size(); i++){
		//Move the sword along with Megaman, updating the direction
		meleeList[i] -> updateFaceDir(faceDir);
		//Right
		if (faceDir == 1)
			if(jumpCount > 0 || velY > 3){
				meleeList[i] -> setPosX(posX + width * faceDir - 11);
				meleeList[i] -> setPosY(posY+1);
			}
			else{
				meleeList[i] -> setPosX(posX + width * faceDir - 11);
				meleeList[i] -> setPosY(posY+9);
			}
		//Left
		else {
			if(jumpCount > 0 || velY > 3){
				meleeList[i] -> setPosX(posX + width * faceDir + 14);
				meleeList[i] -> setPosY(posY+3);
			}
			else{
				meleeList[i] -> setPosX(posX + width * faceDir + 10);
				meleeList[i] -> setPosY(posY+11);
			}
		}

		
		meleeList[i]->updateBorders();
		if (meleeList[i]->getIsGone()) {
			isAtk = 0;
			removeMelee(i);
		}
	}
}

void Firebat::onCollision(Entity *B) {
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
				//Special Down here
				velY = 0;
				posY = B->getTop() - height;
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

void Firebat::specialAtk() {
	/*
	int vel = faceDir * 10;

	Projectile *pj;
	//Create a new projectile and add it to list
	if (!isFastFall) {
		if(faceDir == 1)
			pj = new Projectile(posX + width, posY + 15, 6, 12, vel,faceDir, 0, projSprite);
		else
			pj = new Projectile(posX, posY + 15, 6, 12, vel, faceDir, 0, projSprite);
		projectileList.push_back(pj);
		isSpecial = 1;
	}
	else
		isSpecDown = 1;
	*/
}

void Firebat::releaseSpecialAtk() {
	//isSpecial = 0;
}

void Firebat::Atk(){
	Melee *atk;
	//Create a new sword and add it to list
	if(faceDir == 1){
		atk = new Melee(posX + width, posY + 40, 15, 45, faceDir, meleeSprite);
	}
	else{
		atk = new Melee(posX, posY + 25, 15, 45, faceDir, meleeSprite);
	}

	meleeList.push_back(atk);
	isAtk = 1;
}

void Firebat::releaseAtk(){
	isAtk = 0;
	for(int i = 0; i < meleeList.size(); i++)
		meleeList[i] -> setIsGone(1);
	aniCounter[WALKING] = 0;
	//cout << "getMeleeGone = " << getMeleeGone() << endl;
}

//Draws onto specified surface
void Firebat::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	
	if (isGhost && jumpCount == 0)
		src.x = 5 * width;
	//if in air
	else if (jumpCount > 0 || velY > 3 || velY < -3) {
		src.x = 4 * width;
		//If jumping and special attacking
		//if (isSpecial) src.x += width * 8;
		//If jumping and attacking
		if (isAtk) src.x = width * 10;
		else src.x = width * 4;
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
		if (isSpecial || isAtk) src.x += width * 8;

		aniCounter[WALKING]++;
	}
	else {
		aniCounter[WALKING] = 0;
		//If standing and special attacking
		if (isSpecial || isAtk){
			src.x = width * 7;
		}
		else{
			src.x = 0;
		}
	}

	//If left or right
	if (faceDir == 1) src.y = height;
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
