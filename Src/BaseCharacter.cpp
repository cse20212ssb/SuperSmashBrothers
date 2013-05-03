/* BaseCharacter class

Is the base for all character classes. This class contains the basic information of a class, such as  whether or not it's attacking 
or which direction it's facing, as well as some basic functions, such as jump(). Some of these classes are updated further in its derived 
classes, if the vision of the new class requires us to do so. The BaseCharacter class derives from the Entity class, which hold information 
such as position and hitboxes. 
*/

//#include "stdafx.h"
#include "BaseCharacter.h"
#include <iostream>

using namespace std;

//Constructor
BaseCharacter::BaseCharacter(int x, int y, int h, int w) : Entity(x, y, h, w){
	//Opens audio channels for Mix_Chunks
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	//Initialization of all the nonsense
	setMoveDir(0);
	isGhost = 0;
	faceDir = 1;
	maxVelX = 3;
	maxVelY = 9;
	jumpCount = 0;
	isSpecial = 0;
	isRest = 0;
	isAtk = 0;
	isAerial = 0;
}

//Deconstructor, is virtual 
BaseCharacter::~BaseCharacter() {
	for (int i = 0; i < projectileList.size(); i++) {
		projectileList.erase(projectileList.begin() + i);
	}
	
	for (int i = 0; i < meleeList.size(); i++) {
		meleeList.erase(meleeList.begin() + i);
	}

	Mix_CloseAudio();
}

//"Fast fall"
void BaseCharacter::fastFall() {
	if (jumpCount > 0 || velY != 0) {
		velY = maxVelY;
		isFastFall = 1;	
	}
}

//Test whether you can jump or not
int BaseCharacter::jumpable() {
	if (jumpCount >= 2 || isSpecDown || isRest)
		return 0;
	return 1;
}

//Jump functions
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

//Removes a certain projectile object
void BaseCharacter::removeProj(int index) {
	projectileList.erase(projectileList.begin()+index);
}


//Removes a certain melee object
void BaseCharacter::removeMelee(int index) {
	meleeList.erase(meleeList.begin()+index);
}

//Makes the screen wrapped
void BaseCharacter::offScreen(){
	if(posX > 800) posX = 0;
	else if(posX < 0) posX = 800;
	
	if(posY < 0) posY = 628;
	else if(posY > 628) posY = 0;
}

//Standard onCollision behavior, unless otherwise defined.
void BaseCharacter::onCollision(Entity *B) {
	//Platform
	if (B->getID() == 1) {
		//If bottom border is in a certain range of the platform
		if (velY > 0 && getBot() > B->getTop()-10 && getBot() < (B->getBot() + B->getTop()) / 2 + 5) {
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
