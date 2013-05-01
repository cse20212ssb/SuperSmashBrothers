//#include "stdafx.h"
#include "Events.h"
#include <iostream>

using namespace std;

Events::Events() {
	SDL_JoystickEventState(SDL_ENABLE);
}

//Load objects to the Event
void Events::add(BaseCharacter *obj0, BaseCharacter *obj1) {
	player0 = obj0;
	player1 = obj1;
	
}

void Events::addSel(startScreen *obj2, CharSelect *obj3, MapSelect *obj4) {
	startSel = obj2;
	charSel = obj3;
	mapSel = obj4;
}
 

//Pushes collision event to queue
void Events::addCollision(Entity *obj0, Entity *obj1) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	//data type is *void, needs to be typecast
	event.user.data1 = obj0;
	event.user.data2 = obj1;
	
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
	BaseCharacter *select;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			//Joystick axis motion
			case SDL_JOYAXISMOTION:
				if (event.jaxis.which == 0)
					select = player0;
				else
					select = player1;
				//Horizontal movement
				if (event.jaxis.axis == 0) {
					//Right
					if (event.jaxis.value > 0)
						select->setMoveDir(1);
					//Left
					else if (event.jaxis.value < 0)
						select->setMoveDir(-1);
					//Centered
					else 
						select->setMoveDir(0);
				}
				//Vertical Movement
				else if (event.jaxis.axis == 1) {
					//Up
					if (event.jaxis.value < 0) {
						if (select->jumpable()) 
							select->jump();
					}
					//Down
					else if (event.jaxis.value > 0)
						select->fastFall();
					//Centered
					else {}
				}
			break;
			
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:			
				if (event.jbutton.which == 0)
					select = player0;
				else
					select = player1;
				//Button up
				if (event.jbutton.state == SDL_RELEASED) {
					if (event.jbutton.button == 1){
						select->releaseAtk();
						//cout << "BUTTON A RELEASED" << endl;
					}
					if (event.jbutton.button == 2){
						select->releaseSpecialAtk();
						//cout << "Button B RELEASED" << endl;
					}
				}
				//Button down
				if (event.jbutton.state == SDL_PRESSED) {
					if (event.jbutton.button == 1){
						select->Atk();
					}
					else if (event.jbutton.button == 2){
						select->specialAtk();
						//cout << "BUTTON B RELEASED" << endl;
					}


					else if (event.jbutton.button == 8) {}
					else if (event.jbutton.button == 9) {}
					else {} 
				}			
			break;
			
			case SDL_QUIT:
				return 0;
			break;

			//Collision events
			case SDL_USEREVENT:
				//Typecast *void to *Entity
				((Entity *)event.user.data1)->onCollision((Entity *)event.user.data2);
				((Entity *)event.user.data2)->onCollision((Entity *)event.user.data1);
			break; 
		}
	}
	return 1;
}

void Events::resolveCharSelect() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_JOYAXISMOTION:
				if (!charSel->isConfirm(event.jaxis.which)) {
					//Horizontal movement
					if (event.jaxis.axis == 0) {
						//Right
						if (event.jaxis.value > 0) 
							charSel->toRight(event.jaxis.which);
						//Left
						else if (event.jaxis.value < 0)
							charSel->toLeft(event.jaxis.which);
					}
					//Vertical Movement
					else if (event.jaxis.axis == 1) {
						//Up
						if (event.jaxis.value < 0) 
							charSel->toUp(event.jaxis.which);
						//Down
						else if (event.jaxis.value > 0)
							charSel->toDown(event.jaxis.which);
					}
				}
			break;
			
			//Start button
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				if (event.jbutton.state == SDL_PRESSED) {
					if (event.jbutton.button == 1)
						charSel->toggle(event.jbutton.which);
				}		
			break;
		}
	}
}

void Events::resolveMapSel() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_JOYAXISMOTION:
				//Horizontal movement
				if (event.jaxis.axis == 0) {
					//Right
					if (event.jaxis.value > 0) 
						mapSel->toRight();
					//Left
					else if (event.jaxis.value < 0)
						mapSel->toLeft();
				}
			break;
			
			//Start button
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				if (event.jbutton.state == SDL_PRESSED) {
					if (event.jbutton.button == 9)
						mapSel->select();
				}		
			break;
		}
	}
}

void Events::resolveStartSel() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_JOYAXISMOTION:
				//Horizontal movement
				if (event.jaxis.axis == 0) {
				}
			break;
			
			//Start button
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				if (event.jbutton.state == SDL_PRESSED) {
					if (event.jbutton.button == 9)
						startSel->select();
				}		
			break;
		}
	}
}

