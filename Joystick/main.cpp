#include "joystick_map.h"

using namespace std;

int main() {
	joystick_map joy;
	if (joy.js_initialize() == 1) {
		while (1) {
			joy.check_axis();
			joy.check_buttons();
		}
	}
	return 1;
}
