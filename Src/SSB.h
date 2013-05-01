#ifndef SSB_H
#define SSB_H

#include "stdafx.h"
#include "SDL.h"
//#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "Events.h"
#include "Entity.h"
#include "Platform.h"
#include "Megaman.h"
#include "BigSmoke.h"
#include "BaseCharacter.h"
#include "CharSelect.h"
#include "MapSelect.h"
#include "Jukebox.h"
#include "startScreen.h"

using namespace std;

class SSB {
	public:
		//Constructor and deconstructor in init() and cleanUp()
		SSB() {}
		~SSB() {}
		void execute();
	
	private:
		int init();
		void select();

		int events();
		void loop();
		void render();
		void cleanUp();
		void fps_control();
	
		//Variables for fps_control
		int FPS, nextTick;

		BaseCharacter *player0, *player1;
		
		vector<Entity*> entityList;

		SDL_Surface *screen, *map;
		SDL_Joystick *js_0, *js_1;

		CharSelect *sel;
		MapSelect *mapSel;

		startScreen *startSel;

		Events queue;

		Jukebox bgMusic;
};		
	

#endif
