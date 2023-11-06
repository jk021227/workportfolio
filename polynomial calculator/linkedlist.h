//============================================================================
// Name         : Polynomial Calculator 
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-08-2022
// Date Modified: 30-08-2022 
// Description  : Linked List class used for Polynomial Calculagtor
//============================================================================

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
using namespace std;
class Node
{
	private:
		int coef; //coefficient of a term
		int expo; //exponent of a term
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(int coef, int expo) : coef(coef), expo(expo), next(NULL)
		{}
		friend class LinkedList;
		friend class PolyCalculator;
};
//=============================================================================
class LinkedList
{
	private:
		Node* head; // pointer to the head of the Singly Linked list
	public:
		LinkedList (); // empty list constructor
		void insert(int coef,int expo); // add a new Node (term) at the right place in the Linked List
		void display() const;
		void removeAll();	 // clean up (delete) all nodes
		string helperfout(); //help fout into file 
		bool empty(); //check if empty
		~LinkedList (); // destructor to clean up all nodes
	
		friend class PolyCalculator;
	};
//
	
#endif
