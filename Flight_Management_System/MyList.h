#ifndef MYLIST_H
#define MYLIST_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<string>

// template <typename T>
// class Node
// {
// 	private:
// 		T elem; //data element 
// 		T* next; //Link (pointer) to the next Node
		
// 	public:
// 		Node(T elem) : elem(elem), next(NULL)
// 		{}
// 		friend class MyLinkedList ;
// };

template <typename T>
class MyList
{
	private:
		T* head; // pointer to the head of list
		int list_size;
	public:
		MyList (); // empty list constructor
		~MyList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		void removeFront(); // remove front Node from the list
		int getIndexOf(T* node); //returns index of key+data pair in bucket
		void display() const;
		bool removePos(int pos);
		T* front();
		void add_front(T* node);
		T* getelem(int index);
		int size();

		friend class FlightHASHTABLE;
		friend class Flight_Ticket;
		friend class HashNode;
};
#endif