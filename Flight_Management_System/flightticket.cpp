#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<sstream>
#include "flighthashtable.h"
using namespace std;

Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date)
{
	this->companyName = companyName;
	this->flightNumber = flightNumber;
	this->country_of_origin = country_of_origin;
	this->country_of_destination = country_of_destination;
	this->stopOver = stopOver;
	this->price = price;
	this->time_of_departure = time_of_departure;
	this->time_of_arrival = time_of_arrival;
	this->date = date;
};

Flight_Ticket::Flight_Ticket(){};

//====================================
bool Flight_Ticket::compare(Flight_Ticket *data){
	if(this->companyName != data->companyName){
		return false;
	} 
	else if(this->flightNumber != data->flightNumber){
		return false;
	}
	else if(this->country_of_origin != data->country_of_origin){
		return false;
	}
	else if(this->country_of_destination != data->country_of_destination){
		return false;
	}
	else if(this->stopOver != data->stopOver){
		return false;
	}
	else if(this->price != data->price){
		return false;
	}
	else if(this->time_of_departure != data->time_of_departure){
		return false;
	}
	else if(this->time_of_arrival != data->time_of_arrival){
		return false;
	}
	else if(this->date != data->date){
		return false;
	}
return true;
}

void Flight_Ticket::print(){
	cout<<this->companyName<<","<<this->flightNumber<<","<<this->country_of_origin<<","<<this->country_of_destination<<","<<this->stopOver<<","<<this->price<<","<<this->time_of_departure<<","<<this->time_of_arrival<<","<<this->date<<endl;
}

