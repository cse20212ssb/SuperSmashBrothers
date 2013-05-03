/* CharSelect class

This is the CharSelect class, which is utilized for determining which character each player selected. This is the 
cpp implementation for the class. The non-default contructor, draw, and deconstructor functions are defined here.
They are elaborated on below.

*/

//#include "stdafx.h"
#include "CharSelect.h"
#include <iostream>

using namespace std;

void CharSelect::tryIsDone() {
	if (isConfirm_0 && isConfirm_1)
		done = 1;
	else done = 0;
}

void CharSelect::toggle(int t) {
	//If the player has confirmed, but the A button is pressed again, then the confirmation is cancelled
	//The if else is for determining which character is pressing the button
	if (t == 0) {
		if (!isConfirm_0)
			intros.play(head_0->index);
		isConfirm_0 = !isConfirm_0;
	}
	else {
		if (!isConfirm_1)
			intros.play(head_1->index);
		isConfirm_1 = !isConfirm_1;
	}
}

//This returns the index, i.e. character selected, of the player. The index is used to determine which
		//player's selection is being called for
int CharSelect::isConfirm(int t) {
	if (t == 0) 
		return isConfirm_0;
	return isConfirm_1;
}

int CharSelect::returnIndex(int index) {
	if (index == 0)
		return head_0->index;
	return head_1->index;
}

//This is the draw function which is used to blit the charSelect.bmp established in the
//constructor on the screen. It also draws the sprite for the selection box.

void CharSelect::draw() {
	SDL_Rect boxes;
	boxes.x = 0;
	boxes.y = 0;
	boxes.w = 0;
	boxes.h = 0;


	//Player 1's selection area
	SDL_Rect selDst_0;
	//Draw the selection box in the appropriate area by multiplying the current index by 200 since the box is 400X400
	selDst_0.x = (head_0->index % 2) * 200; 
	selDst_0.y = (head_0->index / 2) * 200;
	selDst_0.w = 0;
	selDst_0.h = 0;
	SDL_Rect selSrc_0;
	//Draw the confirmation box in the appropriate location
	selSrc_0.x = 200 * isConfirm_0;
	selSrc_0.y = 0;
	selSrc_0.w = 200;
	selSrc_0.h = 200;
	
	//Player 2's selection area
	SDL_Rect selDst_1;
	//Draw the selection box in the appropriate area by multiplying the current index by 200 since the box is 400X400
	selDst_1.x = (head_1->index % 2) * 200 + 400;
	selDst_1.y = (head_1->index / 2) * 200;
	selDst_1.w = 0;
	selDst_1.h = 0;
	SDL_Rect selSrc_1;
	//Draw the confirmation box in the appropriate location
	selSrc_1.x = 200 * isConfirm_1;
	selSrc_1.y = 0;
	selSrc_1.w = 200;
	selSrc_1.h = 200;
	

	SDL_FillRect(screen, NULL, 0);

	SDL_BlitSurface(boxes_sprite, NULL, screen, &boxes);
	SDL_BlitSurface(sel_sprite, &selSrc_0, screen, &selDst_0);
	SDL_BlitSurface(sel_sprite, &selSrc_1, screen, &selDst_1);

	SDL_Flip(screen);
}

CharSelect::CharSelect(SDL_Surface *surf) {
	done = 0;
	isConfirm_0 = 0;
	isConfirm_1 = 0;
	boxes_sprite = SDL_LoadBMP("Images/Misc/CharSelect.bmp");
	sel_sprite = SDL_LoadBMP("Images/Misc/CharSelBox.bmp");
	SDL_SetColorKey(sel_sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sel_sprite->format, 255, 0, 0) );

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

	for (int i = 0; i < 4; i++) {
		collection[i] = new node;
		collection[i]->index = i;
	}
	for (int i = 0; i < 4; i++) {
		collection[i]->right = collection[(i+1) % 4];
		if (i == 0)
			collection[i]->left = collection[3];
		else
			collection[i]->left = collection[i-1];
		collection[i]->down = collection[(i+2) % 4];
		if (i < 2)
			collection[i]->up = collection[i+2];
		else
			collection[i]->up = collection[i-2];
	}
	head_0 = collection[0];
	head_1 = collection[0];
	root = collection[0];

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	intros.load("Sounds/CharSelect/Megaman.wav" , "Sounds/CharSelect/ForDaGrove.wav", "Sounds/CharSelect/NDfight.wav", "Sounds/CharSelect/firebat.wav");
}

CharSelect::~CharSelect() {
	cout << "Closing charSelect" << endl;
	SDL_FreeSurface(boxes_sprite);
	SDL_FreeSurface(sel_sprite);
	Mix_CloseAudio();
	cout << "Closed" << endl;
}
