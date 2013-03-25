SDL=`sdl-config --libs`

all:	main

main:	main.o SSB.o Events.o
	g++ $(SDL) main.o SSB.o Events.o -o main

main.o:	main.cpp
	g++ main.cpp -c

SSB.o:	SSB.cpp
	g++ $(SDL) SSB.cpp -c

Events.o: ./Events/Events.cpp
	g++ $(SDL) ./Events/Events.cpp -c

clean:
	rm -f *.o *~
