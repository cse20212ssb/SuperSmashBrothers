/* Megaman class

Takes inspiration from the classic NES game "Megaman". Has fast movement and a cool aerial movement buff activated by hold "A" during your second jump. Attacks however are fairly weak and shooting has a time constraint. It also has a special down attack which is activated by fastfalling and pressing "B". This class, just as all the other character classes, derives from the BaseCharacter classes.
*/

#include "stdafx.h"
#include "Megaman.h"
#include <iostream>

#define WALKING 0
#define AERIAL 1
#define PROJ 2

using namespace std;

//height and width are constant to Megaman
Megaman::Megaman(int x, int y) : BaseCharacter(x, y, 33, 31){
	//Load sprite sheets
	sprite = SDL_LoadBMP("Images/Sprites/Megaman/Megaman.bmp");
	projSprite = SDL_LoadBMP("Images/Sprites/Megaman/Projectiles.bmp");
	meleeSprite = SDL_LoadBMP("Images/Sprites/Megaman/Sword.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
	SDL_SetColorKey(projSprite, SDL_SRCCOLORKEY, SDL_MapRGB(projSprite->format, 255, 0, 0) );
	SDL_SetColorKey(meleeSprite, SDL_SRCCOLORKEY, SDL_MapRGB(meleeSprite->format, 255, 0, 0) );
	//Loads sounds
	sfx.load("Sounds/Megaman/melee.wav", "Sounds/Megaman/proj.wav", "Sounds/Megaman/specDown.wav", "Sounds/Megaman/aerial.wav");
}

//Movement in both x and y directions
void Megaman::move() {	
	maxVelX = 5;
	//Aerial state
	if (isAerial) {
		accelX = 2.4;
		maxVelX = 10;
		velY -= .2;
	}	
	//If moving in a direction
	if (moveDir != 0 && !isGhost) {
		accelX = .33 * moveDir;
	}
	else {
		//Friection
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
	
	if (aniCounter[PROJ] - SDL_GetTicks() > 250) {
		isSpecial = 0;
	}

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
				meleeList[i] -> setPosX(posX + width * faceDir - 3);
				meleeList[i] -> setPosY(posY+10);
			}
			else{
				meleeList[i] -> setPosX(posX + width * faceDir - 3);
				meleeList[i] -> setPosY(posY+18);
			}
		//Left
		else {
			if(jumpCount > 0 || velY > 3){
				meleeList[i] -> setPosX(posX + width * faceDir + 3);
				meleeList[i] -> setPosY(posY+10);
			}
			else{
				meleeList[i] -> setPosX(posX + width * faceDir + 5);
				meleeList[i] -> setPosY(posY+18);
			}
		}

		
		meleeList[i]->updateBorders();
		if (meleeList[i]->getIsGone()) {
			isAtk = 0;
			removeMelee(i);
		}
	}
}

//Behavior on collision
void Megaman::onCollision(Entity *B) {
	//Platform
	if (B->getID() == 1) {
		//If bottom border is in a certain range of the platform
		if (velY > 0 && getBot() > B->getTop()-10 && getBot() < (B->getBot() + B->getTop()) / 2 + 5) {
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
				//Special down
				velY = 0;
				posY = B->getTop() - height;
				specialDown();
				isSpecDown = 0;
				isFastFall = 0;
			}
		}
	}
	//Melee
	else if (B->getID() == 2 && !isGhost) {
		velX = B->getFaceDir() * 1.5;
		velY = -3;
		isGhost = 1;
	}
	//Projectile
	else if (B->getID() == 3) {
		velX += B->getVelX() * .1;
	}	
	//SpecDown Proj
	else if (B->getID() == 4) {
		velX = 7 * B->getVelX() * .5;
		velY = -7 * B->getVelX() * .2;
		isGhost = 1;
	}
	//FOOTBALL
	else if (B->getID() == 5) {
		velX = B->getVelX();
		velY = -B->getVelY();
		isGhost = 1;
	}			
}

//Special down attack
void Megaman::specialDown() {
	//Special down sound
	sfx.play(2);
	//Special Down projectiles created
	Projectile *pj0 = new Projectile(posX + width/2, posY + 25, 6, 12, 3, 1, 1, projSprite);
	Projectile *pj1 = new Projectile(posX + width/2 - 10, posY + 25, 6, 12, -3, -1, 1, projSprite);
	projectileList.push_back(pj0);
	projectileList.push_back(pj1);
}

//Projectiles created
void Megaman::specialAtk() {
	if (SDL_GetTicks() - aniCounter[PROJ] > 500) {
		sfx.play(1);
		//Velocity of projectiles
		int vel = faceDir * 10;

		Projectile *pj;
		//Create a new projectile and add it to list
		if (!isFastFall) {
			if(faceDir == 1)
				pj = new Projectile(posX + width, posY + 15, 6, 12, vel, faceDir, 0, projSprite);
			else
				pj = new Projectile(posX, posY + 15, 6, 12, vel, faceDir, 0, projSprite);
			projectileList.push_back(pj);
			isSpecial = 1;
			aniCounter[PROJ] = SDL_GetTicks();
		}
		else
			isSpecDown = 1;
	}
}

//When "B" is released
void Megaman::releaseSpecialAtk() {
	isSpecial = 0;
}

//Aerial attack, movement buff
void Megaman::aerialAtk() {
	isAerial = 1;
}

//Normal attack, swrod
void Megaman::Atk(){
	//If megaman is in second jump, aerial instead of attack
	if (jumpCount > 1) {
		sfx.play(3);
		aerialAtk();
	}
	else {
		sfx.play(0);
		Melee *sword;
		//Create a new sword and add it to list
		if(faceDir == 1)
			//Ignore position here, actually set in move function
			sword = new Melee(posX + width, posY + 15, 13, 28, faceDir, meleeSprite);
		else
			sword = new Melee(posX, posY + 15, 13, 28, faceDir, meleeSprite);

		meleeList.push_back(sword);
		isAtk = 1;
	}
}

//When "A" is released
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
			//Aerial animation
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
		//Walking animation
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
	if (faceDir == 1 && !isAerial) src.y = height;
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
