#!/bin/bash

for f in Base* Entity* Events* main.cpp Mega* Plat* Proj* SSB*
do
	sed -i 's/\/\/#include <SDL\/SDL.h>/#include <SDL\/SDL.h>/g' $f
	sed -i 's/#include "stdafx.h"/\/\/#include "stdafx.h"/g' $f
	sed -i 's/#include "SDL.h"/\/\/#include "SDL.h"/g' $f
done
