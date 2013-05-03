#include "Jukebox.h"

using namespace std;

Jukebox::Jukebox() {
}

Jukebox::~Jukebox() {
	Mix_FreeChunk(sound0);
	Mix_FreeChunk(sound1);
	Mix_FreeChunk(sound2);
	Mix_FreeChunk(sound3);
	Mix_FreeMusic(background);
}	

void Jukebox::load(const char *musicFile) {
	background = Mix_LoadMUS(musicFile);
	sound0 = NULL;
	sound1 = NULL;
	sound2 = NULL;
	sound3 = NULL;
}

void Jukebox::load(const char *s0, const char *s1, const char *s2, const char *s3) {
	sound0 = Mix_LoadWAV(s0);
	sound1 = Mix_LoadWAV(s1);
	sound2 = Mix_LoadWAV(s2);
	sound3 = Mix_LoadWAV(s3);
}

void Jukebox::play(int ID) {
	switch (ID) {
		case (-1):
			Mix_PlayMusic(background, -1);
			break;
		case (0):
			Mix_PlayChannel(-1, sound0, 0);
			break;
		case (1):
			Mix_PlayChannel(-1, sound1, 0);
			break;
		case (2):
			Mix_PlayChannel(-1, sound2, 0);
			break;
		case (3):
			Mix_PlayChannel(-1, sound3, 0);
			break;
	}
}
