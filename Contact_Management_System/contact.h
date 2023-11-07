#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
using namespace std;

class Contact
{
	private:
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		bool isFav;

	public:
		Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav);
		friend class Node;
		friend class ContactBST;	
};

#endif