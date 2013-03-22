//Outline of event handling

#ifndef EVENTS_H
#define EVENTS_H

#include <SDL/SDL.h>
#include <iostream>

using namespace std;

class Events {
	public:
		Events() {}
		int initialize();
		void handleEvents();
		int do_something();
	private:
		SDL_Joystick *joy;
};

int Events::initialize() {
	if (SDL_Init( SDL_INIT_EVERYTHING ) == -1)
		return 0;
	
	joy = SDL_JoystickOpen(0);
	if (!joy) {
		cout << "Could not open Joystick 0" << endl;
		return 0;
	}
	SDL_JoystickEventState(SDL_ENABLE);
	return 1;	
}

int Events::do_something() {
	int temp;
	cout << "1 to continue, 0 to stop: ";
	cin >> temp;
	return temp;
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
void Events::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_JOYAXISMOTION:
				cout << "JOYSTICK: AXIS" << endl;
				cout << "   EVENT: ";
				if (event.jaxis.axis == 0)
					if (event.jaxis.value < 0) cout << "RIGHT";
					else if (event.jaxis.value > 0) cout << "LEFT";
					else cout << "CENTERED";
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
				if (event.jbutton.button == 1) cout << "A";
				else if (event.jbutton.button == 2) cout << "B";
				else if (event.jbutton.button == 8) cout << "SELECT";
				else if (event.jbutton.button == 9) cout << "START";
				else cout << "MISSINGNO";
		
				if (event.jbutton.state == SDL_PRESSED) cout << " PRESSED";
				else cout << " RELEASED";
					cout << endl;					
			break;
		}
	}
}

#endif
