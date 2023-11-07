a.out: MyList.o flightticket.o flighthashtable.o main.o
	g++ MyList.o flightticket.o flighthashtable.o main.o -o a.out
main.o: main.cpp
	g++ -c main.cpp
flighthashtable.o: flighthashtable.cpp flighthashtable.h
	g++ -c flighthashtable.cpp
flightticket.o: flightticket.cpp flightticket.h
	g++ -c flightticket.cpp
MyList.o: MyList.cpp MyList.h
	g++ -c MyList.cpp
clean:
	rm a.out main.o flighthashtable.o flightticket.o MyList.o