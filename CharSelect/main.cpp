#include <SDL/SDL.h>
#include <iostream>
#include "CharSelect.h"

using namespace std;

int main() {
	SDL_Init( SDL_INIT_EVERYTHING );
 	SDL_SetVideoMode(600, 200, 0, 0 );

	CharSelect *sel = new CharSelect();

	SDL_Event event;
        int quit = 0;

        /* Loop until an SDL_QUIT event is found */
        while( !quit ){
		 while( SDL_PollEvent( &event ) ){             
                    	if (event.type == SDL_KEYDOWN) {
				switch( event.key.keysym.sym ){
					case SDLK_DOWN:
					sel->toDown();
					break;
		      			case SDLK_UP:
		               		sel->toUp();
					break;
					case SDLK_RIGHT:
					sel->toRight();
					break;
					case SDLK_LEFT:
					sel->toLeft();
					break;
		       			default:
		               		break;
					case SDLK_RETURN:
					cout << sel->select() << endl;
					break;				
				}
                	}
			if (event.type == SDL_QUIT) 
		               	quit = 1;

      		}
		sel->draw();
        }

        SDL_Quit();
	exit( 0 );
}

