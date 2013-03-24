#ifndef SSB_H
#define SSB_H

#include <SDL/SDL.h>
#include <iostream>
#include "Events/Events.h"

using namespace std;

class SSB {
	public:
		SSB() {}
		void execute();
	
	private:
		int init();
		int event();
		void loop();
		void render();
		void cleanUp();
		
		SDL_Surface *screen, *map;
		SDL_Joystick *js_1, *js_2;
		Events queue;
};
	

#endif
