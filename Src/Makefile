SDL= `sdl-config --libs` -lSDL -lSDL_mixer 

OBJ=main.o SSB.o Events.o BaseCharacter.o Megaman.o Entity.o Projectile.o CharSelect.o Melee.o MapSelect.o BigSmoke.o startScreen.o Jukebox.o Firebat.o Leprechaun.o Platform.o

all:	main

main:	script $(OBJ)
	g++ -o main $(OBJ) $(SDL)

script:

%.o:	%.cpp
	g++ $(SDL) -c $<


clean:
	rm -f *.o *~ main
	rm -f */*~
