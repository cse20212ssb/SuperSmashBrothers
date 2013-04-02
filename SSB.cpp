#include "SSB.h"

using namespace std;

void SSB::execute() {
	if (init()) {
		int running = 1;
		while (running) {
			running = events();
			loop();
			render();
		}
		cleanUp();
	}
	else cout << "SSB init failed" << endl;

	SDL_Quit();
}

int SSB::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cout << "SDL init failed" << endl;
		return 0;
	}

	screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
	map = SDL_LoadBMP("Images/Maps/FinalDest.bmp");

	if (screen == NULL) {
		cout << "Screen init failed" << endl;
		return 0;
	}

	js_1 = SDL_JoystickOpen(0);
	js_2 = SDL_JoystickOpen(1);
	
	if (!js_1) 
		cout << "Joystick 1 failed to init" << endl;
	if (!js_2) 
		cout << "Joystick 2 failed to init" << endl;

	if (!js_1 && !js_2) {
		cout << "No controller was found" << endl;
		return 0;
	}
	//BaseCharacter*
	player = new Megaman();
	queue.add(player);
	
	return 1;
}

int SSB::events() {
	for (int i = 0; i < entityList.size(); i++) {
		for (int j = i + 1; j < entityList.size(); j++) {
			if (entityList[i].collides(entityList[j]) {
				entityList[j].collides(entityList[i];
			}
		}
	}

	return queue.resolve();
}

void SSB::loop() {
	//World events
	player->addYVel(1); //Gravity

	//Everything else
	player->move();
}

void SSB::render() {
	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);

	player->drawTo(screen)

	SDL_Flip(screen);
}

void SSB::cleanUp() {
	delete screen, map, js_1, js_2, player;
}
