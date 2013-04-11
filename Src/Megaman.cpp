#include "stdafx.h"
#include "Megaman.h"

//height and width are constant to Megaman
Megaman::Megaman(int x, int y) : BaseCharacter(x, y, 31, 33){
	//Load sprite sheet
	sprite = SDL_LoadBMP("../Images/Sprites/Megaman/Megaman.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
}

void Megaman::onCollision(Entity *B) {
	//Platform
	if (B->getID() == 3) {
		//If bottom border is in a certain range of the platform
		if (velY > 0 && getBot() > B->getTop() - 5 && getBot() < (B->getBot() + B->getTop()) / 2) {
		//if (velY > 0 && getBot() > B->getTop() - 7 && getBot() < B->getTop() + 7) {
			if (velY > 3)
				velY = -velY / 5;
			else
				velY = 0;
			jumpCount = 0;
			canJump = 1;
			posY = B->getTop() - height;
		}
	}
	
	/*
	//Other Character
	if (B->getID() == 2) {
		addVelX(-B->getVelX() / 10);
		addVelY(-B->getVelY() / 10);
	}
	*/
}

void Megaman::specialAtk() {
	int new_posX = posX;
	int vel = 12;
	if(faceDir == 1) {
		vel = 12;
		new_posX += width;
	}
	else if(faceDir == -1) {
		vel = -12;
	}
	
	//Create a new projectile and add it to list
	Projectile *pj = new Projectile(posX, posY+17, 5, 5, vel, 0);
	projectileList.push_back(pj);
	isSpecial = 1;
}

void Megaman::releaseSpecialAtk() {
	isSpecial = 0;
}

//Draws onto specified surface
void Megaman::drawTo(SDL_Surface *surf) {
	SDL_Rect src;

	//if in air
	if (jumpCount > 0 || velY > 3) {
		src.x = 4 * width;
		//If jumping and special attacking
		if (isSpecial) src.x += width * 13;
	}
	//if on ground
	else if (moveDir != 0) {
		if (aniCounter > 40)
			aniCounter = 0;
		int frame = aniCounter / 10;
		
		if (frame == 1) src.x = width * 2;
		else if (frame == 2) src.x = width * 3;
		else if (frame == 3) src.x = width * 2;
		else src.x = width;
		//If running and special attacking
		if (isSpecial) src.x += width * 13;
	}
	else {
		//If standing and special attacking
		if (isSpecial) src.x = width * 9;
		else src.x = 0;
	}

	//If left or right
	if (faceDir == 1) src.y = 33;
	else src.y = 0;

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
