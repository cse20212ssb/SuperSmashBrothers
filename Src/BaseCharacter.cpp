#include "stdafx.h"
#include "BaseCharacter.h"

using namespace std;

BaseCharacter::BaseCharacter(int x, int y, int w, int h) : Entity(x, y, w, h){
	setMoveDir(0);
	maxVelX = 3;
	maxVelY = 9;
	faceDir = -1;
	jumpCount = 0;
	isSpecial = 0;
}

//Movement in both x and y directions
void BaseCharacter::move() {
	//Loop through all projectiles and provide movement
	for(int i = 0; i < projectileList.size(); i++){
		projectileList[i] -> move();
	}

	if (moveDir != 0) {
		accelX = .33 * moveDir;
		aniCounter++;
	}
	else {
		if (velX > 0) accelX = -.25;
		if (velX < 0) accelX = .25;
		if (velX < 2 && velX > -2) {
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

	posY += velY;
	posX += velX;
}

void BaseCharacter::fastFallCrouch() {
	if (jumpCount > 0)
		velY += 5;
	//Crouch
}

//If you can jump
int BaseCharacter::jumpable() {
	if (!canJump)
		return 0;
	if (jumpCount >= 2)
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

