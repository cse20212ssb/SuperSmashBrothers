#!/bin/bash

for f in *.cpp *.h
do
	sed -i 's/^#include <SDL\/SDL.h>/\/\/#include <SDL\/SDL.h>/g' $f
	sed -i 's/^\/\/#include "stdafx.h"/#include "stdafx.h"/g' $f
	sed -i 's/^\/\/#include "SDL.h"/#include "SDL.h"/g' $f
done

sed -i 's/event.jaxis.value < 0/event.jaxis.value < -257/g' Events.cpp
sed -i 's/event.jaxis.value > 0/event.jaxis.value > -257/g' Events.cpp
