//#include "stdafx.h"
#include "BaseCharacter.h"
#include <iostream>

using namespace std;

BaseCharacter::BaseCharacter(int x, int y, int h, int w) : Entity(x, y, h, w){
	setMoveDir(0);
	isGhost = 0;
	faceDir = 1;
	maxVelX = 3;
	maxVelY = 9;
	jumpCount = 0;
	isSpecial = 0;
	isAtk = 0;
}

//Movement in both x and y directions
void BaseCharacter::move() {
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
		if(jumpCount > 0 || velY > 3){
			meleeList[i] -> setPosX(posX + width * faceDir - 3);
			meleeList[i] -> setPosY(posY+12);
		}
		else{
			meleeList[i] -> setPosX(posX + width * faceDir);
			meleeList[i] -> setPosY(posY+15);
		}

		
		meleeList[i]->updateBorders();
		if (meleeList[i]->getIsGone()) {
			isAtk = 0;
			removeMelee(i);
		}
	}
		
	if (moveDir != 0 && !isGhost) {
		accelX = .33 * moveDir;
		aniCounter++;
	}
	else {
		double accel_inc = .25;
		if (isGhost) accel_inc = 0;
		if (velX > 0) accelX = -accel_inc;
		if (velX < 0) accelX = accel_inc;
		if (velX < 1 && velX > -1) {
			velX = 0;
			accelX = 0;
		}
		aniCounter = 0;
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
}

void BaseCharacter::fastFall() {
	if (jumpCount > 0)
		velY += 5;
	isFastFall = 1;	
}

//If you can jump
int BaseCharacter::jumpable() {
	if (jumpCount >= 2 || isSpecDown)
		return 0;
	return 1;
}
void BaseCharacter::jump() {
	//First jump
	if (jumpCount == 0)
		velY = -2*maxVelY/3;
	//Second jump
	if (jumpCount == 1)
		velY = -3*maxVelY/4;
	jumpCount++;
}

void BaseCharacter::removeProj(int index) {
	projectileList.erase(projectileList.begin()+index);
}

void BaseCharacter::removeMelee(int index) {
	meleeList.erase(meleeList.begin()+index);
}

void BaseCharacter::offScreen(){
	if(posX > 800) posX = 0;
	else if(posX < 0) posX = 800;
	
	if(posY < 0) posY = 400;
	else if(posY > 400) posY = 0;
}

