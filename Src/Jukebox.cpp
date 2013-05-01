#include "Jukebox.h"

using namespace std;

Jukebox::Jukebox() {
}

Jukebox::~Jukebox() {
	Mix_FreeChunk(atk);
	Mix_FreeChunk(specialAtk);
	Mix_FreeChunk(specDown);
	Mix_FreeChunk(aerial);
	Mix_FreeMusic(background);
}	

void Jukebox::load(const char *musicFile) {
	background = Mix_LoadMUS(musicFile);
	atk = NULL;
	specialAtk = NULL;
	specDown = NULL;
	aerial = NULL;
}

void Jukebox::load(const char *atkSound, const char *specialAtkSound, const char *specDownSound, const char *aerialSound) {
	atk = Mix_LoadWAV(atkSound);
	specialAtk = Mix_LoadWAV(specialAtkSound);
	specDown = Mix_LoadWAV(specDownSound);
	aerial = Mix_LoadWAV(aerialSound);
}

void Jukebox::play(int ID) {
	switch (ID) {
		case (-1):
			Mix_PlayMusic(background, -1);
			break;
		case (0):
			Mix_PlayChannel(-1, atk, 0);
			break;
		case (1):
			Mix_PlayChannel(-1, specialAtk, 0);
			break;
		case (2):
			Mix_PlayChannel(-1, specDown, 0);
			break;
		case (3):
			Mix_PlayChannel(-1, aerial, 0);
			break;
	}
}
