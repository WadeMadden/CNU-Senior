/**
 * Authors:  Tyre King, Wade Madden
 */
#include <string>
#include <vector>
#include "../../crypto/includes/crypto.h"
#include "../includes/string_data.h"
#include "../includes/data_store.h"
#include "../includes/string_data.h"


bool DataStore::decrypt(std::string &myString) {
	if(myCrypto ){
		return myCrypto->decrypt(myString);
	}

	return false;

}
bool DataStore::encrypt(std::string &myString) {
	if(myCrypto ){
		return myCrypto->encrypt(myString);
	}
	return false;

}






  DataStore::DataStore(Crypto *pCrypt):myCrypto(pCrypt){

  }
   DataStore::~DataStore(){

  }

