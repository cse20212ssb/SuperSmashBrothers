#include "stdafx.h"
#include "Events.h"
#include <iostream>

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
					if (event.jaxis.value > -257) {
						select->setMoveDir(1);
					}
					//Left
					else if (event.jaxis.value < -257) {
						select->setMoveDir(-1);
					}
					//Centered
					else {
						select->setMoveDir(0);
						
					}
				}
				//Vertical Movement
				else if (event.jaxis.axis == 1) {
					//Up
					if (event.jaxis.value < -257) {
						if (select->jumpable()) {
							select->jump();
							select->setCanJump(0);
						}
					}
					//Down
					else if (event.jaxis.value > -257) {
						select->fastFallCrouch();
					}
					//Centered
					else {
						select->setCanJump(1);
						//cout << "CENTERED";
					}
				}
			break;
			
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				//Button down
				if (event.jbutton.state == SDL_RELEASED) {
					if (event.jbutton.button == 1){
						//select->releaseAtk();
					}
					if (event.jbutton.button == 2){
						select->releaseSpecialAtk();
					}
				}
				//Button up
				if (event.jbutton.state == SDL_PRESSED) {
					if (event.jbutton.button == 1){
						//select->Atk();
					}
					else if (event.jbutton.button == 2){
						select->specialAtk();
					}


					else if (event.jbutton.button == 8) {}
					else if (event.jbutton.button == 9) {}
					else {} 
				}
				else {
					if (event.jbutton.button == 1) {} 
					else if (event.jbutton.button == 2) {} 
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

