/* Melee class

This is the melee class, which is similar to the projectile class without initial movement. The melee
class features four IDs to create unique melee behavior and animations for each character. Megaman
has a character ID of 0, Big Smoke 1, Leprechaun 3, and Firebat 4. Melee have a specified hitbox
in front of the character for collision detection. When an object collides with melee, it will
recoil further than when it colides with a projectile

*/

//#include "stdafx.h"
#include "Melee.h"
#include <iostream>

using namespace std;

//The constructor for the melee class, utilizes member list initialization
Melee::Melee(int x,int y, int h, int w, int dir, SDL_Surface *t_sprite) : Entity (x, y, h, w) {
	faceDir = dir;
	sprite = t_sprite;

	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );
	isGone = 0;
	counter = 0;

}

//Renders melee objects on the screen
void Melee::drawTo(SDL_Surface *surf) {
	SDL_Rect src;
	if(faceDir == 1)
		src.x = 0;
	else
		src.x = width;
	src.y = 0;
	src.h = height;
	src.w = width;

	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.h = 0;
	dst.w = 0;
	if (counter >= 20)
		isGone = 1;
	counter++;
	SDL_BlitSurface(getSprite(), &src, surf, &dst);
}

void Melee::onCollision(Entity *obj){

}


