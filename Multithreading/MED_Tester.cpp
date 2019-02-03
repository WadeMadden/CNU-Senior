//============================================================================
// Name        : MED_Tester.cpp
// Author      : Tyre King, Wade Madden
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <sstream>
#include "pthread.h"
#include "../../datastore/includes/data_store_file.h"
#include "../../datastore/includes/string_data.h"
#include "../../crypto/includes/crypto.h"
#include "../../crypto/includes/crypto_AES.h"
#include "../../datastore/includes/data_store.h"
#include "../../stringdatabase/includes/string_database.h"
//I've provided some hints in the form of comments and commented out code
//use them if you wish

//	global database object;
String_Database myGlobalCache;
const string file1 = "loadfile.txt";
	const string file2 ="savefile.txt";
	const string file3 ="input.txt";
	const string file4 ="output2.txt";
Crypto *pCrypto;
bool testSerialization(const std::string &MYFILE1, const std::string &MYFILE2,
		Crypto *pCrypto) {
	DataStore_File myDataStore_File1(MYFILE1, pCrypto);
	myGlobalCache.save(&myDataStore_File1);

	//clear cache
	myGlobalCache.clear();
		std::cout<<"Clearing Cache\n";

	//load itz
	myGlobalCache.load(&myDataStore_File1);
		std::cout<<"Loading from file "+ MYFILE1 +" \n";

	//save to a different file
	DataStore_File myDataStore_File2(MYFILE2, pCrypto);
	myGlobalCache.save(&myDataStore_File2);
		std::cout<<"Saving to file "+ MYFILE2 +" \n";

//	I use my own objects here to compare the files
	return true;
}
 void addme(string  d){

	for(int j = 0;j < 5; j++){
		myGlobalCache.add(d);

	}

}

int main() {
	const string one = "one";
	const string two = "two";
	const string three = "three";
	const string four = "four";



	std::vector<string> strings;
	strings.push_back(one);
	strings.push_back(two);
	strings.push_back(three);
	strings.push_back(four);
	std::vector<thread> myThreads;

	for(int i =0; i< 4;i++){
		myThreads.push_back(thread(addme,strings.at(i)));
	}




	for(auto& thread: myThreads){
		thread.join();
	}


	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	//I created and ran a bunch(20) of threads that added different strings to a string_database instance

	//Then I waited for all of them to finish so my program did not crash

	//Then I went through my string_database instance and made sure that it held the correct data

	//then I tested  serialization
	//first without encryption, 
	testSerialization(file3,file4, 0);

	//then with
	Crypto_AES myCrypto("I Like Rollos   ");
	testSerialization(file1, file2, &myCrypto);
}
