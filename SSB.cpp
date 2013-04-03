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

	screen = SDL_SetVideoMode(800, 400, 32, SDL_HWSURFACE);
	map = SDL_LoadBMP("Images/Maps/basic.bmp");

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

	pf = new Platform (100, 300 , 20, 400);

	//BaseCharacter*
	player = new Megaman(100, 50);
	queue.add(player);

	entityList[0] = player;
	entityList[1] = pf;
	
	return 1;
}

int SSB::events() {
	return queue.resolve();
}

void SSB::loop() {
	//Everything else
	player->move();
	player->update();

	for (int i = 0; i < 2; i++) {
		for (int j = i + 1; j < 2; j++) {
			if (entityList[i]->collides(entityList[j])) {
				queue.addCollision(entityList[i], entityList[j]);
			}
		}
	}
}

void SSB::render() {
	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);

	player->drawTo(screen);
	pf->drawTo(screen);

	SDL_Flip(screen);
}

void SSB::cleanUp() {
	delete screen, map, js_1, js_2, player;
}
