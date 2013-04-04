//#include "stdafx.h"
#include "SSB.h"

using namespace std;

void SSB::execute() {
	if (init()) {
		//Main game loop
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

	screen = SDL_SetVideoMode(800, 400, 32, SDL_HWSURFACE);
	map = SDL_LoadBMP("Images/Maps/basic.bmp");

	if (screen == NULL) {
		cout << "Screen init failed" << endl;
		return 0;
	}

	js_0 = SDL_JoystickOpen(0);
	js_1 = SDL_JoystickOpen(1);
	
	if (!js_0) 
		cout << "Joystick 1 failed to init" << endl;
	if (!js_1) 
		cout << "Joystick 2 failed to init" << endl;

	if (!js_0 && !js_1) {
		cout << "No controller was found" << endl;
		return 0;
	}

	Platform *pf0 = new Platform(200, 350 , 20, 400, 1);
	Platform *pf1 = new Platform(250, 250, 20, 100, 0);
	Platform *pf2 = new Platform(450, 250, 20, 100, 0);
	Platform *pf3 = new Platform(350, 150, 20, 100, 0);
	Platform *pf4 = new Platform(50, 100, 20, 100, 0);
	Platform *pf5 = new Platform(650, 100, 20, 100, 0);

	player0 = new Megaman(250, 50);
	player1 = new Megaman(450, 50);
	//Adds players to the events class
	queue.add(player0, player1);
	
	//Holds all entities created
	entityList.push_back(player0);
	entityList.push_back(player1);
	entityList.push_back(pf0);
	entityList.push_back(pf1);
	entityList.push_back(pf2);
	entityList.push_back(pf3);
	entityList.push_back(pf4);
	entityList.push_back(pf5);
	
	return 1;
}

int SSB::events() {
	return queue.resolve();
}

//Update everything
void SSB::loop() {
	player0->move();
	player0->updateBorders();
	player1->move();
	player1->updateBorders();

	for (int i = 0; i < entityList.size(); i++) {
		for (int j = i + 1; j < entityList.size(); j++) {
			if (entityList[i]->collides(entityList[j])) {
				queue.addCollision(entityList[i], entityList[j]);
			}
		}
	}
}

void SSB::render() {
	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);

	for (int i = 0; i < entityList.size(); i++)
		entityList[i]->drawTo(screen);

	SDL_Flip(screen);
}

void SSB::cleanUp() {
	delete screen, map, js_0, js_1;
	for (int i = 0; i < entityList.size(); i++) {
		delete entityList[i];
	}
}
