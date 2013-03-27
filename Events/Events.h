#ifndef EVENTS_H
#define EVENTS_H

#include <SDL/SDL.h>
#include <iostream>
#include "../Characters/BaseCharacter.h"

using namespace std;

class Events {
	public:
		Events();
		int resolve();
		void add(BaseCharacter *);
	private:
		BaseCharacter *ptr;
};

#endif
