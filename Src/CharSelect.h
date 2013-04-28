#ifndef CHARSELECT_H
#define CHARSELECT_H

////#include <SDL/SDL.h>
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
		void toRight() {head = head->right;}
		void toLeft(){head = head->left;}
		void toUp() {head = head->up;}
		void toDown() {head = head->down;}
		void select() {sel = head->index;}
		int isDone() {return sel;}
		void draw();
		
	private:
		int sel;
		SDL_Surface *sprite;
		SDL_Surface *screen;
		SDL_Surface *map;
		node *collection[12];
		node *root;
		node *head;
};	

#endif
