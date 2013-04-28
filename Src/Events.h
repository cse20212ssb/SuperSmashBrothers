#ifndef EVENTS_H
#define EVENTS_H

#include "SDL.h"
#include "stdafx.h"
//////#include <SDL/SDL.h>
#include "CharSelect.h"
#include "BaseCharacter.h"
#include "Entity.h"

using namespace std;

class Events {
	public:
		Events();
		int resolve();
		void resolveSel();
		void addCollision(Entity *, Entity *);
		void add(BaseCharacter *, BaseCharacter *, CharSelect *);

	private:
		BaseCharacter *player0, *player1;
		CharSelect *charSel;
		
};

#endif
