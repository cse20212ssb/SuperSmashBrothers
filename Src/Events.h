/* Events class

This is the events class, which is used for determining and processing what the user presses on the NES
controller. There are several resolve functions because each screen of events requires its own resolve
function. The screen of events include the start screen, character select screen, map screen, and the
actual gameplay screen. Polymorphism is heavily used here to access the unique functions of each
class that derived from the entity class. This is the header file of the class.

*/


#ifndef EVENTS_H
#define EVENTS_H

//#include "SDL.h"
//#include "stdafx.h"
#include <SDL/SDL.h>
#include "CharSelect.h"
#include "BaseCharacter.h"
#include "Entity.h"
#include "MapSelect.h"
#include "startScreen.h"

using namespace std;

class Events {
	public:
		Events(); //Constructor
		int resolve(); //The resolve function for gameplay
		void resolveStartSel(); //Resolve function for start screen
		void resolveCharSelect(); //Resolve function for character select screen
		void resolveMapSel(); //Resolve function for character select screen
		void addCollision(Entity *, Entity *); //Used for adding the collision in the queue of collisions to process
		void add(BaseCharacter *, BaseCharacter *); //Creates the players
		void addSel(startScreen *, CharSelect *, MapSelect *); //Creates the start screen, character select, and map select objects for display
	private:
		//Pointers to each of the classes so their virtual functions can be used
		BaseCharacter *player0, *player1;
		startScreen *startSel;
		CharSelect *charSel;
		MapSelect *mapSel;	
};

#endif
