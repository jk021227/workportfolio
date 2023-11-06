//============================================================================
// Name         : Polynomial Calculator 
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-08-2022
// Date Modified: 30-08-2022 
// Description  : Polynomial Calculator in C++ using Singly Linked-List
//============================================================================

#ifndef POLYCACLULATOR_H
#define POLYCACLULATOR_H
#include<fstream>
#include<string>
#include "linkedlist.h"
using namespace std;
//=======================================
class PolyCalculator
{
	private:
		LinkedList list1; //list where you store the first polynomial expression
		LinkedList list2; //list where you store the second polynomial expression
		LinkedList list3; //list where you store the final polynomial expression after mathmathical operations 
	public:
		void input(); //take input the values of polynomial expressions
		void add(); //add both polynomials (list1 and list2) and save the result in list3
		void sub(); //subtract list2 from list1 and save the results in list3
		void mul(); //multiply both polynomials (list1 and list2) and save the result in list3
		void readData(string); //read a file and load the data into the linked lists (list1 and list2)
		void writeData(string); //write the polynomial expressions and the results of addition,subtraction and multiplication to a file
		void parse(string,LinkedList&);
		void display(); //display both polynomials (list1 and list2)
	private:
		void write(LinkedList& ,ofstream&); //Optional helper function to write a polynomial expression (List) to a file;
};
	


#endif
