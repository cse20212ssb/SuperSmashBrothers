#include "stdafx.h"
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(int x, int y, int h, int w) : Entity(x, y, h, w){
	setMoveDir(0);
	maxVelX = 6;
	maxVelY = 9;
	aniCounter = 0;
	jumpCount = 0;
}

void BaseCharacter::setMoveDir(int dir) {
	moveDir = dir;
}

//Draws onto specified surface
void BaseCharacter::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	src.x = 0; //Something with aniCounter
	src.y = 0;
	src.h = height;
	src.w = width;

	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.h = 0;
	dst.w = 0;

	//Loop through all projectiles and provide movement
	for(int i = 0; i < projectileList.size(); i++){
		projectileList[i] -> drawTo(surf);
	}

	//Add to aniCounter after certain amount of pixel movement, then after that amt of movement will result in a blitSurface
	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}

//Movement in both x and y directions
void BaseCharacter::move() {
	//Loop through all projectiles and provide movement
	for(int i = 0; i < projectileList.size(); i++){
		projectileList[i] -> move();
	}

	if (moveDir != 0) {
		accelX = .75 * moveDir;
	}
	else {
		if (velX > 0) accelX = -1;
		if (velX < 0) accelX = 1;
		if (velX < 2 && velX > -2) {
			velX = 0;
			accelX = 0;
		}
	}
	//Gravity
	accelY = 0.3;

	velX += accelX;
	velY += accelY;

	if (velX > maxVelX) velX = maxVelX;
	if (velX < -maxVelX) velX = -maxVelX;
	if (velY > maxVelY) velY = maxVelY;
	if (velY < -maxVelY) velY = -maxVelY;

	posX += velX;
	posY += velY;
}

void BaseCharacter::fastFallCrouch() {
	if (jumpCount > 0)
		velY += 5;
	//Crouch
}

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
