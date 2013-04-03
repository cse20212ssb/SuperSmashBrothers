#ifndef EVENTS_H
#define EVENTS_H

//#include "SDL.h"
//#include "stdafx.h"
#include <SDL/SDL.h>
#include <iostream>
#include "../Characters/BaseCharacter.h"
#include "../Entity.h"

using namespace std;

class Events {
	public:
		Events();
		int resolve();
		void addCollision(Entity *, Entity *);
		void add(BaseCharacter *, BaseCharacter *);
	private:
		BaseCharacter *player0, *player1, *select;
};

#endif
