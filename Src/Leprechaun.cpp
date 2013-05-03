/* Leprechaun class
Taken from our beloved Notre Dame. The Leprechaun throws footballs of mass destruction that cause massive knockback. Because he's a real man, he don't need no melee weapon and punches people. In addition to that, he does not flinch, meaning he is impervious to knockbacks. This class, just as all the other character classes, derives from the BaseCharacter classes.
*/
//#include "stdafx.h"
#include "Leprechaun.h"
#include <iostream>

#define WALKING 0
#define SPECIAL 1

using namespace std;

//Constructor
Leprechaun::Leprechaun(int x, int y) : BaseCharacter(x, y, 28, 34){
	//Load sprite sheets
	sprite = SDL_LoadBMP("Images/Sprites/Leprechaun/Leprechaun.bmp");
	projSprite = SDL_LoadBMP("Images/Sprites/Leprechaun/Football.bmp");
	meleeSprite = SDL_LoadBMP("Images/Sprites/Leprechaun/Pawnch.bmp");	
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 0, 0xFF, 0) );
	SDL_SetColorKey(meleeSprite, SDL_SRCCOLORKEY, SDL_MapRGB(meleeSprite->format, 0, 0xFF, 0) );
	SDL_SetColorKey(projSprite, SDL_SRCCOLORKEY, SDL_MapRGB(projSprite->format, 0, 0xFF, 0) );
	//Load sounds
	sfx.load("Sounds/Leprechaun/melee.wav", "Sounds/Leprechaun/proj.wav", NULL, NULL);
	aniCounter[SPECIAL] = 0;
}

//Movement in both x and y directions
void Leprechaun::move() {	
	maxVelX = 4.5;
	//If moving
	if (moveDir != 0 && !isGhost) {
		accelX = .33 * moveDir;
	}
	else {
		//Not moving, friction
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

	//Apply velocities and accelerations
	velX += accelX;
	velY += accelY;

	if (velX > maxVelX) velX = maxVelX;
	if (velX < -maxVelX) velX = -maxVelX;
	if (velY > maxVelY) velY = maxVelY;
	if (velY < -maxVelY) velY = -maxVelY;

	posX += velX;
	posY += velY;
		
	if (!isSpecial)
		isThrow = 0;

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
				meleeList[i] -> setPosX(posX + width);
				meleeList[i] -> setPosY(posY);
			}
			else{
				meleeList[i] -> setPosX(posX + width - 7);
				meleeList[i] -> setPosY(posY + 10);
			}
		//Left
		else {
			if(jumpCount > 0 || velY > 3){
				meleeList[i] -> setPosX(posX - width);
				meleeList[i] -> setPosY(posY);
			}
			else{
				meleeList[i] -> setPosX(posX - 4);
				meleeList[i] -> setPosY(posY + 10);
			}
		}

		
		meleeList[i]->updateBorders();
		if (meleeList[i]->getIsGone()) {
			isAtk = 0;
			removeMelee(i);
		}
	}
}

//Collision detection for platform only
void Leprechaun::onCollision(Entity *B) {
	//Platform
	if (B->getID() == 1) {
		//If bottom border is in a certain range of the platform
		if (velY > 0 && getBot() > B->getTop() - 10 && getBot() < (B->getBot() + B->getTop()) / 2 + 5) {
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
}

//Special attack (hold down bit)
void Leprechaun::specialAtk() {
	if (!isSpecial) {
		isSpecial = 1;
		aniCounter[SPECIAL] = SDL_GetTicks();
	}
}

//Special attack (creation bit)
void Leprechaun::createSpecialAtk() {
	//Increases range based on how long it is held
	double factor = (SDL_GetTicks() - aniCounter[SPECIAL]) / 1000.0;
	sfx.play(1);
	int vel = faceDir * 15 * factor;
	Projectile *pj;
	//Create a new projectile and add it to list
	if(faceDir == 1)
		pj = new Projectile(posX + width - 14, posY + 11, 6, 12, vel, faceDir, 2, projSprite);
	else
		pj = new Projectile(posX - 1, posY + 11, 6, 12, vel, faceDir, 2, projSprite);
	projectileList.push_back(pj);
	isSpecial = 0;
	isThrow = 0;
	aniCounter[SPECIAL] = 0;
}

//Special attack (release bit)
void Leprechaun::releaseSpecialAtk() {
	if (isSpecial)
		createSpecialAtk();
}

//Normal attack
void Leprechaun::Atk(){
	sfx.play(0);
	Melee *pawnch;
	//Create a new bat and add it to list
	if(faceDir == 1)
		//Ignore position here, actually set in move function
		pawnch = new Melee(posX + width, posY + 10, 10, 10, faceDir, meleeSprite);
	else
		pawnch = new Melee(posX + 10, posY + 10, 10, 10, faceDir, meleeSprite);
	meleeList.push_back(pawnch);
	isAtk = 1;
}

//Release of "A"
void Leprechaun::releaseAtk(){
	isAtk = 0;
	for(int i = 0; i < meleeList.size(); i++)
		meleeList[i] -> setIsGone(1);
	aniCounter[WALKING] = 0;
}

//Draws onto specified surface
void Leprechaun::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	//if in air
	if (jumpCount > 0 || velY > 3 || velY < -3) {
		//If jumping and special attacking
		if (isSpecial) 
			if (isSpecial)
				src.x = width * 6;
			else if (isThrow)
				src.x = width * 8;
		//If jumping and attacking
		else if (isAtk) src.x = width * 4;
		else src.x = 3 * width;
	}
	//if on ground
	else if (moveDir != 0) {
		int numOfSprites = 2;
		int timePerSprite = 10;
		if (aniCounter[WALKING] > numOfSprites * timePerSprite)
			aniCounter[WALKING] = 0;
		int frame = aniCounter[WALKING] / timePerSprite;
		
		if (frame == 1) src.x = width;
		else src.x = width * 2;
		if (isSpecial)
			src.x = width * 6; //Expand
		else if (isThrow)
			src.x = width * 7;
		else if (isAtk) 
			src.x = width * 4;
		
		aniCounter[WALKING]++;
	}
	//if standing
	else {
		aniCounter[WALKING] = 0;
		//If standing and special attacking
		if (isSpecial)
			src.x = width * 6; //Expand
		else if (isThrow)
			src.x = width * 7;
		else if (isAtk) 
			src.x = width * 4;
		else{
			src.x = 0;
		}
	}
	if (isAtk) 
		src.x = width * 4;

	//If left or right
	if (faceDir == 1) src.y = height + 6;
	else src.y = 2;

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
