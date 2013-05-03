/* Entity class

This is the entity class, which is base class for all objects: characters, platforms, projectiles, and melee weapons.
All functions related to all objects are defined here. This is the cpp implementation for the class. The functions defined
here include the constructor, deconstructor, updateBorders, collides, and get and set functions. The constructor is useful
for all classes due to member list initialization.

*/

//#include "stdafx.h"
#include "Entity.h"
#include <iostream>

using namespace std;

//The constructor of the entity class. This will be used with member list initialization so that
//each class doesn't have to define its own initial position, height, and width setters.
Entity::Entity(int x, int y, int h, int w) {
	//Determine position and size
	posX = x;
	posY = y;
	height = h;
	width = w;
	
	//The top left corner is taken as starting corner
	top = posY;
	bot = posY + height - 1;
	left = posX;
	right = posX + width - 1;

	//Establish no movement initially for most objects
	velX = 0;
	velY = 0;
	accelX = 0;
	accelY = 0;

	//For objects with animations this will serve as the counter to
	//help determine which state in the animation they are located in
	for (int i = 0; i < 3; i++)
		aniCounter[i] = 0;
}


//The deconstructor
Entity::~Entity() {
	cout << "Destorying entity..." << endl;
	SDL_FreeSurface(sprite);
	cout << "... done" << endl;
}

//Ensures the collision framework will know the hitbox of the object
void Entity::updateBorders() {
	top = posY;
	bot = posY + height;
	left = posX;
	right = posX + width;
}

//Used for accessing the current sprite of an object
SDL_Surface * Entity::getSprite() {
	return sprite;
}

//This logic determines whether one entity has collided with another entity
int Entity::collides(Entity *b) {
	//Essentially if the area created bottom, left, right, or top border is overlapping
	//with another, this will return 1. If there is no overlap, then a 0 will be returned
	if (getBot() < b->getTop()) return 0;
	if (getTop() > b->getBot()) return 0;
	if (getRight() < b->getLeft()) return 0;
	if (getLeft() > b->getRight()) return 0;

	return 1;
}

//This is used for setting which direction the object is facing
void Entity::setMoveDir(int dir) {
	if (dir != 0) 
		faceDir = dir;
	moveDir = dir;
}

//This is used for setting the direction something is facing
void Entity::updateFaceDir(int dir){
	faceDir = dir;
}
