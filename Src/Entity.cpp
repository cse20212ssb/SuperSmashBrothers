//#include "stdafx.h"
#include "Entity.h"
#include <iostream>

using namespace std;

Entity::Entity(int x, int y, int h, int w) {
	posX = x;
	posY = y;
	height = h;
	width = w;
	
	top = posY;
	bot = posY + height - 1;
	left = posX;
	right = posX + width - 1;

	velX = 0;
	velY = 0;
	accelX = 0;
	accelY = 0;

	for (int i = 0; i < 3; i++)
		aniCounter[i] = 0;
}

Entity::~Entity() {
	SDL_FreeSurface(sprite);
}

void Entity::updateBorders() {
	top = posY;
	bot = posY + height;
	left = posX;
	right = posX + width;
}

SDL_Surface * Entity::getSprite() {
	return sprite;
}

int Entity::collides(Entity *b) {
	if (getBot() < b->getTop()) return 0;
	if (getTop() > b->getBot()) return 0;
	if (getRight() < b->getLeft()) return 0;
	if (getLeft() > b->getRight()) return 0;

	return 1;
}

void Entity::setMoveDir(int dir) {
	if (dir != 0) 
		faceDir = dir;
	moveDir = dir;
}

void Entity::updateFaceDir(int dir){
	faceDir = dir;
}
