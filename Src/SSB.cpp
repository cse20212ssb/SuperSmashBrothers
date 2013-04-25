#include "stdafx.h"
#include "SSB.h"
#include <iostream>

using namespace std;

void SSB::execute() {
	if (init()) {
		select();
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

void SSB::select() {
	if (js_0) {
		while (sel->isDone() < 0) {
			queue.resolveSel();
			sel->draw();
		}

		//Case statement with isDone to load character
	}

	if (js_1) {
		while (sel->isDone() < 0) {
			queue.resolveSel();
			sel->draw();
		}

		//Case statement with isDone to load character
	}
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

	//Large base platform
	Platform *pf0 = new Platform(200, 300, 20, 400, 1);
	//Floating Platforms
	//Platform *pf1 = new Platform(150, 300, 200, 20, 0);
	//Platform *pf2 = new Platform(250, 300, 200, 20, 0);
	//Platform *pf3 = new Platform(175, 250, 200, 20, 0);
	//Platform *pf4 = new Platform(50, 150, 200, 20, 0);
	//Platform *pf5 = new Platform(300, 150, 200, 20, 0);
	
	player0 = new Megaman(330, 50);
	player1 = new Megaman(430, 50);

	sel = new CharSelect(screen);

	//Loads players and CharSelect to the events class
	queue.add(player0, player1, sel);
	
	//Holds all entities created
	entityList.push_back(player0);
	entityList.push_back(player1);
	entityList.push_back(pf0);
	//entityList.push_back(pf1);
	//entityList.push_back(pf2);
	//entityList.push_back(pf3);
	//entityList.push_back(pf4);
	//entityList.push_back(pf5);
	return 1;
}

int SSB::events() {
	return queue.resolve();
}

//Update everything
void SSB::loop() {	
	//Variables for projectile collision
	vector<Entity*> ptr0 = player0->getProjectileList();
	vector<Entity*> ptr1 = player1->getProjectileList();

	player0->move(); //Also moves projectiles belonging to player0
	player1->move(); 

	//Check for collisions
	for (int i = 0; i < entityList.size(); i++) {
		//Platforms and characters
		for (int j = i + 1; j < entityList.size(); j++) {
			if (entityList[i]->collides(entityList[j])) 
				queue.addCollision(entityList[i], entityList[j]);
		}

		//Player 1 Projectiles
		if (entityList[i] != player0) {
			for (int j = 0; j < ptr0.size(); j++) {
				if (ptr0[j]->collides(entityList[i]))
					queue.addCollision(entityList[i], ptr0[j]);
			}
		}

		//Player 2 Projectiles
		if (entityList[i] != player1) {
			for (int j = 0; j < ptr1.size(); j++) {
				if (ptr1[j]->collides(entityList[i]))
					queue.addCollision(entityList[i], ptr1[j]);
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
