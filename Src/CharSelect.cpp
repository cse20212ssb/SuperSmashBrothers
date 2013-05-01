#include "stdafx.h"
#include "CharSelect.h"

using namespace std;

/*
>>>>>>> BigSmoke
int CharSelect::isConfirm(int t) {
	if (t == 0) 
		return isConfirm_0;
	return isConfirm_1;
}

void CharSelect::toggle(int t) {
	if (t == 0)
		isConfirm_0 = !isConfirm_0;
	else
		isConfirm_1 = !isConfirm_1;
}
*/
void CharSelect::draw() {
	SDL_Rect boxes_0;
	boxes_0.x = 0;
	boxes_0.y = 0;
	boxes_0.w = 0;
	boxes_0.h = 0;
	SDL_Rect boxes_1;
	boxes_1.x = 400;
	boxes_1.y = 0;
	boxes_1.w = 0;
	boxes_1.h = 0;

	SDL_Rect selDst_0;
	selDst_0.x = (head_0->index % 2) * 200;
	selDst_0.y = (head_0->index / 2) * 200;
	selDst_0.w = 0;
	selDst_0.h = 0;
	SDL_Rect selSrc_0;
	selSrc_0.x = 200 * isConfirm_0;
	selSrc_0.y = 0;
	selSrc_0.w = 200;
	selSrc_0.h = 200;
	
	SDL_Rect selDst_1;
	selDst_1.x = (head_1->index % 2) * 200 + 400;
	selDst_1.y = (head_1->index / 2) * 200;
	selDst_1.w = 0;
	selDst_1.h = 0;
	SDL_Rect selSrc_1;
	selSrc_1.x = 200 * isConfirm_1;
	selSrc_1.y = 0;
	selSrc_1.w = 200;
	selSrc_1.h = 200;
	

	SDL_FillRect(screen, NULL, 0);

	SDL_BlitSurface(boxes_sprite, NULL, screen, &boxes_0);
	SDL_BlitSurface(boxes_sprite, NULL, screen, &boxes_1);
	SDL_BlitSurface(sel_sprite, &selSrc_0, screen, &selDst_0);
	SDL_BlitSurface(sel_sprite, &selSrc_1, screen, &selDst_1);

	SDL_Flip(screen);
}

CharSelect::CharSelect(SDL_Surface *surf) {
	isConfirm_0 = 0;
	isConfirm_1 = 0;
	boxes_sprite = SDL_LoadBMP("Images/Misc/CharSelect.bmp");
	sel_sprite = SDL_LoadBMP("Images/Misc/Selection.bmp");
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
}

CharSelect::~CharSelect() {
	SDL_FreeSurface(boxes_sprite);
	SDL_FreeSurface(sel_sprite);
	delete [] collection;
}
