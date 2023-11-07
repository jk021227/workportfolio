#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<sstream>
#include "contactbst.h"
#include "myvector.h"
using namespace std;


ContactBST::ContactBST() {
	this->root = nullptr;
}
//==========================================================
ContactBST::~ContactBST() {
	delete root;

}
//==========================================================
// void ContactBST::destructor_helper(Node* ptr) { 
// 	if(ptr==root){
// 		delete root;
// 		return;
// 	}
// 	if(ptr->left != nullptr){
// 		destructor_helper(ptr->left);
// 	}
// 	if(ptr->right != nullptr){
// 		destructor_helper(ptr->right);
// 	}
// 	delete ptr;
// }
//==========================================================
Node* ContactBST::getRoot() {
	return this->root;
}
//==========================================================
void ContactBST::add(Node* ptr, string key, Contact* data) {
	Node* entry = searchFor(getRoot(), key); 
	if (root == nullptr) {
		root = new Node(key, data);
	}
	else if	(entry == nullptr) { //case 1: if there is no same key in BST:  pushback into vector & add to BST
		if (key < ptr->key) { //key is smaller then left
			if (ptr->left == nullptr) {
				ptr->left = new Node(key, data);
				ptr->left->parent = ptr;
			}
			else {
				add(ptr->left, key, data);
			}
		}
		else if (key > ptr->key) { //key is bigger then right
			if (ptr->right == nullptr) {
				ptr->right = new Node(key, data);
				ptr->right->parent = ptr;
			}
			else {
				add(ptr->right, key, data);
			}
		}
	}
	else { // case 2: if there is same key in BST, pushback into that node's vector 
		(entry->contactVector).push_back(data);
	}
}
//==========================================================
int ContactBST::importCSV(string path) {//Load all the contacts from the CSV file to the BST     for (int x=0; x<strlen(arr); x++)
	ifstream fin(path);
	string line = "";
	int number = 0;
	if (fin.is_open()) {
		while (getline(fin, line)) { //getting input

			string fname;
			string lname;
			string email;
			string primaryPhone;
			string city;
			string country;
			string temp;
			bool isFav;

			stringstream fin(line);

			getline(fin, fname, ',');
   			fname[0] = toupper(fname[0]); //acounts for case sensitivity
   			for(int i = 1; i < fname.length(); i++){ //acounts for case sensitivity
   				fname[i] = tolower(fname[i]);
   			}
			getline(fin, lname, ',');
   			lname[0] = toupper(lname[0]); //acounts for case sensitivity
   			for(int i = 1; i < lname.length(); i++){ //acounts for case sensitivity
   				lname[i] = tolower(lname[i]);
   			}
			getline(fin, email, ','); //storing imported details into vars
			getline(fin, primaryPhone, ',');
			getline(fin, city, ',');
			getline(fin, country, ',');
			getline(fin, temp);
			isFav = stoi(temp);//convert to bool use temp
			
			string node_key = fname + " " + lname; //creating key

			Contact* contact1 = new Contact(fname, lname, email, primaryPhone, city, country, isFav); //creating contact object
			line = "";
			// search if there are other nodes with same key
			add(root, node_key, contact1);
			number++;
		} 
	cout<<number<<" contacts imported"<<endl; //will print out the number of contacts that were imported
	return number;
	}
	else {
		cout<<"File does not exist!"<<endl;
		return -1;
	}
}
//==========================================================
int ContactBST::exportCSV(Node* ptr,string path){
	int num_lines = 0; //coutner for number of lines
	ofstream fout;
	fout.open(path, ios::app); //openfile
		string fav = "";
		if(ptr == nullptr){
			return 0;
		}

		if(ptr->left != nullptr) { //internal node 
			num_lines+=exportCSV(ptr->left, path); //going left
		}

	        for(int i = 0; i < (ptr->contactVector).size(); i++){
	            Contact *ct = ptr->contactVector.at(i);
	            if(ct->isFav == 1){
	                fav = "1";
	            }
	            else{
	                fav = "0";
	            }
	            fout<<ct->fname+","+ct->lname+","+ct->email+","+ct->primaryPhone+","+ct->city+","+ct->country+","+fav+"\n"; //writing it into a file
	            num_lines++; //increment number of contacts each time one is exported
	        }

		if (ptr->right != nullptr) { //internal node
			num_lines+=exportCSV(ptr->right, path); //going right
		}
	fout.close();

return num_lines; //will print out the number of contacts exported in main
}
//==========================================================
Node* ContactBST::searchFor(Node* ptr, string key) {
	if (root == nullptr) { //if there is nothing in the database
		return nullptr;
	}
	else if(ptr == nullptr){ //if no such node exists with said key
		return nullptr;
	}
	else if (key < ptr->key) { //if key is smaller
		if (ptr->left == nullptr) { //there's nowhere to go
			return nullptr;
		}
		else {
			ptr = searchFor(ptr->left, key); //go left
		}
	}
	else if (key > ptr->key) { //if key is bigger
		if (ptr->right == nullptr) { //there's nowhere to go
			return nullptr;
		}
		else {
			ptr = searchFor(ptr->right, key); //go right
		}
	}
	else if (key == ptr->key) { //here is the key!
	}
return ptr;
}

