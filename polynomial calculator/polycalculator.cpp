#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<string>
#include "polycalculator.h"
#include "linkedlist.h"
using namespace std;
//=============================================================================
//=============================================================================
void PolyCalculator::input() {
	list1.removeAll();
	list2.removeAll();
	string p1 = "";
	string p2 = "";
	cout<<"Enter the first polynomial expression: "<<endl;
	getline(cin,p1);
	cout<<"Enter the second polynomial expression: "<<endl;
	getline(cin,p2);
	this->parse(p1, list1);
	if(list1.empty()){ //so that "invalid expression does not print twice"
		return;
	}
	this->parse(p2, list2); //only displays if there's smth in the lists
	if(!list1.empty()){
		this->display();
	}
}
//=============================================================================
void PolyCalculator::parse(string str, LinkedList& list){
	remove(str.begin(), str.end(), ' ');
	string sub = "";
	char var = 'x';
	char pow = '^';
	int index = 0;
	int counter = 0;
	int k;
	string coef_term = "";
	string expo_term = "";
	string sign = "";
	int coefficient;
	int exponent;
	bool flag = true;
	bool addsign = true;

	while(!str.empty() && flag != false){ //loop runs while the string is not empty
		addsign = true;
		if(str[0] == '-' || str[0] == '+'){ //this is the case where the term has a sign in front of it
			if(str[0] == '-'){
				sign = "-";
				str.erase(0,1);
				addsign = false;
			}
			else if(str[0] == '+'){
				sign = "+";
				str.erase(0,1);
			}
		}
		else if(isdigit(str[0]) || str[0] == 'x'){ //in the case where the first term has no sign or is x
			index = 0;
		}
		for(int i = index; i < str.size(); i++){
			if(str.find('+') != string::npos || str.find('-') != string::npos){ //when it's more than one term
				if(str[i] == '-' || str[i] == '+') { //will get the index where we need to stop
				counter = i;
				break;
				}
			}
			else if(str.find('+') == string::npos || str.find('-') == string::npos){ //when there's only one term
				counter = str.length();// need to set counter properly
				break;
			}
		}
		sub = str.substr(0,counter); //creates a copy of the term in question
		int counting_x = count(sub.begin(), sub.end(), var); //makes sure there's no xx
		int counting_power = count(sub.begin(), sub.end(), pow); //makes sure there's only one ^ *It works up till here
		if(sub.find(var) != string::npos && sub.find(pow) != string::npos && counting_x == 1 && counting_power == 1){  //case 1: there's an exponent & x *this works
			k = sub.find(var); //finds index of the first occurrence of var
			if(sub[k+1] != '^'){ //if there is a power symbol next to x (checks order of term)
				flag = false;
			}
			else if(sub[k+1] == '^'){ //there is a power symbol(right order) 
				coef_term = sub.substr(0,k); //we get the coefficient substring
				expo_term = sub.substr(k+2,sub.size()-(k+2)); //get the exponent substring
				if(k == 0){ //there's no coefficient number
					if(k==0 && addsign == false){ //when x has a -
					coefficient = -1; //set coefficient manually
				}
					else if(k==0 && addsign == true){ //when coefficient is 1
					coefficient = 1;
					}
				}
				else if(expo_term.empty()){
					flag = false;
				}
				else if(k != 0){ //when there is numbers infront of x
					for(int i = 0; i < coef_term.size(); i++){ //checks if the coefficient term is a digit
						if(isdigit(coef_term[i]) == false){ 
							flag = false;
						}
					}
					for(int i = 0; i < expo_term.size(); i++){ //checks if the exponent term is a digit
						if(isdigit(expo_term[i]) == false){
							flag = false;
						}
					}
				}
				if(flag == true){ //if the term is valid
					if(addsign == true && k != 0){ //when positive & there's numbers infront
						coefficient = stoi(coef_term); //cast coefficient as int
						exponent = stoi(expo_term); //cast exponent as int 
						str.erase(0,counter); //erase the term in the substring
						list.insert(coefficient,exponent); //insert it into list - segmentation fault here

					}
					else if(addsign == false && k != 0){ //when it is negative & there's numbers infront
						coef_term = coef_term.insert(0,sign);
						coefficient = stoi(coef_term); //cast coefficient as int
						exponent = stoi(expo_term); //cast exponent as int
						str.erase(0,counter); //erase the term in the substring
						list.insert(coefficient,exponent); //insert it into list - segmentation fault here
					}
					else if(addsign == true && k == 0){ //when positive & there's no num coef
						exponent = stoi(expo_term);
						str.erase(0,counter); 
						list.insert(coefficient, exponent);
					}
					else if(addsign == false && k == 0){ //when negative & there's no num coef
						exponent = stoi(expo_term);
						str.erase(0,counter);
						list.insert(coefficient, exponent);
					}
				}
			}
		}
		else if(sub.find(var) != string::npos && sub.find(pow) == string::npos && counting_x == 1 && counting_power == 0){ //case 2: there's only an x
			k = sub.find(var);
			if(k != (sub.size()-1)){ //when x is not the last char in the string
				flag = false;
			}
			else if(k == 0){ //when x does not have num infront
				if(k==0 && addsign == false){ //when x has - in front
					coefficient = -1;
					exponent = 1;
					str.erase(0,counter); //erase is done so that the term that will be inserted is not used for the next iteration of the loop & used as a condition to exit while loop
					list.insert(coefficient,exponent);
					
				}
				else if(k==0 && addsign == true){ 
					coefficient = 1;
					exponent = 1;
					str.erase(0,counter);
					list.insert(coefficient,exponent);
					
				}

			}
			else if(k == (sub.size()-1)){ //when x is the last char in the string
				coef_term = sub.substr(0,k);

				for(int i = 0; i < coef_term.size(); i++){
					if(isdigit(coef_term[i]) == false){
						flag = false;
					}
				}

				for(int i = 0; i < expo_term.size(); i++){
					if(isdigit(expo_term[i]) == false){
						flag = false;	
					}
				}
				if(flag == true){
					if(addsign == false){ //when it is negative & there's numbers infront
						coef_term = sub.substr(0,(sub.size()));
						coef_term = coef_term.insert(0,sign); 
						coefficient = stoi(coef_term);
						exponent = 1;
						str.erase(0,counter);
						list.insert(coefficient,exponent);
					}
					else if(addsign){
						coefficient = stoi(coef_term);
						exponent = 1;
						str.erase(0,counter);
						list.insert(coefficient,exponent);
					}
				}
			}
		
		}
		else if(sub.find(var) == string::npos && sub.find(pow) == string::npos){ //case 3: there's only a constant 
			for(int i = 0; i < sub.size(); i++){
				if(isdigit(sub[i]) == false){ 
					flag = false;
				}
			}
			if(flag == true){
				if(addsign == false){ //when it is negative & there's numbers infront
					coef_term = sub.substr(0,(sub.size()));
					coef_term = coef_term.insert(0,sign); 
					expo_term = '0';
					coefficient = stoi(coef_term);
					exponent = 0;
					str.erase(0,counter);
					list.insert(coefficient,exponent);
				}
				else if(addsign){			
					coef_term = sub.substr(0,(sub.size()));
					expo_term = '0';
					coefficient = stoi(coef_term);
					exponent = 0;
					str.erase(0,counter);
					list.insert(coefficient,exponent);
				}

			}
		}
		else{
			flag = false;
		}
	}
	if(flag == false){
		cout<<"invalid expression!"<<endl;
	}
}
//=============================================================================
void PolyCalculator::display(){
	cout<<"Exp1: ";
	list1.display();
	cout<<"\n";
	cout<<"Exp2: ";
	list2.display();
	cout<<"\n";
}
//=============================================================================
void PolyCalculator::add(){
	//addition is done via using the simplifying term that already exists in insert
	list3.removeAll(); //clears list3 for use
	Node* temp1 = list1.head; //pointer to head of list1
	Node* temp2 = list2.head; //pointer to head of list2
	while(temp1 != NULL){
		list3.insert(temp1->coef,temp1->expo); 
		temp1 = temp1->next;
	}
	while(temp2 != NULL){
		list3.insert(temp2->coef,temp2->expo);
		temp2 = temp2->next;
	}
	cout<<"Exp1 + Exp2 = ";
	list3.display();
	cout<<"\n";
}
//=============================================================================
void PolyCalculator::sub(){
	list3.removeAll(); 
	Node* temp1 = list1.head;
	Node* temp2 = list2.head;
	while(temp1 != NULL){
		list3.insert(temp1->coef, temp1->expo);
		temp1 = temp1->next;
	}
	while(temp2 != NULL){ //we multiply the coefficients of the second polynomial expression then use the insert function to essentially perform subtraction
		int change_coef;
		change_coef = -1*temp2->coef;
		list3.insert(change_coef, temp2->expo);
		temp2 = temp2->next;
	}
	cout<<"Exp1 - Exp2 = ";
	list3.display();
	cout<<"\n";
}
//=============================================================================
void PolyCalculator::mul(){
	list3.removeAll(); 
	Node* temp1 = list1.head;
	Node* temp2 = list2.head;
	Node* temp3 = list3.head;
	while(temp1!=NULL){ //two while loops makes sure each term of polynomial expression 1 and 2 are multiplied to all terms in the other polynomial expression
		while(temp2!=NULL){
			int exponent;
			int coefficient;
			coefficient = temp1->coef*temp2->coef;
			exponent = temp1->expo + temp2->expo;
			list3.insert(coefficient,exponent);
			temp2 = temp2->next;
		} //move to next term
		temp2 = list2.head; //start at the beginning of 2nd polynomial
		temp1 = temp1->next;//move to the second position of 1st polynomial

	}
	cout<<"Exp1 * Exp2 = ";
	list3.display();
	cout<<"\n";
}
//=============================================================================
void PolyCalculator::readData(string filename){
	string pol1 = "";
	string pol2 = "";
	ifstream fin(filename);
	if(fin.is_open()){ //returns whether stream is currently associate with file
		getline(fin, pol1);
		this->parse(pol1, list1);
		getline(fin, pol2);
		this->parse(pol2, list2);
	}
	else{
		cout<<"No such file exists"<<endl;
	}
	fin.close();
}
//=============================================================================
void PolyCalculator::writeData(string filename){
	ofstream fout(filename); //declaring an output file stream & opens file
	Node* temp1 = list1.head; //creates a temporary node set as head
	Node* temp2 = list2.head;
	if(fout.is_open()){ //returns whether stream is currently associate with file
		fout<<"Exp1: "<<list1.helperfout();
		fout<<"\n";
		fout<<"Exp2: "<<list2.helperfout();
		fout<<"\n";
		display();
		add();
		fout<<"Exp1+Exp2: "<<list1.helperfout();
		fout<<"\n";
		sub();
		fout<<"Exp1-Exp2: "<<list1.helperfout();
		fout<<"\n";
		mul();
		fout<<"Exp1*Exp2: "<<list1.helperfout();
	}
	else{
		cout<<"File does not exist!";
	}
	fout.close();
}
//=============================================================================
