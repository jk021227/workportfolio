#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include "flightticket.h"
#include "MyList.h"


using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+flightNumber
		Flight_Ticket data;
		HashNode* next;
		
	public:
		HashNode(string key, Flight_Ticket data)
		{
			this->key = key;
			this->data = data;
			this->next = NULL;
		}
		friend class FlightHASHTABLE;
		friend class Flight_Ticket;
		template <typename T> friend class MyList;
};

// template <typename T>
// class MyList
// {
// 	private:
// 		T* head; // pointer to the head of list
// 		int list_size;
// 	public:
// 		MyList (); // empty list constructor
// 		~MyList (); // destructor to clean up all nodes
// 		bool empty() const; // is list empty?
// 		//void addFront(T node); // add a new Node at the front of the list
// 		void removeFront(); // remove front Node from the list
// 		unsigned int countElem(string key); //count frequency of an element in the list
// 		int getIndexOf(T* node); //returns index of key+data pair in bucket
// 		void display() const;
// 		bool removePos(int pos);
// 		T* front();
// 		void add_front(T* node);
// 		T* getelem(int index);
// 		int size();

// 		friend class FlightHASHTABLE;
// 		friend class Flight_Ticket;
// 		friend class HashNode;
// };
//=============================================================================
class FlightHASHTABLE
{
	private: 
		MyList<HashNode> *buckets;		//List of Buckets, Please create your own List Class called MyList
		MyList<HashNode> *allindee;     //separate hash table for allinday function
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int probes; 					//number of probes
	public:
		FlightHASHTABLE(int capacity);						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(string key); 						//implement and test different hash functions	
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
		int count_collisions();					//return the number of collisions on the HashTable
		int add(string key, Flight_Ticket *data);			//add new flight to the HashTable
		int add_date(string key,Flight_Ticket *data); //helper for allinday
		void removeRecord(string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void remove_helper(HashNode* node);
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
		friend class HashNode;	
		friend class Flight_Ticket;
};

#endif
