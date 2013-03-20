// SuperSmashBrothers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//Establish variable to determine if the window is running
	bool running = true;


	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		running = false;
	}

	//Set up screen
	SDL_Surface *screen;
	screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
	
	//Determines if the screen was exited
	if (screen == NULL){
		running = false;
	}

	//Declare SDL variables
	SDL_Event occur; //For event
	SDL_Surface *map; //For map image

	map = SDL_LoadBMP("Images/Maps/FinalDest.bmp");

	//main application loop
	while (running == true){
		SDL_PollEvent(&occur);

		if(occur.type == SDL_QUIT){
			running = false;
		}

		//Draw map
		SDL_FillRect(screen, NULL, 0);
		SDL_BlitSurface(map, NULL, screen, NULL);
		SDL_Flip(screen);
	}

	SDL_Quit();
	return 0;
}
