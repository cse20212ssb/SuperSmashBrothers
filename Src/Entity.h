/* Entity class

This is the entity class, which is base class for all objects: characters, platforms, projectiles, and melee weapons.
All functions related to all objects are defined here. The ones defined in this header file, in particular, include
several set and get functions, and velocity based functions. Since most classes will override the functions located in
this file, many of the functions are virtual.

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
		virtual ~Entity();
		Entity(int, int, int, int);
		//Checks if it has collided with a certain entity
		int collides(Entity *);
		//Behavior on collision
		virtual void onCollision(Entity *){}
		virtual int getID() {return 0;}

		//Functions all classes will use to draw their sprites or backgrounds
		virtual void drawTo(SDL_Surface *) {}
		//Movement function for all classes
		virtual void move() {}
		SDL_Surface *getSprite();

		//This function will ensure that after collision or movement, the collision framework recognizes
		//the current location of the object
		void updateBorders();

		//These functions acquire or set the location of objects
		int getPosX() {return posX;}
		int getPosY() {return posY;}
		void setPosX(int new_x) {posX = new_x;}
		void setPosY(int new_y) {posY = new_y;}

		//These functions acquire the borders of the object for hitbox
		int getTop() {return top;}
		int getBot() {return bot;}
		int getLeft() {return left;}
		int getRight() {return right;}

		//These move the object or allows other classes to access the velocity of certain objects
		void addVelX(double inc) {velX += inc;}
		void addVelY(double inc) {velY += inc;}
		double getVelX() {return velX;}
		double getVelY() {return velY;}

		//These functions determine or provide information on which way certain objects are facing
		void setMoveDir(int dir);
		int getMoveDir() {return moveDir;}
		void setIsGone(int t) {isGone = t;}
		int getIsGone(){return isGone;}
		void updateFaceDir(int);
		int getFaceDir() {return faceDir;}	

	protected:
		SDL_Surface *sprite; //Variable used to establish sprites

		double posX, posY; //Position

		int height, width; //Dimensions

		int top, bot, left, right; //Dimensions for collision framework

		//Movement and limits
		double velX, velY;
		double accelX, accelY;
		double maxVelX, maxVelY;
		
		//Direction of movement
		int moveDir;
		//Direction object is facing
		int faceDir;
		//Keeps track of the animation
		int aniCounter[3];
		int isGone;
		//Determines if an object is recoiling 
		int isRecoil;

};

#endif
