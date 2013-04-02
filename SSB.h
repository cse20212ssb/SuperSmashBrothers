#ifndef SSB_H
#define SSB_H

#include <SDL/SDL.h>
#include <iostream>
#include "Events/Events.h"
#include "Characters/Megaman.h"
#include "Characters/BaseCharacter.h"

using namespace std;

class SSB {
	public:
		SSB() {}
		void execute();
	
	private:
		int init();
		int events();
		void loop();
		void render();
		void cleanUp();

		BaseCharacter *player;
		
		SDL_Surface *screen, *map;
		SDL_Joystick *js_1, *js_2;
	
		Events queue;
};		
	

#endif
