//#include "stdafx.h"
#include "BaseCharacter.h"
#include <iostream>

using namespace std;

BaseCharacter::BaseCharacter(int x, int y, int h, int w) : Entity(x, y, h, w){
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	setMoveDir(0);
	isGhost = 0;
	faceDir = 1;
	maxVelX = 3;
	maxVelY = 9;
	jumpCount = 0;
	isSpecial = 0;
	isAtk = 0;
	isAerial = 0;
}

BaseCharacter::~BaseCharacter() {
	for (int i = 0; i < projectileList.size(); i++) {
		projectileList.erase(projectileList.begin() + i);
	}
	
	for (int i = 0; i < meleeList.size(); i++) {
		meleeList.erase(meleeList.begin() + i);
	}

	Mix_CloseAudio();

	cout << "BaseCharacter deconstructed" << endl;
}

void BaseCharacter::fastFall() {
	if (jumpCount > 0 || velY != 0) {
		velY = maxVelY;
		isFastFall = 1;	
	}
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
		velY = -4*maxVelY/5;
	jumpCount++;
	isGhost = 0;
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
