#ifndef HITBOX_H
#define HITBOX_H

//#include "SDL.h"
//#include "stdafx.h"

using namespace std;

template<typename T>
class HitBox {
	public:
		HitBox() {}
		HitBox(T &name);
		int getTopBorder() {return topBorder;}
		int getBotBorder() {return botBorder;}
		int getLeftBorder() {return leftBorder;}
		int getRightBorder() {return rightBorder;}
	private:
		int topBorder;
		int botBorder;
		int leftBorder;
		int rightBorder;
};

//Constructor
template<typename T>
HitBox<T>::HitBox(T &name) {
	topBorder = name.getY();
	botBorder = name.getY() + name.getLength();
	leftBorder = name.getX();
	leftBorder = name.getX() + name.getWidth();
}

#endif
