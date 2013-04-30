SDL=`sdl-config --libs`

OBJ=main.o SSB.o Events.o BaseCharacter.o Megaman.o Entity.o Platform.o Projectile.o CharSelect.o Melee.o MapSelect.o

all:	main

main:	script $(OBJ)
	g++ $(SDL) $(OBJ) -o main

script:

%.o:	%.cpp
	g++ $(SDL) -c $<


clean:
	rm -f *.o *~ main
	rm -f */*~
