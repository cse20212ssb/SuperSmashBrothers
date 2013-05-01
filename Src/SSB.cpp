#include "stdafx.h"
#include "SSB.h"
#include <iostream>

using namespace std;

void SSB::execute() {
	if (init()) {
		cout << "Init clear" << endl;
		select();
		//Main game loop
		int running = 1;
		while (running) {
			fps_control();
			running = events();
			loop();
			render();
		}
		cleanUp();
	}
	else cout << "SSB init failed" << endl;

	SDL_Quit();
}

void SSB::fps_control() {
	if (nextTick > SDL_GetTicks()) 
		SDL_Delay(nextTick - SDL_GetTicks());
	nextTick = SDL_GetTicks() + 1000 / FPS;
}
	

void SSB::select() {
	startSel = new startScreen(screen);
	cout << "Start screen cleared" << endl;
	sel = new CharSelect(screen);
	cout << "CharSel clear" << endl;
	mapSel = new MapSelect(screen);
	cout << "Selection objects cleared" << endl;

	queue.addSel(startSel, sel, mapSel);
	while(startSel->isDone() < 0){
		queue.resolveStartSel();
		startSel->draw();
	}


	//Change to or later
	while (!sel->isConfirm(0) && !sel->isConfirm(1)) {
		queue.resolveCharSelect();
		sel->draw();
	}

	while(mapSel->isDone() < 0){
		queue.resolveMapSel();
		mapSel->draw();
	}

	//If statement with mapSelect's isDone to load map
	if(mapSel->isDone() == 0)
		map = SDL_LoadBMP("Images/Maps/FinalDest.bmp");
	else
		map = SDL_LoadBMP("Images/Maps/Battlefield.bmp");
	
	//Establish the platforms depending on map selected
	if(mapSel->isDone() == 0)
		entityList.push_back(new Platform(50, 400 , 20, 700, 1));
	else{
		entityList.push_back(new Platform(145, 400 ,20, 400, 1));
		entityList.push_back(new Platform(160, 310, 28, 154, 0));
		entityList.push_back(new Platform(480, 310, 28, 154, 0));
		entityList.push_back(new Platform(325, 235, 28, 154, 0));
		entityList.push_back(new Platform(155, 125, 28, 154, 0));
		entityList.push_back(new Platform(555, 125, 28, 154, 0));
	}

	if(sel->returnIndex(0) == 0)
		player0 = new Megaman(330, 50);
	else if(sel->returnIndex(0) == 1)
		player0 = new BigSmoke(330, 50);
	else if(sel->returnIndex(0) == 3)
		player0 = new Firebat(330, 50);
	else
		player0 = new Megaman(330, 50);

	if(sel->returnIndex(1) == 0)
		player1 = new Megaman(430, 50);
	else if(sel->returnIndex(1) == 1)
		player1 = new BigSmoke(430, 50);
	else if(sel->returnIndex(1) == 3)
		player1 = new Firebat(430, 50);
	else
		player1 = new Megaman(430, 50);

	//Loads players and CharSelect to the events class
	queue.add(player0, player1);
	
	entityList.push_back(player0);
	entityList.push_back(player1);
}

int SSB::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cout << "SDL init failed" << endl;
		return 0;
	}

	screen = SDL_SetVideoMode(800, 550, 32, SDL_HWSURFACE);

	if (screen == NULL) {
		cout << "Screen init failed" << endl;
		return 0;
	}

	FPS = 60;
	nextTick = 0;

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
	vector<Entity*> mPtr0 = player0->getMeleeList();
	vector<Entity*> mPtr1 = player1->getMeleeList();

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
			if (ptr1[j]->collides(entityList[i]) && entityList[i] != player1)
				queue.addCollision(entityList[i], ptr1[j]);
		}

		//Player 1 Melee
		for (int j = 0; j < mPtr0.size(); j++) {
			if (mPtr0[j]->collides(entityList[i]) && entityList[i] != player0)
				queue.addCollision(entityList[i], mPtr0[j]);
		}

		//Player 2 Melee
		for (int j = 0; j < mPtr1.size(); j++) {
			if (mPtr1[j]->collides(entityList[i]) && entityList[i] != player1)
				queue.addCollision(entityList[i], mPtr1[j]);
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