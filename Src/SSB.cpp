/* SSB class

This is the SSB class, which is utilized for processing all the events of the program. The main file
will run an instance of this class in order to run the program. This class processes the initial setup
of the joystick, goes to the various screens, then loops through the gameplay portion of the program 
until the user exits

*/


//#include "stdafx.h"
#include "SSB.h"
#include <iostream>

using namespace std;

//This is the execute function, which orders all the events in this class together
void SSB::execute() {
	if (init()) {
		cout << "Init clear" << endl;
		select();
		//Main game loop
		int running = 1;
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
		bgMusic.load("Sounds/backgroundMusic.wav");
		bgMusic.play(-1);
		while (running) {
			fps_control();
			running = events();
			loop();
			render();
		}
		Mix_CloseAudio();
		cleanUp();
	}
	else cout << "SSB init failed" << endl;

	SDL_Quit();
}

//This is utilized for standardizing the speed of the program 
void SSB::fps_control() {
	if (nextTick > SDL_GetTicks()) 
		SDL_Delay(nextTick - SDL_GetTicks());
	nextTick = SDL_GetTicks() + 1000 / FPS;
}

//This function is used for the varius selection processes
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
		map = SDL_LoadBMP("Images/Maps/NDStadium.bmp");
	else
		map = SDL_LoadBMP("Images/Maps/SwissAlps.bmp");
	
	//Establish the platforms depending on map selected
	if(mapSel->isDone() == 0)
		entityList.push_back(new Platform(100, 470 , 18, 600));
	else{
		entityList.push_back(new Platform(324, 242, 20, 155));
		entityList.push_back(new Platform(159, 318, 20, 155));
		entityList.push_back(new Platform(480, 318, 20, 155));
		entityList.push_back(new Platform(160, 405, 15, 475));
	}
	cout << "Platform clear" << endl;

	if(sel->returnIndex(0) == 0)
		player0 = new Megaman(300, 200);
	else if(sel->returnIndex(0) == 1)
		player0 = new BigSmoke(300, 200);
	else if(sel->returnIndex(0) == 3)
		player0 = new Firebat(300, 200);
	else
		player0 = new Leprechaun(300, 200);

	if(sel->returnIndex(1) == 0)
		player1 = new Megaman(500, 50);
	else if(sel->returnIndex(1) == 1)
		player1 = new BigSmoke(500, 50);
	else if(sel->returnIndex(1) == 3)
		player1 = new Firebat(500, 50);
	else
		player1 = new Leprechaun(500, 50);

	//Loads players and CharSelect to the events class
	queue.add(player0, player1);
	
	entityList.push_back(player0);
	entityList.push_back(player1);
}

//This is used to establish the screen
int SSB::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cout << "SDL init failed" << endl;
		return 0;
	}

	screen = SDL_SetVideoMode(800, 628, 32, SDL_HWSURFACE);

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
	}
	return 1;
}

//Used to call the resolve function
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

//Draw objects onto the screen
void SSB::render() {
	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);

	for (int i = 0; i < entityList.size(); i++)
		entityList[i]->drawTo(screen);

	SDL_Flip(screen);
}

//Deletes all instances when this goes out of scope
void SSB::cleanUp() {
	//Screen deleted in SDL_Quit
	delete map, js_0, js_1, sel, mapSel;
	cout << "Non-Entity objects deleted" << endl;
	for (int i = 0; i < entityList.size(); i++) {
		cout << i << endl;
		cout << "Object of type " << entityList[i]->getID() << " begin deletion" << endl;
		delete entityList[i];
	}
}
