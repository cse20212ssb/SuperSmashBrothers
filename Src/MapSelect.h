#ifndef MAPSELECT_H
#define MAPSELECT_H

#include <SDL/SDL.h>
//#include "SDL.h"
//#include "stdafx.h"

class MapSelect {
	public:
		MapSelect();
		MapSelect(SDL_Surface *);
		~MapSelect();
		void draw();
		void toRight() {index = 1;}
		void toLeft(){index = 0;}
		void select(){sel = index;}
		int isDone() {return sel;}
		
		
	private:
		int sel;
		int index;
		SDL_Surface *sprite;
		SDL_Surface *screen;
		SDL_Surface *map;
};	

#endif
