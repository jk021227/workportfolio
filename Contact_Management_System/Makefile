a.out: contact.o myvector.o contactbst.o main.o
	g++ contact.o myvector.o contactbst.o main.o -o a.out
main.o: main.cpp
	g++ -c main.cpp
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
clean:
	rm a.out main.o contactbst.o myvector.o contact.o