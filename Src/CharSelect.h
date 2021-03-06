/* CharSelect class

This is the CharSelect class, which is utilized for determining which character each player selected. This is the 
header file for the class. The struct node, which is used produces a quadruply linked list, is declared here. It
contains the index, which is used to determine the current position of the cursor, and each of the locations of the
character portraits. The toRight, toLeft, toUp, and toDown functions are defined in this header file. These are used
to register the NES controller's button presses and move the cursor to the appropriate location. The toggle and
isConfirm functions are also defined here. These determine which player is selecting a character and whether a
user has selected a character.

*/


#ifndef CHARSELECT_H
#define CHARSELECT_H

#include <SDL/SDL.h>
//#include "SDL.h"
//#include "stdafx.h"
#include <iostream>
#include "Jukebox.h"

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
		CharSelect(); //Constructor (not utilized)
		CharSelect(SDL_Surface *); //Non-default contructor that accepts the surface to be drawn upon (it is the screen)
		~CharSelect(); //Deconstructor used to delete the memory from producing the boxes and list

		//These functions move the cursor. They do this by determining the current location and which player is
		//being called. It then moves the head to that location in the list
		//This moves the cursor to the right
		void toRight(int which) {if (which == 1) head_1 = head_1->right; else head_0 = head_0->right;}
		//This moves the cursor to the left
		void toLeft(int which){if (which == 1) head_1 = head_1->left; else head_0 = head_0->left;}
		//This moves the cursor upward
		void toUp(int which) {if (which == 1) head_1 = head_1->up; else head_0 = head_0->up;}
		//This moves the cursor downward
		void toDown(int which) {if (which == 1) head_1 = head_1->down; else head_0 = head_0->down;}
		int isDone() {return done;}
		void toggle(int);//This determines which player has confirmed a character and allows cancelling of confirmation
		int isConfirm(int);//This returns the isConfirm variable based on the inputted character
		int returnIndex(int);
		void tryIsDone();
		void draw();//This function displays the character select image on the screen
		

	private:
		//Holds all character intros
		Jukebox intros;
		int done;

		SDL_Surface *sel_sprite; //Determines which sprite has been selected
		SDL_Surface *screen; //Variable for printing the screen
		SDL_Surface *boxes_sprite; //This is for the selection box
		//Variables for the quadruply list
		node *collection[4]; 
		node *root;
		node *head_0;
		node *head_1;
		//Variables for determining whether players have finished their confirmation and selection
		int isConfirm_0;
		int isConfirm_1;
		int selection;
		
};	

#endif
