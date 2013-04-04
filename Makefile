SDL=`sdl-config --libs`
OBJ=main.o Events.o Megaman.o SSB.o BaseCharacter.o Entity.o Platform.o
EVENTS=Events/Events
BASE=Characters/BaseCharacter
MEGA=Characters/Megaman

all:	main

main:	$(OBJ)
	g++ $(SDL) $(OBJ) -o main

main.o:	main.cpp
	g++ main.cpp -c

SSB.o:	SSB.cpp
	g++ $(SDL) SSB.cpp -c

Events.o: $(EVENTS).cpp
	g++ $(SDL) $(EVENTS).cpp -c

Megaman.o: $(MEGA).cpp
	g++ $(SDL) $(MEGA).cpp -c

BaseCharacter.o: $(BASE).cpp
	g++ $(SDL) $(BASE).cpp -c

Platform.o: Platform.cpp
	g++ $(SDL) Platform.cpp -c

Entity.o: Entity.cpp
	g++ $(SDL) Entity.cpp -c

clean:
	rm -f *.o *~
	rm -f */*~
