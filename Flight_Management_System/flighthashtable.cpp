#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<sstream>
#include<math.h>
#include <time.h>
#include "flighthashtable.h"
#include "MyList.h"
using namespace std;

//=============================================================================
FlightHASHTABLE::FlightHASHTABLE(int capacity){//contructor 
	this->capacity = capacity;
	this->size = 0;
	this->probes = 0;

	buckets = new MyList<HashNode>[capacity]; 
	allindee = new MyList<HashNode>[capacity];
}
//=============================================================================
FlightHASHTABLE::~FlightHASHTABLE(){
	for(int i = 0; i < capacity; i++){ 
		while(!buckets[i].empty()){ //as long as it's not empty
			buckets[i].removeFront(); //continue to pop back 
		}
	}//the for loop will allow to clear the bucket array of each index
	delete [] buckets;

	for(int i = 0; i < capacity; i++){ 
		while(!allindee[i].empty()){ //as long as it's not empty
			allindee[i].removeFront(); //continue to pop back 
		}
	}//the for loop will allow to clear the bucket array of each index
	delete [] allindee;
}
//=============================================================================
long FlightHASHTABLE::hashCode(string key){ //polynomial_2
	
	unsigned long a = 1317375;
	unsigned long b = 27351381;
	long s_h = 0;
	for(int i = 0; i < key.size(); i++){ //cutting key into multiple pieces 
		s_h = s_h*b + (key[i]); //multiplying ascii code or value of key (bit) by value / it is multiplied each time
		b = a*b; //b*a^i
	}
	return s_h;
}
//=============================================================================
int FlightHASHTABLE::importCSV(string path){
	ifstream fin(path);
	string line = "";
	int number = 0;

	if (fin.is_open()) {
		getline(fin,line);
		while (getline(fin, line)) { //getting input

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
			string quote;

			stringstream fin2(line);
	             // You now have separate entites here
				//storing imported details into vars
				getline(fin2, companyName, ',');
				getline(fin2,temp,','); //takes comma with

				if(fin2.peek() == '"'){ //if there is a comma in the country of origin
					getline(fin2,quote,'"');//getrid of quote
					getline(fin2,country_of_origin, '"');
					getline(fin2,quote,',');//getrid of comma
				}
				else{
					getline(fin2,country_of_origin, ',');
				}

				if(fin2.peek() == '"'){//if there is a comma in the country of destination
					getline(fin2,quote,'"'); //getrid of quote
					getline(fin2,country_of_destination, '"');
					getline(fin2,quote,',');//getrid of comma
				}
				else{
					getline(fin2,country_of_destination, ',');
				}
				getline(fin2, stopOver, ',');
				getline(fin2, price, ',');
				getline(fin2, time_of_departure, ',');
				getline(fin2, time_of_arrival, ',');
				getline(fin2, date);
				
			

			string key1 = companyName + "," + temp; //creating key for buckets
			date.pop_back(); //there was an extra space
			string key2 = date; //second key for allinday function

			flightNumber = stoi(temp); //cast temp as integer
			Flight_Ticket *ticket = new Flight_Ticket(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date); //creating flight ticket object
			line = ""; //clearing line
			
			add(key1, ticket); //adding it to buckets array of lists
			add_date(key2, ticket); //adding it to allindee array of lists
			number++;
		} 
	cout<<number<<" flight schedules imported"<<endl; //will print out the number of flight schedules that were imported
	return number;
	}

	else {
		cout<<"File does not exist!"<<endl;
		return -1;
	}
}
//=============================================================================
int FlightHASHTABLE::exportCSV(string path){
	int num_lines = 0; //coutner for number of lines
	ofstream fout;
	fout.open(path, ios::app); //openfile
	string fav = "";
	for(int i = 0; i < capacity; i++){
		if(!buckets[i].empty()){
			HashNode* p = buckets[i].front(); //pseudo iterator to go through lists
			while(p != NULL){
				if(p->data.country_of_origin.find(',') == string::npos && p->data.country_of_destination.find(',') == string::npos){ //there are no commas
					fout<<p->data.companyName<<","<<to_string(p->data.flightNumber)<<","<<p->data.country_of_origin<<","<<p->data.country_of_destination<<","<<p->data.stopOver<<","<<p->data.price<<","<<p->data.time_of_departure<<","<<p->data.time_of_arrival<<","<<p->data.date<<"\n";
					num_lines++;	
				}
				else if(p->data.country_of_origin.find(',') == string::npos && p->data.country_of_destination.find(',') != string::npos){//there is comma in country of destination
					fout<<p->data.companyName<<","<<to_string(p->data.flightNumber)<<","<<p->data.country_of_origin<<","<<'"'<<p->data.country_of_destination<<'"'<<","<<p->data.stopOver<<","<<p->data.price<<","<<p->data.time_of_departure<<","<<p->data.time_of_arrival<<","<<p->data.date<<"\n";
					num_lines++;	
				}
				else if(p->data.country_of_origin.find(',') != string::npos && p->data.country_of_destination.find(',') == string::npos){//there is comma in country of destination
					fout<<p->data.companyName<<","<<to_string(p->data.flightNumber)<<","<<'"'<<p->data.country_of_origin<<'"'<<","<<p->data.country_of_destination<<","<<p->data.stopOver<<","<<p->data.price<<","<<p->data.time_of_departure<<","<<p->data.time_of_arrival<<","<<p->data.date<<"\n";
					num_lines++;	
				}
				else{ //there are commas in both
					fout<<p->data.companyName<<","<<to_string(p->data.flightNumber)<<","<<'"'<<p->data.country_of_origin<<'"'<<","<<'"'<<p->data.country_of_destination<<'"'<<","<<p->data.stopOver<<","<<p->data.price<<","<<p->data.time_of_departure<<","<<p->data.time_of_arrival<<","<<p->data.date<<"\n";
					num_lines++;
				}
				p = p->next;
			}
		}
	}
	fout.close();
return num_lines;
}
//=============================================================================
int FlightHASHTABLE::add(string key, Flight_Ticket *data){
	int index = hashCode(key) % capacity;
	index = abs(index);
    HashNode* tempo = new HashNode(key,*data);
	bool flag = true;

	if(buckets[index].empty()){
		buckets[index].add_front(tempo);
		return 1;

	}
	HashNode* i = buckets[index].front(); //iterator to go through bucket list
	while(i != NULL){
		if(i->key == key && (i->data.compare(data))){//if they have the same value 
			cout<<"Warning: the record already exists in the system!"<<endl;
			return -1; //value already exists
		}
		else if(i->key == key){
			flag = false;
		}
		i = i->next;
	}

	buckets[index].add_front(tempo); //I get a segmentation fault here in some runs but not others at different lines of the csv file
	size++; //increase # of entries in hash table

	if(flag){
		probes++;
	}
	return 1;

}
//=============================================================================
int FlightHASHTABLE::add_date(string key,Flight_Ticket *data){
	int index = hashCode(key) % capacity;
	index = abs(index);
	HashNode* temp = new HashNode(key,*data);
	allindee[index].add_front(temp); //segmentation fault here: is it bcs im working with pointer
	size++; //increase # of entries in hash table

	HashNode* current = allindee[index].front();
	if(allindee[index].size() > 1){
		bool swap;
		do
		{
			current = allindee[index].front();	//reset current to the head (for next round)
			swap = false;
			while(current->next != NULL){
				string curr_tod = current->data.time_of_departure;
				stringstream fin3(curr_tod); //trying to cut current node's time of departure into hour & mins
				string curr_tod1;
				string curr_tod2;
				getline(fin3,curr_tod1,':');
				getline(fin3,curr_tod2);
				string curr_next_tod = current->next->data.time_of_departure;
				stringstream fin4(curr_next_tod); //trying to cut current->next's node's time of departure into hour & mins
				string curr_next_tod1;
				string curr_next_tod2;
				getline(fin4,curr_next_tod1,':');
				getline(fin4,curr_next_tod2);
				if(stoi(curr_tod1) > stoi(curr_next_tod1)){ //comparing the hours
					Flight_Ticket temp = current->data; //store data in temporary flight-ticket
					string temp_key = current->key; //store key in temporary string
					current->data = current->next->data; //swap data
					current->key = current->next->key; //swap key
					current->next->data = temp; //reassign data
					current->next->key = temp_key; //reassign key
					swap = true;
				}
				else if(stoi(curr_tod1) == stoi(curr_next_tod1) && stoi(curr_tod2) > stoi(curr_next_tod2)){ //comparing minutes
					Flight_Ticket temp = current->data;
					string temp_key = current->key;
					current->data = current->next->data;
					current->key = current->next->key;
					current->next->data = temp;
					current->next->key = temp_key;
					swap = true;
				}
				current = current->next;    //move the current node
			}
		}
		while(swap);
	}
	return 1;
}
//=============================================================================
void FlightHASHTABLE::removeRecord(string companyName, int flightNumber){	
	string fli_num = to_string(flightNumber);
	string key = companyName + "," + fli_num;
	int index = hashCode(key) % capacity;
	index = abs(index);
	bool val = true;
	int count = 1;
	int num = 0;
	HashNode* i = buckets[index].front(); //set the pointer to the front of list


	while(i != NULL){
		if(i->key == key){ //if the key is the same
			val = true;
			cout<<count<<".";
			i->data.print(); //print the results
			count++;
		
		}
		i = i->next;
	}

	if(val && count > 2){
		cout<<count-1<<" records found."<<endl;
		string choice = "";
		cout<<"Which one would you like to delete?"<<endl;
		bool flag = true;
		do{ //choice validation
				flag = true;
				getline(cin,choice);

				for(int i = 0; i < choice.length();i++){
					if (!isdigit(choice[i])){
						flag = false;
						break;
					}
				}

				if(flag != false){
					if(stoi(choice)<0 || stoi(choice) > count){
						flag = false;
					}
				}

				if(!flag){
					cout<<"Please enter a valid option: "<<endl;
				}
			}
			while(!flag);


		i = buckets[index].front(); //bring iterator back to front 
		count  = 0;
		num = 0;
		while(i != NULL){
			num++; //here to count where the index in the bucker[index] list we need to delete the element
			if(i->key == key){
				count++;
			}
			if(i->key == key && count == stoi(choice)){
				remove_helper(buckets[index].getelem(num-1)); //will delete it in the allindee[index] list
				buckets[index].removePos(num-1);
				cout<<"The flight-ticket record for "<<key<<" has been removed."<<endl;
				size--;
				return;
			}
			i = i->next; //move i
		}
	}
	else if(val && count == 2){
		buckets[index].removePos(0);
		size--;
		cout<<"The flight-ticket record for "<<key<<" has been removed."<<endl;
		return;
	}
	else{
		cout<<"No such record exists!"<<endl;
	}	
}
//=============================================================================
void FlightHASHTABLE::remove_helper(HashNode* node){ //get node that is deleted from remove record & search through allindee to delete it 
	string key = node->data.date;
	int index = hashCode(key) % capacity;
	index = abs(index);
	HashNode* i = allindee[index].front();
	int num = 0;

	while(i != NULL){ //finding the record 
		if(i->key == key && i->data.compare(&node->data)){ //if they are idential
			allindee[index].removePos(num); //delete it
		}
	i = i->next;
	num++;
	}
}
//=============================================================================
int FlightHASHTABLE::count_collisions()
{
	return probes; //number of collisions
}
//=============================================================================
void FlightHASHTABLE::find(string companyName, int flightNumber){
	clock_t start, end;
	
	string strflight = to_string(flightNumber);
	string key = companyName + "," + strflight;
	int count = 1;
	bool flag = false;
	int index = hashCode(key) % capacity; //get index
	index = abs(index);
	HashNode* i = buckets[index].front();

	if(buckets[index].size() == 0){ //if the bucket is empty then the record does not exist
		cout<<"No such flight info. exists!"<<endl;
		return;
	}
	else{
		start = clock();
		while(i != NULL){
			if(i->key == key){ //when the value in the bucket is found //same index but not being found why?
				cout<<count<<".";
				i->data.print(); //printing out results
				count++;
				flag = true;
			 }
		i = i->next;
		}
	}
	
	

	if(flag){ //displays time taken when the record exists
		cout<<count-1<<" record(s) found."<<endl;
		end = clock();
		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout<<"Time taken : "<<fixed<<time_taken<<setprecision(5)<<"second(s)."<<endl;
	}
	else if(!flag){
		cout<<"No such flight info. exists!"<<endl;
	}
}
//=============================================================================
void FlightHASHTABLE::allinday(string date){
	int index = hashCode(date) % capacity;
	index = abs(index);
	HashNode* i = allindee[index].front(); //pseudo iterator
	int count = 1;
	bool flag = false;

	while(i != NULL){
		if(i->key == date){ //find the date as date is the key
			cout<<count<<".";
			i->data.print();
			count++;
			flag = true;
		}
		i = i->next;
	}


	if(!flag){
		cout<<"No flights exist on that date!"<<endl;
	}
	else{
		cout<<count-1<<" records found."<<endl; //count-1 since it starts at 1
	}
}
//=============================================================================
void FlightHASHTABLE::printASC(string companyName, int flightNumber){
	string strflight = to_string(flightNumber);
	string key = companyName + "," + strflight;
	int index = hashCode(key) % capacity; //get index
	index = abs(index);
	int count = 0;

	if(buckets[index].empty()){
		cout<<"No such record exists!"<<endl;
		return;
	}

	HashNode* i = buckets[index].front();
	MyList<HashNode> temp;

	while(i != NULL){
		if(i->key == key){
			HashNode* temp_node = new HashNode(i->key,i->data); //creates a temporary node & adds it to temporary list
			temp.add_front(temp_node);
		}
		i = i->next;
		count++;
	}

	HashNode* current = temp.front();
	if(temp.size() > 1){ //when there's more than one value
		bool swap;
		do
		{
			current = temp.front();		//reset current to the head (for next round)
			swap = false;
			while(current->next != NULL){
				if(current->data.country_of_destination > current->next->data.country_of_destination){
					Flight_Ticket temp = current->data; //don't need to swap key since the key is the same in the temp list
					current->data = current->next->data;
					current->next->data = temp;
					swap = true;
				}
				current = current->next;    //move the current node
			}
		}
		while(swap);
	}
	else{
		current->data.print();
		return;
	}
	

	current = temp.front();
	while(current != NULL){ //print from the beginning
		current->data.print();
		current = current->next;
	}
}
//=============================================================================
