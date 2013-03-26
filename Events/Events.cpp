#include "Events.h"

using namespace std;

Events::Events() {
	SDL_JoystickEventState(SDL_ENABLE);
}

void Events::add(BaseCharacter *obj) {
	ptr = obj;
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
			case SDL_JOYAXISMOTION:
				cout << "JOYSTICK: AXIS" << endl;
				cout << "   EVENT: ";
				if (event.jaxis.axis == 0)
					//Horizontal movement
					if (event.jaxis.value > 0) {
						ptr->setMoveDir(1);
						cout << "RIGHT";
					}
					else if (event.jaxis.value < 0) cout << "LEFT";
					else {
						cout << "CENTERED";
						ptr->setMoveDir(0);
					}
				else if (event.jaxis.axis == 1)
					if (event.jaxis.value < 0) cout << "UP";
					else if (event.jaxis.value > 0) cout << "DOWN";
					else cout << "CENTERED";
				cout << endl;
			break;

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
			
			case SDL_QUIT:
				return 0;
			break;
		}
	}
	return 1;
}

