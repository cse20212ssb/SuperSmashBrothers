#include "stdafx.h"
#include "jukeBox.h"

#include "stdafx.h"
#include "SDL.h"
#include "SDL_mixer.h"

jukeBox::jukeBox(void)
{
}


void jukeBox::load(int musicID){
	//Load the music
	music = Mix_LoadMUS("Feint - My Sunset.mp3");

	//Load the sound effects
    //scratch = Mix_LoadWAV( "scratch.wav" );
    //high = Mix_LoadWAV( "high.wav" );
    //med = Mix_LoadWAV( "medium.wav" );
    //low = Mix_LoadWAV( "low.wav" );
}

void jukeBox::play(int selection){

}

void jukeBox::clean_up(){
	/*
	//Free the sound effects
    Mix_FreeChunk( scratch );
    Mix_FreeChunk( high );
    Mix_FreeChunk( med );
    Mix_FreeChunk( low );
    */

    //Free the music
    Mix_FreeMusic( music );
    
    //Quit SDL_mixer
    Mix_CloseAudio();
}