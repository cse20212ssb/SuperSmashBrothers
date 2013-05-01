#ifndef STARTSCREEN_H
#define STARTSCREEN_H

//#include <SDL/SDL.h>
#include "SDL.h"
#include "stdafx.h"

class startScreen {
	public:
		startScreen();
		startScreen(SDL_Surface *);
		void draw();
		void select(){sel = 1;}
		int isDone() {return sel;}
		
		
	private:
		int sel;
		SDL_Surface *screen;
		SDL_Surface *map;
};	

#endif