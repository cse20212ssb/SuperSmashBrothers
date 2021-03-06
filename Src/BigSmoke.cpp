/* Big Smoke class
Inspriation for this class was taken from Grand Theft Auto: San Andreas. While he has a lower move speed and small jump, he enjoys the use of his Tec9, which allows him to shoot projectiles without constraint. This class, just as all the other character classes, derives from the BaseCharacter classes.
*/

//#include "stdafx.h"
#include "BigSmoke.h"
#include <iostream>

#define WALKING 0
#define AERIAL 1

using namespace std;

//height and width are constant to BigSmoke
BigSmoke::BigSmoke(int x, int y) : BaseCharacter(x, y, 30, 33){
	//Load sprite sheets
	sprite = SDL_LoadBMP("Images/Sprites/BigSmoke/BigSmoke.bmp");
	projSprite = SDL_LoadBMP("Images/Sprites/BigSmoke/bullet.bmp");
	meleeSprite = SDL_LoadBMP("Images/Sprites/BigSmoke/Bat.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 0, 0xFF, 0) );
	SDL_SetColorKey(meleeSprite, SDL_SRCCOLORKEY, SDL_MapRGB(meleeSprite->format, 0, 0xFF, 0) );
	SDL_SetColorKey(projSprite, SDL_SRCCOLORKEY, SDL_MapRGB(projSprite->format, 0, 0xFF, 0) );
	//Loads sounds
	sfx.load("Sounds/BigSmoke/melee.wav", "Sounds/BigSmoke/proj.wav", NULL, NULL);
	//Overwrites the original maxVels
	maxVelX = 2.5;
	maxVelY = 7;
}

//Movement in both x and y directions
void BigSmoke::move() {	
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

	//Apply velocities
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
				meleeList[i] -> setPosY(posY+3);
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

//Special attack, create projectile without time restraints
void BigSmoke::specialAtk() {
	int vel = faceDir * 10;
	sfx.play(1);
	Projectile *pj;
	//Create a new projectile and add it to list
	if(faceDir == 1)
		pj = new Projectile(posX + width - 8, posY + 11, 6, 12, vel, faceDir, 0, projSprite);
	else
		pj = new Projectile(posX - 1, posY + 11, 6, 12, vel, faceDir, 0, projSprite);
	projectileList.push_back(pj);
	isSpecial = 1;
}

//When "B" is released
void BigSmoke::releaseSpecialAtk() {
	isSpecial = 0;
}

//Normal attack, bat
void BigSmoke::Atk(){
	Melee *bat;
	sfx.play(0);
	//Create a new bat and add it to list
	if(faceDir == 1)
		//Ignore position here, actually set in move function
		bat = new Melee(posX + width, posY + 15, 13, 28, faceDir, meleeSprite);
	else
		bat = new Melee(posX, posY + 15, 13, 28, faceDir, meleeSprite);
	
	meleeList.push_back(bat);
	isAtk = 1;
}
void BigSmoke::releaseAtk(){
	isAtk = 0;
	for(int i = 0; i < meleeList.size(); i++)
		meleeList[i] -> setIsGone(1);
	aniCounter[WALKING] = 0;
}
//Draws onto specified surface
void BigSmoke::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	
	//If hit with melee
	if (isGhost && jumpCount == 0)
		src.x = 5 * width;
	//if in air
	else if (jumpCount > 0 || velY > 3 || velY < -3) {
		//If jumping and special attacking
		if (isSpecial) src.x = width * 12;
		//If jumping and attacking
		else if (isAtk) src.x = width * 13;
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
		if (isSpecial || isAtk) src.x += width * 8;

		aniCounter[WALKING]++;
	}
	else {
		aniCounter[WALKING] = 0;
		//If standing and special attacking
		if (isSpecial)
			src.x = width * 7;
		else if (isAtk) 
			src.x = width * 8;
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
