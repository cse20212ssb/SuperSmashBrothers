#include "stdafx.h"
#include "SSB.h"
#include <iostream>

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


	screen = SDL_SetVideoMode(800, 550, 32, SDL_HWSURFACE);
	map = SDL_LoadBMP("Images/Maps/Battlefield.bmp");

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
	Platform *pf0 = new Platform(150, 400 , 400, 20, 1);
	//Floating Platforms
	Platform *pf1 = new Platform(160, 310, 154, 28, 0);
	Platform *pf2 = new Platform(480, 310, 154, 28, 0);
	Platform *pf3 = new Platform(325, 235, 154, 28, 0);
	Platform *pf4 = new Platform(150, 150, 154, 28, 0);
	Platform *pf5 = new Platform(550, 150, 154, 28, 0);
	
	player0 = new Megaman(330, 50);
	player1 = new Megaman(430, 50);
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
		for (int j = 0; j < ptr0.size(); j++) {
			if (ptr0[j]->collides(entityList[i]) && entityList[i] != player0)
				queue.addCollision(entityList[i], ptr0[j]);
		}

		//Player 2 Projectiles
		for (int j = 0; j < ptr1.size(); j++) {
			if (ptr1[j]->collides(entityList[i]) && entityList[i] != player0)
				queue.addCollision(entityList[i], ptr1[j]);
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
