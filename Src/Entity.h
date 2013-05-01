/*
Base class for all objects with movement and/or borders
*/

#ifndef ENTITY_H
#define ENTITY_H

//#include "stdafx.h"
//#include "SDL.h"
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

		int getPosX() {return posX;}
		int getPosY() {return posY;}
		
		int getTop() {return top;}
		int getBot() {return bot;}
		int getLeft() {return left;}
		int getRight() {return right;}

		void addVelX(double inc) {velX += inc;}
		void addVelY(double inc) {velY += inc;}
		double getVelX() {return velX;}
		double getVelY() {return velY;}

		void setMoveDir(int dir);
		int getMoveDir() {return moveDir;}
		void setIsGone(int t) {isGone = t;}
		int getIsGone(){return isGone;}

		void updateFaceDir(int);

		void setPosX(int new_x) {posX = new_x;}
		void setPosY(int new_y) {posY = new_y;}


	protected:
		SDL_Surface *sprite;

		double posX, posY;

		int height, width;

		int top, bot, left, right;

		double velX, velY;
		double accelX, accelY;
		double maxVelX, maxVelY;
		
		//Direction of movement
		int moveDir;
		//Direction object is facing
		int faceDir;
		//Keeps track of the animation
		int aniCounter;
		int isGone;
		int isRecoil;

};

#endif
