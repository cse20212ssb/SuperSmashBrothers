#include "Entity.h"

using namespace std;

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
