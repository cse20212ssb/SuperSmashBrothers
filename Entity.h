#ifndef ENTITY_H
#define ENTITY_H

class Entity {
	public:
		Entity(int, int, int, int);

		int collides(Entity *);
		
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

Entity::Entity(int x, int y, int h, int w) {
	posX = x;
	posY = y;
	height = h;
	width = w;
	
	top = posY;
	bot = posY + height;
	left = posX;
	right = posX + width;

	velX = 0;
	velY = 0;
	accelX = 0;
	accelY = 0;
}

int Entity::collides(Entity *b) {
	if (this->getBot() < b->getTop()) return 0;
	if (this->getTop() < b->getBot()) return 0;
	if (this->getLeft() < b->getRight()) return 0;
	if (this->getRight() < b->getLeft()) return 0;
	return 1;
}

#endif ENTITY_H
