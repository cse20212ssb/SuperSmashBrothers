#ifndef TIME_CONTROL_H
#define TIME_CONTROL_H

#include <SDL/SDL.h>

class TimeControl {
	public:
		TimeControl();
		void update();
		double getValue();
		int accumulate();
	private:
		double dt;
		double t;
		double current_time;
		double accumulator;
};

#endif
