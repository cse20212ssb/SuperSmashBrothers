#ifndef JOYSTICK_MAP_H
#define JOYSTICK_MAP_H

#include <SDL/SDL.h>
#include <iostream>

using namespace std;

class joystick_map {
	public:
		joystick_map(){}
		int js_initialize();
		void check_hats();
		void check_buttons();
		
	private:
		SDL_Joystick *joy;
};

void joystick_map::check_buttons() {
	Uint8 input;
	for (int i = 0; i < SDL_JoystickNumButtons(joy); i++) {
		input = SDL_JoystickGetButton(joy, i);
		if (input)
			cout << "Button " << i << " has been pressed" << endl;
	}
}	

void joystick_map::check_hats() {
	Uint8 input = SDL_JoystickGetHat(joy, 0);
	if (input == SDL_HAT_UP)
		cout << "Up hat has been pressed" << endl;
	if (input == SDL_HAT_RIGHT)
		cout << "Right hat has been pressed" << endl;
	if (input == SDL_HAT_LEFT)
		cout << "Left hat has been pressed" << endl;
	if (input == SDL_HAT_DOWN)
		cout << "Down hat has been pressed" << endl;
}

int joystick_map::js_initialize() {
	if (SDL_Init( SDL_INIT_EVERYTHING ) ==  -1)
		return 0;

	int num_joy = SDL_NumJoysticks();
	cout << "Number of joysticks connected: " << num_joy << endl;
	for (int i = 0; i < num_joy; i++) 
		cout << "JoyStick #" << i << ": " << SDL_JoystickName(i) << endl;

	joy = SDL_JoystickOpen(0);

	if (!joy) {
		cout << "Could not open Joystick 0" << endl;
		return 0;
	}
	cout << "Opened Joystick 0" << endl;
	cout << "Number of Axes: " << SDL_JoystickNumAxes(joy) << endl;
	cout << "Number of Hats: " << SDL_JoystickNumHats(joy) << endl;
	cout << "Number of Buttons: " << SDL_JoystickNumButtons(joy) << endl;
	return 1;
}

#endif
