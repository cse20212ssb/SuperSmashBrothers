#ifndef CHARSELECT_H
#define CHARSELECT_H

#include <SDL/SDL.h>
//#include "SDL.h"
//#include "stdafx.h"
#include <iostream>

using namespace std;

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
		~CharSelect();
		void toRight(int which) {if (which == 1) head_1 = head_1->right; else head_0 = head_0->right;}
		void toLeft(int which){if (which == 1) head_1 = head_1->left; else head_0 = head_0->left;}
		void toUp(int which) {if (which == 1) head_1 = head_1->up; else head_0 = head_0->up;}
		void toDown(int which) {if (which == 1) head_1 = head_1->down; else head_0 = head_0->down;}

		void draw();
		void toggle(int t) {
			if (t == 0)
				isConfirm_0 = !isConfirm_0;
			else
				isConfirm_1 = !isConfirm_1;
			cout << "sel 0: " << returnIndex(0) << endl;
			cout << "sel 1: " << returnIndex(1) << endl;
		};

		int isConfirm(int t) {
			if (t == 0) 
				return isConfirm_0;
			return isConfirm_1;
		}
		int returnIndex(int index) {
			if (index == 0)
					return head_0->index;
			return head_1->index;
		}

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
		int selection;
};	

#endif
