#include "CharSelect.h"

using namespace std;

void CharSelect::draw() {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 100;
	src.h = 100;

	SDL_Rect dst;
	dst.x = head->index % 6 * 100;
	dst.y = head->index / 6 * 100;
	dst.w = 0;
	dst.h = 0;

	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(map, NULL, screen, NULL);
	SDL_BlitSurface(sprite, &src, screen, &dst);
	SDL_Flip(screen);
}

CharSelect::CharSelect(SDL_Surface *surf) {
	sel = -1;
	map = SDL_LoadBMP("Images/CharSelect.bmp");
	sprite = SDL_LoadBMP("Images/Selection.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );

	screen = surf;
	/*
	__________________________________
	| Megaman  | Ch_B     | Ch_C     |
	|__________|__________|__________|
	| Ch_A     |...	      |...       |
	|__________|__________|__________|

	If head points at Megaman,
		head->right points to Ch_B
		head->left points to Ch_C
		head->up points to Ch_A
		head->down points to Ch_A
	*/

	for (int i = 0; i < 12; i++) {
		collection[i] = new node;
		collection[i]->index = i;
	}
	for (int i = 0; i < 12; i++) {
		collection[i]->right = collection[(i+1) % 12];
		if (i == 0)
			collection[i]->left = collection[11];
		else
			collection[i]->left = collection[i-1];
		collection[i]->down = collection[(i+6) % 12];
		if (i < 6)
			collection[i]->up = collection[i+6];
		else
			collection[i]->up = collection[i-6];
	}
	head = collection[0];
	root = collection[0];
}
