#ifndef EVENTS_H
#define EVENTS_H

//#include "SDL.h"
//#include "stdafx.h"
#include <SDL/SDL.h>
#include "CharSelect.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "MapSelect.h"

using namespace std;

class Events {
	public:
		Events();
		int resolve();
		void resolveCharSelect();
		void resolveMapSel();
		void addCollision(Entity *, Entity *);
		void add(BaseCharacter *, BaseCharacter *, CharSelect *, MapSelect *);

	private:
		BaseCharacter *player0, *player1;
		CharSelect *charSel;
		MapSelect *mapSel;
		
};

#endif
