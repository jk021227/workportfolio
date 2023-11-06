a.out: polycalculator.o linkedlist.o main.o
	g++ polycalculator.o linkedlist.o main.o -o a.out
main.o: main.cpp
	g++ -c main.cpp
polycalculator.o: polycalculator.cpp polycalculator.h
	g++ -c polycalculator.cpp
linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -c linkedlist.cpp
clean:
	rm a.out main.o polycalculator.o linkedlist.o


