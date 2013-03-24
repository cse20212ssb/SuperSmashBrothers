all:	main

main:	main.o SSB.o Events.o
	g++ `sdl-config --libs` main.o SSB.o Events.o -o main

main.o:	main.cpp
	g++ main.cpp -c

SSB.o:	SSB.cpp
	g++ `sdl-config --libs` SSB.cpp -c

Events.o: ./Events/Events.cpp
	g++ `sdl-config --libs` ./Events/Events.cpp -c

clean:
	rm -f *.o *~ main
