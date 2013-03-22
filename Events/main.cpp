#include "Events.h" 

using namespace std;

int main() {
	Events evt;
	if (evt.initialize())
		while (evt.do_something())
			evt.handleEvents();
	return 1;
}
