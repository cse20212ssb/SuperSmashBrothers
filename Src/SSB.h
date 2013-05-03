/* SSB class

This is the SSB class, which is utilized for processing all the events of the program. The main file
will run an instance of this class in order to run the program. This class processes the initial setup
of the joystick, goes to the various screens, then loops through the gameplay portion of the program 
until the user exits

*/


#ifndef SSB_H
#define SSB_H

//#include "stdafx.h"
//#include "SDL.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "Events.h"
#include "Entity.h"
#include "Platform.h"
#include "Megaman.h"
#include "BigSmoke.h"
#include "Firebat.h"
#include "Leprechaun.h"
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
		int init(); //This function initializes gameplay
		void select(); //These is for initializing the user's various selections

		int events(); //Processes all events
		void loop(); //The gameplay loop
		void render(); //Draws items on the screen
		void cleanUp(); //Removes items as they go out of scope
		void fps_control(); //Ensures that the program runs at a constant speed regardless of the machine
	
		//Variables for fps_control
		int FPS, nextTick;

		//Establishing the entity and player objects
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
