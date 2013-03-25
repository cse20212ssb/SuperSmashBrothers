#include "stdafx.h"
#include "BaseCharacter.h"


BaseCharacter::BaseCharacter(){
}

SDL_Surface *BaseCharacter::getSprite(){return sprite;};

int BaseCharacter::getHeight(){return 0;};

int BaseCharacter::getWidth(){return 0;};

int BaseCharacter::getSrcX(){return 0;};

int BaseCharacter::getSrcY(){return 0;};

int BaseCharacter::getDstX(){return 0;};

int BaseCharacter::getDstY(){return 0;};

void BaseCharacter::moveLeft(){};

void BaseCharacter::moveRight(){};

void BaseCharacter::jump(){};

void BaseCharacter::leftAtk(){};

void BaseCharacter::rightAtk(){};

void BaseCharacter::upAtk(){};

void BaseCharacter::downAtk(){};

void BaseCharacter::specialAtk(){};

void BaseCharacter::checkPosition(){};

void BaseCharacter::animate(string action){};