all: main

main:	main.o Events.o
	g++ `sdl-config --libs` main.o Events.o -o main

main.o:	main.cpp
	g++ `sdl-config --libs` main.cpp -c 

Events.o: Events.cpp
	g++ `sdl-config --libs` Events.cpp -c
clean:
	rm -f *~ *.o main
