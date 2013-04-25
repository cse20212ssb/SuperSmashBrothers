#ifndef CHARSELECT_H
#define CHARSELECT_H

#include <SDL/SDL.h>

struct node {
	int index;
	node *right;
	node *left;
	node *up;
	node *down;
};

class CharSelect {
	public:
		CharSelect ();
		void toRight() {head = head->right;}
		void toLeft(){head = head->left;}
		void toUp() {head = head->up;}
		void toDown() {head = head->down;}
		int select();
		void draw();
		
	private:
		SDL_Surface *sprite;
		SDL_Surface *screen;
		SDL_Surface *map;
		node *collection[12];
		node *root;
		node *head;
};

int CharSelect::select() {
	return head->index;
}	

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

CharSelect::CharSelect() {
	map = SDL_LoadBMP("./CharSelect.bmp");
	sprite = SDL_LoadBMP("./Selection.bmp");
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 0) );

	screen = SDL_SetVideoMode(600, 200, 32, SDL_HWSURFACE);
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

#endif		