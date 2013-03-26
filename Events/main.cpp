#include <SDL/SDL.h>
#include "Events.h" 

using namespace std;

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		cout << "SDL failed to initialize" << endl;
	Events evt;
	SDL_Joystick *joy;
	joy = SDL_JoystickOpen(0);
	if (!joy)
		cout << "Joystick failed to initialize" << endl;
	while (evt.resolve());
	return 1;
}
