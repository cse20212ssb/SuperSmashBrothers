#ifndef JUKEBOX_H
#define JUKEBOX_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

using namespace std;

class Jukebox {
	public: 
		Jukebox();
		~Jukebox();
		void load(const char *, const char *, const char *, const char *);
		void load(const char *);
		void play(int);		
	
	private:
		Mix_Chunk *atk;
		Mix_Chunk *specialAtk;
		Mix_Chunk *specDown;
		Mix_Chunk *aerial;

		Mix_Music *background;
};

#endif