//==========================================================
void ContactBST::edit(Node* ptr, string key){
	string choice;
	string change;
	string content;
	string temp;
	string new_key;
	bool flag = true;
	Node* store = searchFor(root, key);
	if(store == nullptr){
		cout<<"The said person does not exist!"<<endl;
	}
	else{
		if((store->contactVector).size() > 1){ //there are more than 1 element in vector of the node
			cout<<"Here are all the contacts under that first and last name: "<<endl;
			store->print();
			cout<<"Which one would you like to change: "<<endl;
			//getline(cin,choice);
			do{
				flag = true;
				getline(cin,choice);
				for(int i = 0; i < choice.length();i++){
					if (!isdigit(choice[i])){
						flag = false;
					}
				}
				if(!flag){
					cout<<"Please enter a valid option: "<<endl;
				}
			}
			while(!flag);

			int option = stoi(choice); // this is the one you want to edit
			while(flag){ //repeats until user answers that they no longer want to change the ndoe
				cout<<"What would you like to change about this contact: "<<endl;
				cout<<"1. First Name "<< "2. Last Name "<<"3. Email "<<"4. Phone Number "<<"5. City "<<"6. Country"<<endl;
				getline(cin, change);
				while(change != "1" && change != "2" && change != "3" && change != "4" && change != "5" && change != "6"){ //check userinput for choice
					cout<<"Please choose one of the options that are available: "<<endl;
					getline(cin, change);
				}
				int change_num = stoi(change);

				if(change_num == 1){ //do not remove node since there is more than one contact
					cout<<"The current first name is "<<store->contactVector.at(option-1)->fname<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(option-1)->fname = content;
					new_key = store->contactVector.at(option-1)->fname + " " + store->contactVector.at(option-1)->lname;
					add(root, new_key, store->contactVector.at(option-1));
					store->contactVector.erase(option-1);
					store = searchFor(root, new_key); // by putting this here, the node that the user is editing in the while loop is not lost, otherwise we could not edit the first name then also try to edit the last name straight away

				}
				else if(change_num == 2){ //do not remove node since there is more than one contact
					cout<<"The current first name is "<<store->contactVector.at(option-1)->lname<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(option-1)->lname = content;
					new_key = store->contactVector.at(option-1)->fname + " " + store->contactVector.at(option-1)->lname;
					add(root, new_key, store->contactVector.at(option-1));
					store->contactVector.erase(option-1);
					store = searchFor(root, new_key);


				}
				else if(change_num == 3){ //change email
					cout<<"The current email is "<<store->contactVector.at(option-1)->email<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(option-1)->email = content;
					store = searchFor(root, new_key);
				}
				else if(change_num == 4){ //change phone number
					cout<<"The current phone number is "<<store->contactVector.at(option-1)->primaryPhone<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(option-1)->primaryPhone = content;
					store = searchFor(root, new_key);
				}
				else if(change_num == 5){ //change city
					cout<<"The current city is "<<store->contactVector.at(option-1)->city<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(option-1)->city = content;
				}
				else{ //change country
					cout<<"The current country is "<<store->contactVector.at(option-1)->country<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(option-1)->country = content;
				}
				cout<<"Do you want to edit another field (y/n)?"<<endl;
				getline(cin, temp);
				while(temp != "y" && temp != "n"){
					cout<<"Please enter 'y' or 'n': "<<endl;
					getline(cin, temp);
				}
				if(temp == "y"){
					flag = true;
				}
				else{
					flag = false;
					cout<<"Contact has successfully been updated!"<<endl;
				}
			}	
		}
		else{ //theres only one contact in the node
			while(flag){
				cout<<"What would you like to change about this contact: "<<endl;
				cout<<"1. First Name "<< "2. Last Name "<<"3. Email "<<"4. Phone Number "<<"5. City "<<"6. Country"<<endl;
				getline(cin, change);
				
				while(change != "1" && change != "2" && change != "3" && change != "4" && change != "5" && change != "6"){ //check userinput for choice
					cout<<"Please choose one of the options that are available: "<<endl;
					getline(cin, change);
				}
				int change_num = stoi(change);

				if(change_num == 1){ //remove node after changing contact since there's only one contact in node of that key
					cout<<"The current first name is "<<store->contactVector.at(0)->fname<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(0)->fname = content;
					new_key = store->contactVector.at(0)->fname + " " + store->contactVector.at(0)->lname;
					add(root, new_key, store->contactVector.at(0));
					store->contactVector.erase(0);
					remove(root, key);
					store = searchFor(root, new_key);


				}
				else if(change_num == 2){ //remove node after changing contact since there's only one contact in node of that key
					cout<<"The current last name is "<<store->contactVector.at(0)->lname<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(0)->lname = content;
					new_key = store->contactVector.at(0)->fname + " " + store->contactVector.at(0)->lname;
					add(root, new_key, store->contactVector.at(0));
					store->contactVector.erase(0);
					remove(root, key);
					store = searchFor(root, new_key);

				}
				else if(change_num == 3){ //change email
					cout<<"The current email is "<<store->contactVector.at(0)->email<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(0)->email = content;
				}
				else if(change_num == 4){ //change phone number
					cout<<"The current phone number is "<<store->contactVector.at(0)->primaryPhone<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(0)->primaryPhone = content;
				}
				else if(change_num == 5){ //change city
					cout<<"The current city is "<<store->contactVector.at(0)->city<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(0)->city = content;
				}
				else{ //change country
					cout<<"The current country is "<<store->contactVector.at(0)->country<<endl;
					cout<<"What would you like to change it as: "<<endl;
					getline(cin,content);
					store->contactVector.at(0)->country = content;
				}
				cout<<"Do you want to edit another field (y/n)?"<<endl; //asking to check whether they want to edit anything further
				getline(cin, temp);
				while(temp != "y" && temp != "n"){
					cout<<"Please enter 'y' or 'n': "<<endl;
					getline(cin, temp);
				}
				if(temp == "y"){
					flag = true;
				}
				else{
					flag = false;
					cout<<"Contact has successfully been updated!"<<endl;
				}
			}
		}	
	}
}
//==========================================================
void ContactBST::remove(Node* ptr,string key){
	string choice;
	bool flag;
	Node* remove_node = searchFor(ptr, key);
	if (ptr == nullptr) {
		cout << "The database is empty!" << endl;
		return;
	}
	if (remove_node == nullptr) {
		cout << "the contact to remove does not exist."<<endl;
	}
	else if(key < ptr->key){
		remove(ptr->left, key);
	}
	else if(key > ptr->key){
		remove(ptr->right, key);
	}
	else if(key == ptr->key){ //found node with same key
		if(ptr->right == nullptr && ptr->left == nullptr){ //case 1: no children
			if(ptr == root){ //case 1a: if the node is root, only node
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					
					do{ //checks validity of the option entered by user
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){ 
							if(!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{ //if there is only one contact in the node
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					root = nullptr;
				}
			}

			else if(ptr->parent->left == ptr){ //case 1b: the node is on the left of the parent
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					//getline(cin,choice);

					do{
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){ //choice has to be a digit
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{ //if the ndoe to remove is not empty then delete it
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					ptr->parent->left = nullptr;
				}
			}
			else{ //case1c: node is on the right of its parent
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					
					do{
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					ptr->parent->right = nullptr;
				}
			}
		}

		else if(ptr->right == nullptr && ptr->left != nullptr){//case 2: left child only
			if(ptr == root){//case 2a: ptr is root
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					//getline(cin,choice);
					
					do{
						cout<< "501"<<endl;
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);
					
					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					root = ptr->left;
					delete ptr;
				}
			}
			else if(ptr->parent->left == ptr){//case 2b: ptr is the left node of its parent
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					//getline(cin,choice);
					
					do{
						cout<<"536"<<endl;
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					ptr->parent->left = ptr->left;
					ptr->left->parent = ptr->parent;
					delete ptr;

				}
			}
			else if(ptr->parent->right == ptr){//2c: ptr is the right node of its parent
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					//getline(cin,choice);
					
					do{
						cout<<"573"<<endl;
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					ptr->parent->right = ptr->left;
					ptr->left->parent = ptr->parent;
					delete ptr;
				}
			}
		}
		else if(ptr->right != nullptr && ptr->left == nullptr){//case 3: right child only
			if(ptr == root){//case 3a: ptr is root
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					//getline(cin,choice);
					
					do{
						cout<<"611"<<endl;
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					root = ptr->right;
					delete ptr;
				}
			}
			else if(ptr->parent->left == ptr){//case 3b: ptr is left node of parent
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					//getline(cin,choice);
					
					do{
						cout<<"646"<<endl;
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1); 
				}
				else{
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					ptr->parent->left = ptr->right;
					ptr->right->parent = ptr->parent; 
					delete ptr;
				}
			}
			else if(ptr->parent->right == ptr){//case 3c: ptr is right node of parent
				if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
					cout<<"Here are all the contacts under that first and last name: "<<endl;
					remove_node->print();					
					cout<<"Which one would you like to delete: "<<endl;
					
					do{
						flag = true;
						getline(cin,choice);
						for(int i = 0; i < choice.length();i++){
							if (!isdigit(choice[i])){
								flag = false;
							}
						}
						if(!flag){
							cout<<"Please enter a valid option: "<<endl;
						}
					}
					while(!flag);

					int del_index = stoi(choice);
					remove_node->contactVector.erase(del_index-1);
				}
				else{
					if(remove_node->contactVector.size() != 0){
						remove_node->contactVector.erase(0);}
					ptr->parent->right = ptr->right;
					ptr->right->parent = ptr->parent;
					delete ptr; 
				}
			}
		}
		else if(ptr->left != nullptr && ptr->right != nullptr){ //has both children 
			if((remove_node->contactVector).size() > 1){ //there are more than 1 element in vector of the node
				cout<<"Here are all the contacts under that first and last name: "<<endl;
				remove_node->print();					
				cout<<"Which one would you like to delete: "<<endl;

				do{
					cout<<"719"<<endl;
					flag = true;
					getline(cin,choice);
					for(int i = 0; i < choice.length();i++){
						if (!isdigit(choice[i])){
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter a valid option: "<<endl;
					}
				}
				while(!flag);

				int del_index = stoi(choice);
				remove_node->contactVector.erase(del_index-1);
			}
			else{ //has both children and there is only one element in the node so we need to also delete the node after copying the elements
				Node* val = findMin(ptr->right);
				ptr->key = val->key; 
				ptr->contactVector = val->contactVector;
				val->contactVector = MyVector<Contact*>(0); //set contactVector content of node val to zero so that it won't ask "which one do you want to delete?"
				remove(ptr->right, val->key);
			}
		}
	}
}
//==========================================================
bool ContactBST::markFav(string key){ //traverse to find then ask to change
	Node* entry = searchFor(root, key);
	string choice;
	int del_index;
	bool flag;
	if(entry == nullptr){ //contact deos not exist
		cout<<"There is no such contact!"<<endl;
		return true;
	}
	else if((entry->contactVector).size() > 1){ //there is more than one contact under the same key
		cout<<"Here are all the contacts under that first and last name: "<<endl;
		entry->print();
		cout<<"Which one would you like to mark as favorite: "<<endl;
		
		do{
			flag = true;
			getline(cin,choice);
			for(int i = 0; i < choice.length();i++){
				if (!isdigit(choice[i])){
					flag = false;
				}
			}
			if(!flag){
				cout<<"Please enter a valid option: "<<endl;
			}
		}
		while(!flag);

		del_index = stoi(choice);
		entry->contactVector.at(del_index-1)->isFav = true; //reassigning isFav val
		cout<<entry->contactVector.at(del_index-1)->fname<<" "<<entry->contactVector.at(del_index-1)->lname<<"("<<entry->contactVector.at(del_index-1)->email<<")"<<" has been successfully marked as favorite!"<<endl;
	}
	else{ //only one contacts exists in the node
		entry->contactVector.at(0)->isFav = true; //reassigning isFav val
		cout<<entry->contactVector.at(0)->fname<<" "<<entry->contactVector.at(0)->lname<<"("<<entry->contactVector.at(0)->email<<")"<<" has been successfully marked as favorite!"<<endl;
	}
return true;
}
//==========================================================
bool ContactBST::unmarkFav(string key){
	Node* entry = searchFor(root, key);
	string choice;
	int del_index;
	bool flag;
	if(entry == nullptr){ //contact deos not exist
		cout<<"There is no such contact!"<<endl;
		return true;
	}
	else if((entry->contactVector).size() > 1){ //there is more than one contact under the same key
		cout<<"Here are all the contacts under that first and last name: "<<endl;
		entry->print();
		cout<<"Which one would you like to unmark as favorite: "<<endl;
		
		do{
			flag = true;
			getline(cin,choice);
			for(int i = 0; i < choice.length();i++){
				if (!isdigit(choice[i])){
					flag = false;
				}
			}
			if(!flag){
				cout<<"Please enter a valid option: "<<endl;
			}
		}
		while(!flag);

		del_index = stoi(choice);
		entry->contactVector.at(del_index-1)->isFav = false; //reassigning isFav val
		cout<<entry->contactVector.at(del_index-1)->fname<<" "<<entry->contactVector.at(del_index-1)->lname<<"("<<entry->contactVector.at(del_index-1)->email<<")"<<" has been successfully unmarked as favorite!"<<endl;
	}
	else{ //only one contacts exists in the node in this case we do not need del_index
		entry->contactVector.at(0)->isFav = false; //reassigning isFav val
		cout<<entry->contactVector.at(0)->fname<<" "<<entry->contactVector.at(0)->lname<<"("<<entry->contactVector.at(0)->email<<")"<<" has been successfully unmarked as favorite!"<<endl;
	}
return true;
}
//==========================================================
void ContactBST::printFav(Node* ptr){ 
	if(ptr == nullptr){
		return;
	}
	if(ptr->left != nullptr || ptr->right != nullptr) {
		printFav(ptr->left);
	}
	for(int i=0; i<ptr->contactVector.size(); i++){ 
		Contact *ct = ptr->contactVector.at(i);
		if(ct->isFav == true){ //only prints out the ones that meet this if condition of isFav = true
			cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
		}
	}
	if (ptr->left != nullptr || ptr->right != nullptr) {
		printFav(ptr->right);
	}

}
//==========================================================
void ContactBST::printASC(Node* ptr){ //take root as pointer
	if(ptr == nullptr){
		return;
	}
	if(ptr->left != nullptr || ptr->right != nullptr) {
		printASC(ptr->left);
	}
	for(int i=0; i<ptr->contactVector.size(); i++){ //in order print method
		Contact *ct = ptr->contactVector.at(i);
		cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
	}
	if (ptr->left != nullptr || ptr->right != nullptr) {
		printASC(ptr->right);
	}

}
//==========================================================
void ContactBST::printDES(Node* ptr){  //in order print but switch left with right to make it descend
	if(ptr == nullptr){
		return;
	}
	if (ptr->left != nullptr || ptr->right != nullptr) {
		printDES(ptr->right);
	}
	for(int i=0; i<ptr->contactVector.size(); i++){
		Contact *ct = ptr->contactVector.at(i);
		cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
	}
	if(ptr->left != nullptr || ptr->right != nullptr) {
		printDES(ptr->left);
	}
	
}
//==========================================================
Node* ContactBST::findMin(Node* ptr){
	while(ptr->left != nullptr){
		ptr = ptr->left;
	}
	return ptr;
}
//==========================================================

