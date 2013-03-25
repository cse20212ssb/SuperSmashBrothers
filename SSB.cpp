// SuperSmashBrothers.cpp : Defines the entry point for the console application.
//Test

//#include <SDL/SDL.h>

#include "stdafx.h"
#include "SDL.h"
#include "BaseCharacter.h"
#include "Megaman.h"
#include "Link.h"

//Declare basic SDL variables
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Event event;

//Establish variable to determine if the window is running
bool running = true; 

//Function to create surfaces
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	//Rectangle for positioning
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	//Placing the surface
	SDL_BlitSurface(source,NULL, destination,&rect);
}

//Function to draw sprites
void draw_sprite(int srcX, int srcY, int dstX, 
				 int dstY, int width, int height, 
				 SDL_Surface* source, SDL_Surface* destination){
	SDL_Rect src;
	src.x = srcX;
	src.y = srcY;
	src.w = width;
	src.h = height;

	SDL_Rect dst;
	dst.x = dstX;
	dst.y = dstY;
	dst.w = width;
	dst.h = height;

	SDL_BlitSurface(source, &src, destination, &dst);
}

int main(int argc, char* argv[]){
	//Initialization
	SDL_Init(SDL_INIT_VIDEO);
	
	//To register holding down a key
	bool keys[323] = {false};

	//Load Items
	screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
	background = SDL_LoadBMP("Images/Maps/FinalDest.bmp");
	Megaman p1; 

	/*How would I do something like this?
	int charSel = 1;
	if(charSel == 1)
		Megaman p1; 
	else
		Link p1;
	*/
	

	//Game loop
	while (running){
		if(SDL_PollEvent(&event)){
			//Check for exit
			if(event.type == SDL_QUIT){
				running = false;
			}

			//Register key being held down
			if(event.type == SDL_KEYDOWN){
				keys[event.key.keysym.sym] = true;
			}

			//Register key being released
			if(event.type == SDL_KEYUP){
				keys[event.key.keysym.sym] = false;
				p1.stopMove();
			}
		}
		

		//Move left correspondingly
		if(keys[SDLK_LEFT]){
			p1.moveLeft();
		}

		//Move right correspondingly
		if(keys[SDLK_RIGHT]){
			p1.moveRight();
		}

		//Make the sprite transparent
		SDL_SetColorKey(p1.getSprite(),SDL_SRCCOLORKEY,SDL_MapRGB(p1.getSprite()->format, 255, 255, 255));

		//Apply surfaces
		apply_surface(0,0,background,screen); //Background onto the screen
		draw_sprite(p1.getSrcX(),p1.getSrcY(),p1.getDstX(),p1.getDstY(),p1.getWidth(),p1.getHeight(),p1.getSprite(),screen);

		//Update screen
		SDL_Flip(screen);
	}

	SDL_Quit();
	return 0;
}