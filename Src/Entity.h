/*
Base class for all objects with movement and/or borders
*/

#ifndef ENTITY_H
#define ENTITY_H

//#include "stdafx.h"
//#include "SDL.h"
#include <iostream>
#include <SDL/SDL.h>

using namespace std;

class Entity {
	public:
		Entity() {}
		Entity(int, int, int, int);
		//Checks if it has collided with a certain entity
		int collides(Entity *);
		//Behavior on collision
		virtual void onCollision(Entity *){}
		virtual int getID() {return 0;}

		virtual void drawTo(SDL_Surface *) {}
		virtual void move() {}
		SDL_Surface *getSprite();

		void updateBorders();
		
		int getTop() {return top;}
		int getBot() {return bot;}
		int getLeft() {return left;}
		int getRight() {return right;}

		void addVelX(double inc) {velX += inc;}
		void addVelY(double inc) {velY += inc;}
		double getVelX() {return velX;}
		double getVelY() {return velY;}

		int getaniCounter() {return aniCounter;}
		void setaniCounter(int n) {aniCounter = n;}
		void incrementaniCounter() {aniCounter++;}
		void setsrcXVal(int n) {srcXVal = n;}

		void setMoveDir(int dir) {moveDir = dir;}
		int getMoveDir() {return moveDir;}

	protected:
		SDL_Surface *sprite;

		int posX, posY;
		int height, width;

		int top, bot, left, right;

		double velX, velY;
		double accelX, accelY;
		double maxVelX, maxVelY;
		
		//Keeps track of position
		int moveDir;
		//Keeps track of the animation
		int aniCounter;
		//Keeps track of position
		int srcXVal;
};

#endif