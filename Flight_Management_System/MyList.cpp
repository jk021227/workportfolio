#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<sstream>
#include "MyList.h"
#include "flighthashtable.h"

using namespace std;
//=============================================================================
template <typename T>
MyList<T>::MyList()
{
	this->head = NULL;
	list_size = 0;
}
//====================================
// destructor to clean up all nodes
template <typename T>
MyList<T>::~MyList() 
{
	while(!empty()){ //will continue to remove head until the list is empty
		removeFront();
	}
}
//====================================
template <typename T>
T* MyList<T>::front(){ //return front for peudo-iterator
	if(head == NULL){
		return NULL;
	}
	else{
		return head;
	}
}
//====================================
// Check if the list is empty or not
template <typename T>
bool MyList<T>::empty() const 
{
	return head == NULL; 
}
//====================================
template <typename T>
void MyList<T>::add_front(T* node) {
	node->next = this->head; //connects node's next to head
	this->head = node; //node now becomes the head
    list_size++;
}
//====================================
// remove the first node from the list
template <typename T>
void MyList<T>::removeFront()
{
	T* old = head; //makes the current head placed into old
	head = old->next; //moves the head status to old's next
	delete old; //deletes old
	list_size--;
}
//====================================
template <typename T>
bool MyList<T>::removePos(int pos){
	T* temp = head; 
	T* prev;
	int iterator = 0;
	
	if(pos == 0){
		removeFront(); //remove the front one
		return true;
	}

	else{
		while(pos != iterator){ //finding the position through counter
			prev = temp;
			temp = temp->next;
			iterator++;

		} //arrived at the position that needs to be deleted
		prev->next = temp->next; //swapping links
		delete(temp); //deleting temporary value
		list_size--;
		return true;
	}
}
//==============================================
// display all nodes of the linked list
template <typename T>
T* MyList<T>::getelem(int index){
	T* temp = head;
	int count = 0;
	while(count != index){
		temp = temp->next; //moving temp
		count++; //increment count
	}
	return temp;
}
template <typename T>
int MyList<T>::size(){
	return list_size;//return list size
}
template class MyList<HashNode>;