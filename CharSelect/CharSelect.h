#ifndef CHARSELECT_H
#define CHARSELECT_H

struct node {
	int charIndex;
	node *right;
	node *left;
	node *up;
	node *down;
}

class CharSelect {
	public:
		CharSelect () {};
	private:
		node *head;
		node *root;
};

CharSelect::CharSelect() {
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

	//Here goes the list population, meaningless to do now with only one playable character
}

#endif		
