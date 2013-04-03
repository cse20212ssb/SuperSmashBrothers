#include "Platform.h"

using namespace std;


Platform::Platform(int x,int y, int h, int w) : Entity (x, y, h, w) {
	//sprite = SDL_LoadBMP("BLAHBLAH");
}

void Platform::drawTo(SDL_Surface *surf) {
}
