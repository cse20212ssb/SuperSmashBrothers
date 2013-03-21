/* Basic HitBox class to be linked with character objects

USAGE:
class _Character Name_ {
	public: 
		int getLength() {return length;}
		...
	private:
		HitBox<_Character Name_> hb;
		int length;
		...
}

//Default Constructor
	hb = HitBox<_Character Name_> (*this)

*/


#ifndef HITBOX_H
#define HITBOX_H

using namespace std;

template<typename T>
class HitBox {
	public:
		HitBox() {}
		HitBox(T &name);
		//Add functions here that deal with the hitbox
	private:
		//Add members
		//int botBorder;
};

//Constructor
template<typename T>
HitBox<T>::HitBox(T &name) {
	//Add stuff here
	//botBorder = name.getLength();
}

#endif
