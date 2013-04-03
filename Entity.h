#ifndef ENTITY_H
#define ENTITY_H

#include <SDL/SDL.h>

class Entity {
	public:
		Entity() {}
		Entity(int, int, int, int);

		int collides(Entity *);
		virtual void onCollision(Entity *){}
		virtual int getID() {return 0;}

		virtual void drawTo(SDL_Surface *) {}
		SDL_Surface *getSprite();

		void update();
		
		int getTop() {return top;}
		int getBot() {return bot;}
		int getLeft() {return left;}
		int getRight() {return right;}

	protected:
		SDL_Surface *sprite;

		int posX, posY;
		int height, width;

		int top, bot, left, right;

		double velX, velY;
		double accelX, accelY;
		double maxVelX, maxVelY;
		int moveDir;
};

#endif
