
//=================================================================================
// Name         : DS Assignment#2 
// Author       : 
// Version      : 1.0
// Date Created : 07-11-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
//=================================================================================
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<regex>
#include<cstdlib>
#include<sstream>
#include<stdexcept>
#include <iomanip>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"
using namespace std;
//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"remove <key>       :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markFav <key>      :Mark as favourite"<<endl
		<<"unmarkFav <key>    :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printFav           :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
int main(void)
{
	ContactBST bst;
	listCommands();
	string user_input;
	string command;
	string string1; //this is for key & path
	
	string fname; 
	string lname;
	string email;
	string primaryPhone;
	string city;
	string country;
	string temp;
	bool isFav;
	bool flag;

	do{
		cout<<">";
		getline(cin, user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,string1);


		
		try
		{
			if(command=="import" or command=="im") 				bst.importCSV(string1);
			else if(command=="export" or command=="ex" ){
				int val = bst.exportCSV(bst.getRoot(),string1);
				cout<<val<<" contact(s) exported."<<endl;
			}
			else if(command=="add" or command=="a"){
				cout<<"Please enter the first name: "<<endl;

				do{
					flag = true;
					getline(cin,fname);
					
					for(int i = 0; i < fname.length(); i++){ //checking input for first name is fully in alphabet
						if(!isalpha(fname[i]) && fname[i] != ' '){ //allowed spaces since some names have them(e.g. some people have two or more first names)
							flag = false;
						}
					}
					if(!flag){
					cout<<"Please enter the first name in a valid format: "<<endl;
					}
				}
   				while(!flag);

   				fname[0] = toupper(fname[0]); //this is done so that the contact is stored in the same node despite case sensititivty
	   				for(int i = 1; i < fname.length(); i++){
	   					fname[i] = tolower(fname[i]);
	   				}
				//--------------------------------------------

				cout<<"Please enter the last name: "<<endl;
				
				do{
					flag = true;
					getline(cin,lname);
					
					for(int i = 0; i < lname.length(); i++){ //checking input for last name is fully in alphabet
						if(!isalpha(lname[i]) && lname[i] != ' '){ //allowed spaces since some names have them(e.g. some people have two or more last names)
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the last name in a valid format: "<<endl;
					}
				}
   				while(!flag);

				lname[0] = toupper(lname[0]); //same with fname, so that they get stored in the same node despite case sensitivity
   				for(int i = 1; i < lname.length(); i++){
   					lname[i] = tolower(lname[i]);
   				}
   				lname[0] = toupper(lname[0]);

   				//--------------------------------------------
				
				cout<<"Please enter the email: "<<endl;
				const regex pattern1("(\\w+)@(\\w+)(\\.(\\w+))+"); //pattern1 e.g. yk2606@gmail.com
				const regex pattern2("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); //pattern2 e.g. yk_as@gmail.com & yk.im@gmail.com
				

				do{
					getline(cin,email);

					if(regex_match(email,pattern1)){
						
					}

					else if(regex_match(email,pattern2)){
						
					}
					else{
						cout<<"Please enter a valid email: "<<endl;
					}
				}

				while(!regex_match(email,pattern1) and !regex_match(email,pattern2));

				//--------------------------------------------

				cout<<"Please enter the phone number: "<<endl;
				
				do{
					flag = true;
					getline(cin,primaryPhone);
					
					for(int i = 1; i < primaryPhone.length(); i++){ //making sure that phone number only has digits aside from first index(could be +)
						if(!isdigit(primaryPhone[i])){
							flag = false;
						}
					}
					if(primaryPhone[0] != '+' && primaryPhone[0] != '0'){ //it has to start with a + or a 0
						flag = false;
					}

					if(primaryPhone.length() > 15 || primaryPhone.length() < 7){ //max. phone number length internationally is 15 & min. is 7
						flag = false;
					}
					if(!flag){
					cout<<"Please enter the phone number in a valid format: "<<endl;
					}
				}
   				while(!flag);

				//--------------------------------------------

				cout<<"Please enter the city: "<<endl;
				
				do{
					flag = true;
					getline(cin,city);
					
					for(int i = 0; i < city.length(); i++){ //making sure the city input does not contain things that are not alphabets
						if(!isalpha(city[i]) && city[i] != ' '){
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the city in a valid format(e.g. make sure it is in English, does not contain special characters or numbers etc.): "<<endl;
					}
				}

   				while(!flag);

				//--------------------------------------------

				cout<<"Please enter the country: "<<endl;
				
				do{
					flag = true;
					getline(cin,country);
					
					for(int i = 0; i < country.length(); i++){ //making sure the country input does not contain things that are not alphabets
						if(!isalpha(country[i]) && country[i] != ' '){
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the country in a valid format(e.g. make sure it is in English, does not contain special characters or numbers etc.): "<<endl;
					}
				}
   				while(!flag);

				//--------------------------------------------

				cout<<"Do you want to add the contact in your favorite(y/n): "<<endl;
				getline(cin,temp);
				
				while(temp != "y" && temp != "n" && temp != "Y" && temp != "N"){ //accounts for inpute of y or n, regardless of case sensitivity
					cout<<"Please enter 'y' or 'n': "<<endl;
					getline(cin, temp);
				}

				if(temp == "y" || temp == "Y"){
					isFav = true;
				}
				else{
					isFav = false;
				}

				//--------------------------------------------

				string node_key = fname + " " + lname; //creating key
				Contact* contact1 = new Contact(fname, lname, email, primaryPhone, city, country, isFav); //creating contact object
				bst.add(bst.getRoot(), node_key, contact1); //adding it to BST
				cout<<fname<<","<<lname<<","<<email<<","<<primaryPhone<<","<<city<<","<<country<<","<<isFav<<endl; //print out what is added
				cout<<"The above contact has been added to the database."<<endl;
			}

			else if(command=="edit" or command=="e")			bst.edit(bst.getRoot(), string1);
			else if(command=="remove" or command=="r"){
				if(bst.searchFor(bst.getRoot(),string1) != nullptr){ //call the function for both but in if, it prints out what was removed 
					bst.remove(bst.getRoot(),string1);
					cout<<"The contact "<<string1<<" has been removed."<<endl;	
				}
				else{ //if contact does not exist do nothing since nothing has been removed
					bst.remove(bst.getRoot(),string1);
				}
			}			 
			else if(command=="searchFor" or command=="s"){
				
				if(bst.searchFor(bst.getRoot(),string1) == nullptr){ //checking if contact even exists
					
					cout<<"There is no contact under the name: "<<string1<<endl;
				}
				else{
					bst.searchFor(bst.getRoot(),string1)->print();
				}
			}		
			else if(command=="markFav" or command=="m")         bst.markFav(string1);
			else if(command=="unmarkFav" or command=="u")       bst.unmarkFav(string1);
			else if(command=="printASC" or command=="pa")		bst.printASC(bst.getRoot());
			else if(command=="printDES" or command=="pd")	    bst.printDES(bst.getRoot());
			else if(command=="printFav" or command=="pf")       bst.printFav(bst.getRoot());
			else if(command == "help" or command=="?")			listCommands();
			else if(command == "exit" or command=="quit")		break;
			else cout<<"Invalid Command !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}
	while(command!="exit" and command!="quit");

	return 0;
}
//==========================================================

