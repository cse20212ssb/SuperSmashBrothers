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
		void check_axis();
		
	private:
		SDL_Joystick *joy;

		Sint16 last_state_axis0;
		Sint16 last_state_axis1;

		Sint16 last_state_btn1;
		Sint16 last_state_btn2;
		Sint16 last_state_btn8;
		Sint16 last_state_btn9;
};

/*
Axis #0
Right: -32768
Left: 32767

Axis #1
Up : -32768
Down: 32767
*/
void joystick_map::check_axis() {
	SDL_JoystickUpdate();
	Sint16 current_state_axis0 = SDL_JoystickGetAxis(joy, 0);
	Sint16 current_state_axis1 = SDL_JoystickGetAxis(joy, 1);

	if (current_state_axis0 != last_state_axis0 && current_state_axis0 != 0) 
		if (current_state_axis0 < 0)
			cout << "Left" << endl;
		else if (current_state_axis0 > 0)
			cout << "Right" << endl;

	if (current_state_axis1 != last_state_axis1 && current_state_axis1 != 0)
		if (current_state_axis1 < 0)
			cout << "Up" << endl;
		else if (current_state_axis1 > 0)
			cout << "Down" << endl;

	last_state_axis0 = current_state_axis0;
	last_state_axis1 = current_state_axis1;
}
	

/*
Button 1: A
Button 2: B
Button 8: Select
Button 9: Start
Buttons 0, 3-7 are empty
*/
void joystick_map::check_buttons() {
	SDL_JoystickUpdate();

	Sint16 current_state_btn1 = SDL_JoystickGetButton (joy, 1);
	Sint16 current_state_btn2 = SDL_JoystickGetButton (joy, 2);
	Sint16 current_state_btn8 = SDL_JoystickGetButton (joy, 8);
	Sint16 current_state_btn9 = SDL_JoystickGetButton (joy, 9);

	if (current_state_btn1 != last_state_btn1 && current_state_btn1)
		cout << "A" << endl;
	if (current_state_btn2 != last_state_btn2 && current_state_btn2)
		cout << "B" << endl;
	if (current_state_btn8 != last_state_btn8 && current_state_btn8)
		cout << "Select" << endl;
	if (current_state_btn9 != last_state_btn9 && current_state_btn9)
		cout << "Start" << endl;

	last_state_btn1 = current_state_btn1;
	last_state_btn2 = current_state_btn2;
	last_state_btn8 = current_state_btn8;
	last_state_btn9 = current_state_btn9;	
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
