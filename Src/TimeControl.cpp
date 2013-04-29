#include "SDL.h"
#include "stdafx.h"
#include "TimeControl.h"
#include <iostream>

using namespace std;

TimeControl::TimeControl() {
	dt = 0.01;
	t = 0;
	current_time = SDL_GetTicks() / 1000;
	accumulator = 0.0;
}

void TimeControl::update() {
	double new_time = SDL_GetTicks() / 1000;
	double frame_time = new_time - current_time;
	current_time = new_time;
	
	cout << accumulator << endl;
	accumulator += frame_time;	
}

double TimeControl::getValue() {
	cout << t << endl;
	return t;
}

int TimeControl::accumulate() {
	accumulator -= dt;
	t += dt;
	if (accumulator >= dt)
		return 1;
	return 0;
}
