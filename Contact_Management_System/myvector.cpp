#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<sstream>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"
using namespace std;

//==========================================================
template <typename T>
MyVector<T>::MyVector(int cap) {
	data = new T[cap];
	v_size = 0;
}
//======================================
template <typename T>
MyVector<T>::~MyVector() {
	delete data;
}
//======================================
template <typename T>
void MyVector<T>::push_back(T element) {
	if (v_size >= v_capacity) {
		T* array;
		if (v_capacity == 0) { //if empty
			array = new T[1];
			v_capacity = 1;
		}
		else { //doubling size
			array = new T[v_capacity * 2];
			v_capacity = v_capacity * 2;
		}
		for (int i = 0; i < v_size; i++) { //copying all elements
			array[i] = data[i];
		}
		if (data != NULL) { //if it is not an empty vector array delete it(all elements been copied), accounts for first 2nd if statement
			delete[] data;
		}
		data = array; //reassign
	}
	data[v_size] = element; //put the element after last element
	v_size = v_size + 1; //increase the count of elements in vector by one
}
//======================================
template <typename T>
void MyVector<T>::insert(int index, T element) {
	if (index > v_size - 1 || index < 0) {
		throw(out_of_range("Contact that you are trying to access does not exist!"));
	}
	if (v_size == v_capacity) {
		T* array;
		if (v_capacity == 0) { //if empty
			array = new T[1];
			v_capacity = 1;
		}
		else {
			array = new T[v_capacity * 2];
			v_capacity = v_capacity * 2;
		}
		for (int i = 0; i < v_size; i++) { //copying all elements
			array[i] = data[i];
		}
		if (data != NULL) { //if it is not an empty vector array delete it(all elements been copied), accounts for first 2nd if statement
			delete[] data;
		}
		data = array; //reassign
	}
	for (int h = v_size - 1; h >= index; h--) { //traverse to find index
		data[h + 1] = data[h]; //shifts elements up
	}
	data[index] = element; //a space is created for the elements to be in the right index due to shifting the prior elements upwards
	v_size = v_size + 1; //size of vector has increased by 1
}
//======================================
template <typename T>
void MyVector<T>::erase(int index) {
	if (index > v_size - 1 || index < 0) {
		throw(out_of_range("Contact option that you have chosen to delete does not exist!"));
	}
	else {
		for (int i = index + 1; i < v_size; i++) { //at the first iteration the index we want gone has been replaced by index after it
			data[i - 1] = data[i]; //continues to fill in space left by before iteration
		}
		v_size = v_size - 1; //1 element has now been deleted
	}
}
//======================================
template <typename T>
T& MyVector<T>::at(int index) {
	if (index > v_size - 1 || index < 0) {
		throw(out_of_range("Contact you are trying to access does not exits!"));
	}
	else {
		return data[index];
	}
}
//======================================
template <typename T>
const T& MyVector<T>::front() {
	if (empty()) {
		throw(out_of_range("Vector is empty!"));
	}
	else {
		return data[0]; //first element
	}
}
//======================================
template <typename T>
const T& MyVector<T>::back() {
	if (empty()) {
		throw(out_of_range("Vector is empty!"));
	}
	else {
		return data[v_size - 1]; //last element
	}
}
//======================================
template <typename T>
int MyVector<T>::size() const {
	return v_size;
}
//======================================
template <typename T>
int MyVector<T>::capacity() const {
	return v_capacity;
}

//======================================
template <typename T>
bool MyVector<T>::empty() const {
	if (v_size == 0) {
		return true;
	}
	else {
		return false;
	}
}
//======================================
template <typename T>
void MyVector<T>::shrink_to_fit() {
	if (v_size != v_capacity) {
		T* array;
		array = new T[v_size]; //creates new vector fit to size with number of elements
		v_capacity = v_size; //sets the capacity to the same amount
		for (int i = 0; i < v_size; i++) { //copying all elements
			array[i] = data[i];
		}
		if (data != NULL) { //if data had nothing in it, there was nothing to copy
			delete[] data;
		}
		data = array; //reassign
	}
}
//======================================
template <typename T>
void MyVector<T>::display(){

	for (int i = 0; i < v_size; i++){ 
		cout<<data[i]<<endl;
	}

}
//======================================
template class MyVector<Contact*>;