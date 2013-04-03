#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(int x, int y, int h, int w) : Entity(x, y, h, w){
	maxVelX = 6;
	maxVelY = 6;
	aniCounter = 0;
}

void BaseCharacter::setMoveDir(int dir) {
	moveDir = dir;
}

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

	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}

SDL_Surface * BaseCharacter::getSprite() {
	return sprite;
}

void BaseCharacter::move() {
	if (moveDir != 0) {
		accelX = 1.25 * moveDir;
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
	accelY = 0.75 * inAir;

	velX += accelX;
	velY += accelY;

	if (velX > maxVelX) velX = maxVelX;
	if (velX < -maxVelX) velX = -maxVelX;
	if (velY > maxVelY) velY = maxVelY;
	if (velY < -maxVelY) velY = -maxVelY;

	posX += velX;
	posY += velX;

	aniCounter += velX / 8;
}

void BaseCharacter::jump() {
	velY = -maxVelY;
	inAir = 1;
}

	










