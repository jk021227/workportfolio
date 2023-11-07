
//=================================================================================
// Name         : DS Assignment#4 
// Author       : 
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<regex>
#include<string>
#include <math.h>
#include<iomanip>
#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"help       	    	:re-display menu"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE(150007); 
	listCommands();

	string user_input;
	string command;
	string string1;
	string string2;
	
	string companyName;
	int flightNumber;
	string temp;
	string country_of_origin;
	string country_of_destination;
	string stopOver;
	string price;
	string time_of_departure;
	string time_of_arrival;
	string date;
	bool flag;

	do{
		cout<<">";
		getline(cin, user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,string1, ',');
		getline(sstr,string2);

		// cout<<command<<endl;
		// cout<<string1<<endl;
		// cout<<string2<<endl;
		
		try
		{
			if(command=="import" or command=="im"){
				int re = myFlightHASHTABLE.importCSV(string1);//try to work with this to resize table
			} 				
			 else if(command=="export" or command=="ex" ){
			 	int val = myFlightHASHTABLE.exportCSV(string1);
			 	cout<<val<<" contact(s) exported."<<endl;
			}
			else if(command=="count_collisions" or command=="c"){
				cout<<"The number of collision(s) is/are "<<myFlightHASHTABLE.count_collisions()<<endl;
			}
			else if(command=="add" or command=="a"){
				cout<<"Please enter the details of the flight-ticket: "<<"\n"<<"Company Name: ";

				do{ //checking input validity for company name
					flag = true;
					getline(cin,companyName);

					if(companyName.length() == 0){ //if they enter nothing
						flag = false;
					}
					
					for(int i = 0; i < companyName.length(); i++){ //checking input for first name is fully in alphabet
						if(!isalpha(companyName[i]) && companyName[i] != ' '){ //allowed spaces since some names have them
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the Company Name in a valid format: ";
					}
				}
   				while(!flag);

   				companyName[0] = toupper(companyName[0]); //this is done so that the contact is stored in the same node despite case sensititivty
				//--------------------------------------------

				cout<<"Flight Number: ";
				
				do{
					flag = true;
					getline(cin,temp);
					
					if(temp.length() == 0){ //if they enter nothing
						flag = false;
					}

					for(int i = 0; i < temp.length(); i++){ //checking input for last name is fully in numbers
						if(!isdigit(temp[i])){ 
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the Flight Number in a valid format: ";
					}
				}
   				while(!flag);


   				flightNumber = stoi(temp); //casting string into an int after checking all characters is a number

   				//--------------------------------------------
				
				cout<<"Country of Origin: ";

				do{
					flag = true;
					getline(cin,country_of_origin);
					
					for(int i = 0; i < country_of_origin.length(); i++){ //making sure the country input does not contain things that are not alphabets
						if(!isalpha(country_of_origin[i]) && country_of_origin[i] != ' '){ //country can have a space in between
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the Country of Origin in a valid format(e.g. make sure it is in English, does not contain special characters or numbers etc.): "<<endl;
					}
				}
   				while(!flag);

   				//--------------------------------------------
				
				cout<<"Country of Destination: ";

				do{
					flag = true;
					getline(cin,country_of_destination);
					
					for(int i = 0; i < country_of_destination.length(); i++){ //making sure the country input does not contain things that are not alphabets
						if(!isalpha(country_of_destination[i]) && country_of_destination[i] != ' '){ //country can have a space
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the Country of Destination in a valid format(e.g. make sure it is in English, does not contain special characters or numbers etc.): "<<endl;
					}
				}
   				while(!flag);

				//--------------------------------------------

				cout<<"Stopover: ";
				
				do{
					flag = true;
					getline(cin,stopOver);
					
					for(int i = 0; i < stopOver.length(); i++){  //checking if it's digits
						if(!isdigit(stopOver[i])){
							flag = false;
						}
					}

					if(!flag){
					cout<<"Please enter stopover in a valid format: ";
					}
				}
   				while(!flag);

				//--------------------------------------------
				cout<<"Price: ";
				
				do{
					flag = true;
					getline(cin,price);
					
					for(int i = 0; i < price.length(); i++){ //checking input for last name is fully in numbers
						if(!isdigit(price[i])){ 
							flag = false;
						}
					}
					if(!flag){
						cout<<"Please enter the Price in a valid format: ";
					}
				}
   				while(!flag);

   				//--------------------------------------------
				cout<<"Time of Departure: ";
				const regex pattern("([01]?[0-9]|2[0-3]):[0-5][0-9]");
				
				do{
					flag = true;
					getline(cin,time_of_departure);

					if(regex_match(time_of_departure,pattern)){ //checking if it is in correct patter via regex
						
					}
					else{
						cout<<"Please enter the Time of Departure in a valid format: "; 
					}
				}

				while(!regex_match(time_of_departure,pattern));


				//--------------------------------------------

				cout<<"Time of Arrival: ";

				do{
					flag = true;
					getline(cin,time_of_arrival);

					if(regex_match(time_of_arrival,pattern)){ //same with previous
						
					}
					else{
						cout<<"Please enter the Time of Arrival in a valid format: ";
					}
				}

				while(!regex_match(time_of_arrival,pattern));

				//--------------------------------------------
				cout<<"Please enter the date in the format date/month. *The month should be in a three letter abbreviation*"<<endl;
				cout<<"Date: ";

				do{
					string day = "";
					string month = "";
					flag = true;
					getline(cin,date);

					for(int i = 0; i < date.size(); i++){ //storing the numbers into date as long as it is a digit
						if(isdigit(date[i])){
							day += date[i];
						}
						else{
							break;
						}
					}
					for(int i = 0; i < date.size(); i++){ //storing the alphabets into month as long as it is alpha
						if(isalpha(date[i])){
							month += date[i];
						}
					}

					if(stoi(date) > 31 || stoi(date) < 0) { //checking day parameters
						flag =	false;
					}

					if(month.length() != 3){ //month should be abbreviated
						flag = false;
					}

					month[0] = toupper(month[0]); //making the month capital

					if ((month != "Jan" && month != "Feb" && month != "Mar" && month != "Apr" 
					    && month != "May" && month != "Jun" && month != "Jul" && month != "Aug" 
					    && month != "Sep" && month != "Oct" && month != "Nov" && month != "Dec")){    
						flag = false;
					} //checking for all the months

					if(!flag){
						cout<<"Please enter the Date in a valid format: ";
					}
					else{
						date = day+month; //collating it 
					}
				}

				while(!flag);

				
				//--------------------------------------------

				string hashnode_key = companyName + "," + temp; //creating key
				string hashnode_key2 = date; //creating key for allinday function
				Flight_Ticket *ticket = new Flight_Ticket(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date); //creating flight ticket object
				if(myFlightHASHTABLE.add(hashnode_key, ticket) == 1 && myFlightHASHTABLE.add_date(hashnode_key2, ticket) == 1){ //adding it to hashtable 
					cout<<"Flight-ticket has been successfully added!"<<endl;
				}				
			}

			else if(command=="delete" or command=="d"){
				int flightnum = stoi(string2); //casting string as integer as flightnum needs to be an int
				myFlightHASHTABLE.removeRecord(string1, flightnum);	
			}		 
			else if(command=="find" or command=="f"){
				int flightnum = stoi(string2); //casting string as integer as flightnum needs to be an int
				myFlightHASHTABLE.find(string1, flightnum);
			}	
			else if(command=="printASC" or command=="pa"){
				int flightnum = stoi(string2); //casting string as integer as flightnum needs to be an int
				myFlightHASHTABLE.printASC(string1, flightnum);
			}		
			else if(command=="allinday" or command=="al")	    myFlightHASHTABLE.allinday(string1);
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
