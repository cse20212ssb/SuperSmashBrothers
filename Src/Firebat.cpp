#include "stdafx.h"
#include "Firebat.h"
#include <iostream>

#define WALKING 0
#define STIMPACK 1
#define ATK 2

using namespace std;

//height and width are constant to Firebat
Firebat::Firebat(int x, int y) : BaseCharacter(x, y, 30, 31){
	//Load sprite sheet
	sprite = SDL_LoadBMP("Images/Sprites/Firebat/Firebat.bmp");
	projSprite = NULL;
	meleeSprite = SDL_LoadBMP("Images/Sprites/Firebat/fire.bmp");
	stimSprite = SDL_LoadBMP("Images/Sprites/Firebat/FirebatStimpack.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 0, 255, 0) );
	SDL_SetColorKey(meleeSprite, SDL_SRCCOLORKEY, SDL_MapRGB(meleeSprite->format, 255,0,0) );
	SDL_SetColorKey(stimSprite, SDL_SRCCOLORKEY, SDL_MapRGB(stimSprite->format, 0, 255, 0) );
	sfx.load("Sounds/Firebat/attack.wav", "Sounds/Firebat/stim1.wav", "Sounds/Firebat/stim2.wav", NULL);
}

//Movement in both x and y directions
void Firebat::move() {	
	maxVelX = 3;
	if (moveDir != 0 && !isGhost && !isRest) {
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

	if (isSpecial) {
		if ((SDL_GetTicks() - aniCounter[STIMPACK]) / 1000 > 6) {
			isSpecial = 0;
			isRest = 1;
			aniCounter[STIMPACK] = SDL_GetTicks();
		}
		velX = 6 * moveDir;
	}
	else if (isRest) {
		if ((SDL_GetTicks() - aniCounter[STIMPACK]) / 1000 > 3) {
			isRest = 0;
		}
	}

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
				meleeList[i] -> setPosX(posX + width * faceDir - 6);
				meleeList[i] -> setPosY(posY+4);
			}
			else{
				meleeList[i] -> setPosX(posX + width * faceDir - 6);
				meleeList[i] -> setPosY(posY+9);
			}
		//Left
		else {
			if(jumpCount > 0 || velY > 3){
				meleeList[i] -> setPosX(posX + width * faceDir - 10);
				meleeList[i] -> setPosY(posY+3);
			}
			else{
				meleeList[i] -> setPosX(posX + width * faceDir - 5);
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

void Firebat::specialAtk() {
	if (isSpecial == 0 && !isRest) {
		sfx.play(1);
		isSpecial = 1;
		aniCounter[STIMPACK] = SDL_GetTicks();
	}
}

void Firebat::releaseSpecialAtk() {
	//isSpecial = 0;
}

void Firebat::Atk(){
	if ((((aniCounter[ATK] - SDL_GetTicks()) / 1000 > 3 && !isSpecial) || ((aniCounter[ATK] - SDL_GetTicks()) / 1000 > 1 && isSpecial)) && !isRest) {
		sfx.play(0);
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
		aniCounter[ATK] = SDL_GetTicks();
	}
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
	
	if (isRest) 
		src.x = 0;
	else if (isGhost && jumpCount == 0)
		src.x = 11 * width;
	//if in air
	else if (jumpCount > 0 || velY > 3 || velY < -3) {
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
		
		if (frame == 1) src.x = width;
		else if (frame == 2) src.x = width * 2;
		else if (frame == 3) src.x = width * 3;
		else src.x = width * 2;

		//If running and special attacking
		if (isAtk) src.x += width * 6;

		aniCounter[WALKING]++;
	}
	else {
		aniCounter[WALKING] = 0;
		//If standing and special attacking
		if (isAtk){
			src.x = width * 6;
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

	SDL_BlitSurface(getSprite(), &src, surf, &dst);

	//Loop through all projectiles and provide movement
	for(int i = 0; i < projectileList.size(); i++){
		projectileList[i] -> drawTo(surf);
	}
	
	//Loop through melee and provide display
	for(int i = 0; i < meleeList.size(); i++){
		meleeList[i] -> drawTo(surf);
	}

	if (isSpecial || isRest) {
		if (faceDir == 1)
			dst.x = posX + width / 2 - 10;
		else 
			dst.x = posX + width/2;
		dst.y = posY - 10;
		if (isSpecial) {
			src.x = 0;
			src.y = 0;
		}
		else if (isRest) {
			src.x = 10;
			src.y = 0;
		}
		src.h = 10;
		src.w = 10;
		SDL_BlitSurface(stimSprite, &src, surf, &dst);
	}
}
