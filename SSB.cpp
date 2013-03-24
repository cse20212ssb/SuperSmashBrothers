#include "SSB.h"

using namespace std;

void SSB::execute() {
	if (init()) {
		int running = 1;
		while (running) {
			running = event();
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

	screen = SDL_SetVideoMode(400, 300, 32, SDL_HWSURFACE);
	map = SDL_LoadBMP("Images/background.bmp");

	if (screen == NULL) {
		cout << "Screen init failed" << endl;
		return 0;
	}

	js_1 = SDL_JoystickOpen(0);
	js_2 = SDL_JoystickOpen(1);
	return 1;
}

int SSB::event() {
	return queue.resolve();
}

void SSB::loop() {
}

void SSB::render() {
	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);
	SDL_Flip(screen);
}

void SSB::cleanUp() {
	delete screen, map, js_1, js_2;
}
