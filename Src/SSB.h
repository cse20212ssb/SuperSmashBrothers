#ifndef SSB_H
#define SSB_H

#include "stdafx.h"
#include "SDL.h"
//#include <SDL/SDL.h>
#include <iostream>
#include <vector>

#include "Events.h"
#include "Entity.h"
#include "Platform.h"
#include "Megaman.h"
#include "BaseCharacter.h"
#include "CharSelect.h"

using namespace std;

class SSB {
	public:
		SSB() {}
		void execute();
		void drawMap();
	
	private:
		int init();
		void select();

		int events();
		void loop();
		void render();
		void cleanUp();

		BaseCharacter *player0, *player1;
		
		vector<Entity*> entityList;

		SDL_Surface *screen, *map;
		SDL_Joystick *js_0, *js_1;

		CharSelect *sel;
		MapSelect *mapSel;
	
		Events queue;
};		
	

#endif
