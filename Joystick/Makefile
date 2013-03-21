all: main

main:	main.o
	g++ `sdl-config --libs` main.o -o main

main.o:	main.cpp
	g++ `sdl-config --libs` main.cpp -c 

clean:
	rm -f *~ *.o
