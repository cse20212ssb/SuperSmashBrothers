#ifndef CHARSELECT_H
#define CHARSELECT_H

//#include <SDL/SDL.h>
#include "SDL.h"
#include "stdafx.h"

struct node {
	int index;
	node *right;
	node *left;
	node *up;
	node *down;
};

class CharSelect {
	public:
		CharSelect();
		CharSelect(SDL_Surface *);
		void toRight(int which) {if (which == 1) head_1 = head_1->right; else head_0 = head_0->right;}
		void toLeft(int which){if (which == 1) head_1 = head_1->left; else head_0 = head_0->left;}
		void toUp(int which) {if (which == 1) head_1 = head_1->up; else head_0 = head_0->up;}
		void toDown(int which) {if (which == 1) head_1 = head_1->down; else head_0 = head_0->down;}

		void draw();

		void toggle(int);
		int isConfirm(int);
		
	private:
		SDL_Surface *sel_sprite;
		SDL_Surface *screen;
		SDL_Surface *boxes_sprite;
		node *collection[4];
		node *root;
		node *head_0;
		node *head_1;
		int isConfirm_0;
		int isConfirm_1;
};	

#endif
