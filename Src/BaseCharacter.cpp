//#include "stdafx.h"
#include "BaseCharacter.h"
#include <iostream>

using namespace std;

BaseCharacter::BaseCharacter(int x, int y, int w, int h) : Entity(x, y, w, h){
	setMoveDir(0);
	maxVelX = 3;
	maxVelY = 9;
	jumpCount = 0;
	isDecrementing = 1;
}

//Draws onto specified surface
void BaseCharacter::drawTo(SDL_Surface *surf) {
	SDL_Rect src;

	/*
	//cout << "velY: " << velY << endl;
	//In the air versus not in the air
	if(velY != .3){
		srcXVal = 240;
		src.x = srcXVal+20;
		//In the air attack animations
	}
	else{
	if(moveDir != 0){
		if(aniCounter%2==0){
			if(srcXVal >= 240){
				//cout << "srcXVal: " << srcXVal << endl;
				isDecrementing++;
				srcXVal = 180;
			}
			else if(srcXVal < 60){
				//cout << "srcXVal: " << srcXVal << endl;
				isDecrementing++;
				srcXVal = 120;
			}
			src.x = srcXVal+7;
		}
	}
	else if(moveDir == 0){
		srcXVal = 0;
		src.x = srcXVal;
		aniCounter = 0;
		isDecrementing = 1;
	}
		
	//Attack animations
	if(isAtk == 1){
		srcXVal = 875;
		src.x = srcXVal-16;
	}

	//Special Attack animations
	if(isSpecial == 1){
		srcXVal = 1004;
		src.x = srcXVal-8;
	}
	}
	*/

	//if in air
	if (canJump != 0) {
		src.x = 4 * width;
	}
	//if on ground
	else if (moveDir != 0) {
		if (aniCounter > 40)
			aniCounter = 0;
		int frame = aniCounter / 10;
		cout << frame << endl;
		
		if (frame == 1) src.x = width * 2;
		else if (frame == 2) src.x = width * 3;
		else if (frame == 3) src.x = width * 2;
		else src.x = width;
	}
	else {src.x = 0;}

	//cout << src.x << endl;

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
	
	SDL_BlitSurface(getSprite(), &src, surf, &dst);
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

	posX += velX;
	posY += velY;
	

	//Establish animation upon a certain amount of movement
	//animate(1);
}

/*
//This function will animate the character
void BaseCharacter::animate(int type) {
	if(type == 1){
		incrementaniCounter();
		if(isDecrementing%2==0)
			srcXVal -= 60;
		else
			srcXVal += 60;
	}
	else if(type == 0){
		setaniCounter(0);
	}
}
*/

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

void BaseCharacter::Atk(){
	isAtk = 1;
}

void BaseCharacter::releaseAtk(){
	isAtk = 0;
}

void BaseCharacter::releaseSpecialAtk(){
	isSpecial = 0;
}
