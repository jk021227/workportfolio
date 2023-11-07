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

Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav)
{
	this->fname = fname;
	this->lname = lname;
	this->email = email;
	this->primaryPhone = primaryPhone;
	this->city = city;
	this->country = country;
	this->isFav = isFav;
}

