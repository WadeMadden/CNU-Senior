/**
 * Authors:  Tyre King, Wade Madden
 */


#include <string>
#include <vector>
#include <mutex>
#include <algorithm>
#include "../../datastore/includes/string_data.h"
#include "../../datastore/includes/data_store_file.h"
#include "../includes/string_database.h"

//need to have mutex in this function for all the critical code


	String_Database::String_Database(void){

	}

	String_Database::~String_Database(void){

	}
	//if not seen yet then add myString to myStrings
		//otherwise increment the count for myString
	void String_Database::add(std::string &myString){

		String_Data noop(myString);
		std::lock_guard<std::mutex> lck(mutex);


			bool check = false;

			for(int j = 0 ;j<myStrings.size(); j++){
				if(myStrings[j]== myString){
					myStrings[j].increment();
					check = true;
				}
			}
			if(!check){
				myStrings.push_back(noop);
		}





	}

	 int String_Database::getCount(std:: string &myString){
		 std::lock_guard<std::mutex> lck(mutex);
		 for(unsigned int i=0; i<myStrings.size();i++){
			 if(myStrings.at(i)==  myString){
				 int index = std::distance(myStrings.begin(),myStringsIter);
				 	return index;
			 }


		 }


	 }

	 void String_Database::clear(){
		myStrings.clear();

	 }

	 bool String_Database::load(DataStore *myDataStore){
		 std::lock_guard<std::mutex> lck(mutex);
		 if(myDataStore == NULL){
			 return false;
		 }
		 return(myDataStore->load(myStrings));

	 }

	 bool String_Database::save(DataStore *myDataStore){
		 std::lock_guard<std::mutex> lck(mutex);
		 if(myDataStore == NULL){
			 return false;
		 }
		 return(myDataStore->save(myStrings));
	 }
















//private:
//	std::mutex mutex;
//	std::vector<String_Data> myStrings;
//	std::vector<String_Data>::iterator  myStringsIter;
