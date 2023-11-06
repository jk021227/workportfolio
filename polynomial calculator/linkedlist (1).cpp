#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<iomanip>
#include "linkedlist.h"
#include "polycalculator.h"
using namespace std;
//=============================================================================
// constructor
LinkedList::LinkedList ()
{
	this->head = NULL;
}
//=============================================================================
// destructor to clean up all nodes
LinkedList::~LinkedList () 
{
	if(head != NULL){ //will continue to remove head until the list is empty
		removeAll();
	}
}
//=============================================================================
void LinkedList::insert(int coef, int expo){

	if(head == NULL){
	 	Node* node = new Node(coef,expo);
	 	head = node;

	 }
	else{
		Node* prev = head; //pointer to before
		Node* curr = head; //pointer to moving
		while(curr != NULL && (curr->expo > expo)){ //if the current exponent is bigger than the argument exponent
			prev = curr;
			curr = curr->next; //moves on to other nodes
		}
		if(curr != NULL && (curr->expo == expo)){ //coefficients are added together if they have the same exponent
			curr->coef += coef;
		}
		else{
			Node* node = new Node(coef,expo);	
			if(prev == head && curr == head){ //add front
			 	node->next = curr;
			 	head = node;
			 }
			else if(curr == NULL){ //add back
				prev->next = node;
			}
			else{ //add middle
				node->next = curr;
				prev->next = node;
			} 
		}
	}
}
//=============================================================================
void LinkedList::removeAll() {
	if(head != NULL){
		while(head != NULL){
			Node* old = head; 
			head = old->next;
			delete old; }
	} 
}
//=============================================================================
void LinkedList::display() const{
	Node* temp = head; //creates a temporary node set as head

	while(temp != NULL){ //continues down the list until temp reaches NULL
		if(temp->coef > 0){
			cout<<"+";
		}
		if(temp->expo == 0 && temp->coef != 0){
			cout<<temp->coef<<" ";
		}
		else if(temp->expo == 1 && temp->coef !=0){
			cout<<temp->coef<<"x";
		}
		else if(temp->expo > 1 && temp->coef != 0){
			cout<<temp->coef<<"x^"<<temp->expo;
		}
		temp = temp->next;
	}
}
//=============================================================================
string LinkedList::helperfout(){
	Node* temp = head; //creates a temporary node set as head
	string help;
	while(temp != NULL){ //continues down the list until temp reaches NULL
		if(temp->coef > 0){ //we convert the integers into string so that it can be used for writefile
			help +="+";
		}
		if(temp->expo == 0 && temp->coef != 0){
			help += to_string(temp->coef) + " ";
		}
		else if(temp->expo == 1 && temp->coef !=0){
			help += to_string(temp->coef) + "x";
		}
		else if(temp->expo > 1 && temp->coef != 0){
			help += to_string(temp->coef) + "x^" + to_string(temp->expo);
		}
		temp = temp->next;
	}
return help;
}
//=============================================================================
bool LinkedList::empty(){
	return head == NULL; 
}
