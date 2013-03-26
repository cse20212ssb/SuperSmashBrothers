SDL=`sdl-config --libs`
OBJ=main.o Events.o Megaman.o BaseCharacter.o SSB.o
EVENTS=./Events/Events

all:	main

main:	$(OBJ)
	g++ $(SDL) $(OBJ) -o main

main.o:	main.cpp
	g++ main.cpp -c

SSB.o:	SSB.cpp
	g++ $(SDL) SSB.cpp -c

Events.o: $(EVENTS).cpp
	g++ $(SDL) $(EVENTS).cpp -c

Megaman.o: Megaman.cpp
	g++ $(SDL) Megaman.cpp -c

BaseCharacter.o: BaseCharacter.cpp
	g++ $(SDL) BaseCharacter.cpp -c

clean:
	rm -f *.o *~ main
