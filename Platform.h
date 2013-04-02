#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public Entity {
	public:
		Platform(int x, int y, int h, int w);
};

Platform::Platform(int x,int y, int h, int w) : Entity (x, y, h, w) {
	//sprite = SDL_LoadBMP("BLAHBLAH");
}
					
#endif PLATFORM_H
