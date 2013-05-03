/* MapSelect class

This is the map select class and is used for the user to select between two maps.
It is similar to the character select class, but doesn't use a linked list because
there are only two entries. Instead an index is set to 1 or 0 to indicate the
selected map and the location of the cursor.

*/


#ifndef MAPSELECT_H
#define MAPSELECT_H

#include <SDL/SDL.h>
//#include "SDL.h"
//#include "stdafx.h"

class MapSelect {
	public:
		MapSelect(); //The constructor
		MapSelect(SDL_Surface *);  //The non-default constructor, which accepts the screen as an argument
		~MapSelect(); //The deconstructor
		void draw(); //This function is used to draw the map select bmp onto the screen as well as establish the cursor
		//Used to move the cursor and document which selection the user is one
		void toRight() {index = 1;} 
		void toLeft(){index = 0;}
		//Determines if the user has selected a map and notes that the process is complete
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

