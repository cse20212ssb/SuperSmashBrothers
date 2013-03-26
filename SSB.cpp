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

	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
	map = SDL_LoadBMP("Images/background.bmp");

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

int SSB::event() {
	return queue.resolve();
}

void SSB::loop() {
	player->move();
}

void SSB::render() {
	SDL_FillRect(screen, NULL, 0);
	switch(player->getAniCounter()){
		case 2:
			player->setSprite(SDL_LoadBMP("Images/Sprites/Megaman/MegamanR1.bmp"));
			break;
		case 4:
			player->setSprite(SDL_LoadBMP("Images/Sprites/Megaman/MegamanR2.bmp"));
			break;
		case 5: 
			player->setSprite(SDL_LoadBMP("Images/Sprites/Megaman/MegamanR3.bmp"));
			break;
		case 7:
			player->setSprite(SDL_LoadBMP("Images/Sprites/Megaman/MegamanR4.bmp")); 
			break;
		case 9:
			player->setSprite(SDL_LoadBMP("Images/Sprites/Megaman/MegamanR5.bmp"));
			break;
		case 11:
			player->setSprite(SDL_LoadBMP("Images/Sprites/Megaman/MegamanStand.bmp"));
			player->setAniCounter(0);
			break;
	}
	
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = player->getWidth();
	src.h = player->getHeight();

	SDL_Rect dst;
	dst.x = player->getX();
	dst.y = player->getY();
	
	SDL_BlitSurface(player->getSprite(), &src, screen, &dst);
	SDL_BlitSurface(map, NULL, screen, NULL);
	SDL_Flip(screen);
}

void SSB::cleanUp() {
	delete screen, map, js_1, js_2, player;
}
