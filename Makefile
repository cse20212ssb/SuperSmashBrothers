SDL=`sdl-config --libs`
OBJ=main.o Events.o Megaman.o SSB.o
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

Megaman.o: $(MEGA).cpp $(BASE).h
	g++ $(SDL) $(MEGA).cpp -c

clean:
	rm -f *.o *~ main
	rm -f */*~ */*.o */main
