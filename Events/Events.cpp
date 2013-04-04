//#include "stdafx.h"
#include "Events.h"

using namespace std;

Events::Events() {
	SDL_JoystickEventState(SDL_ENABLE);
}

//Adds characters to the Event object
void Events::add(BaseCharacter *obj0, BaseCharacter *obj1) {
	player0 = obj0;
	player1 = obj1;
}

//Pushes collision event to queue
void Events::addCollision(Entity *obj1, Entity *obj2) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	//data type is *void, needs to be typecast
	event.user.data1 = obj1;
	event.user.data2 = obj2;
	
	SDL_PushEvent(&event);
}
	

/*
Axis #0
Right: -32768
Left: 32767

Axis #1
Up : -32768
Down: 32767

Button 1: A
Button 2: B
Button 8: Select
Button 9: Start
Buttons 0, 3-7 are empty
*/

int Events::resolve() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			//Joystick axis motion
			case SDL_JOYAXISMOTION:
				//Which joystick
				if (event.jaxis.which == 0)
					select = player0;
				else
					select = player1;
				//Horizontal movement
				if (event.jaxis.axis == 0) {
					//Right
					if (event.jaxis.value > 0) {
						select->setMoveDir(1);
						//cout << "RIGHT";
					}
					//Left
					else if (event.jaxis.value < 0) {
						select->setMoveDir(-1);
						//cout << "LEFT";
					}
					//Centered
					else {
						select->setMoveDir(0);
						//cout << "CENTERED";
					}
				}
				//Vertical Movement
				else if (event.jaxis.axis == 1) {
					//Up
					if (select->jumpable()) {
						select->jump();
					}
					//Down
					else if (event.jaxis.value > 0) {
						 //cout << "DOWN";
					}
					//Centred
					else {
						//cout << "CENTERED";
					}
				}
			break;
			/*
			//Buttons and stuffz
			case SDL_JOYBUTTONUP:
			case SDL_JOYBUTTONDOWN:
				cout << "JOYSTICK: BUTTON" << endl;
				cout << "   EVENT: ";
				if (event.jbutton.state == SDL_PRESSED) {
					if (event.jbutton.button == 1) cout << "A";
					else if (event.jbutton.button == 2) cout << "B";
					else if (event.jbutton.button == 8) cout << "SELECT";
					else if (event.jbutton.button == 9) cout << "START";
					else cout << "MISSING BUTTON";
			
					cout << " PRESSED";
				}
				else {
					if (event.jbutton.button == 1) cout << "A";
					else if (event.jbutton.button == 2) cout << "B";
					else if (event.jbutton.button == 8) cout << "SELECT";
					else if (event.jbutton.button == 9) cout << "START";
					else cout << "MISSING BUTTON";
		
					cout << " RELEASED";
				}
				cout << endl;				
			break;
			*/
			
			case SDL_QUIT:
				return 0;
			break;
			
			//Collision events
			case SDL_USEREVENT:
				//Typecast *void to *Entity
				((Entity *)event.user.data1)->onCollision((Entity *)event.user.data2);
				((Entity *)event.user.data2)->onCollision((Entity *)event.user.data1);
				//cout << "COLLISION DETECTED" << endl;
			break; 
		}
	}
	return 1;
}

