#ifndef JUKEBOX_H
#define JUKEBOX_H

#include "stdafx.h"

class jukeBox
{
public:
	jukeBox(void);
	void load(int);
	void play(int);
	void clean_up();

private:
	Mix_Music *music;
	//The sound effects that will be used
	Mix_Chunk *punch;
	Mix_Chunk *atk;
	Mix_Chunk *specialAtk;
	Mix_Chunk *downAtk;
	Mix_Chunk *upAtk;
};

#endif