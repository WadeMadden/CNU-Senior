/**
 * Authors:  Tyre King, Wade Madden
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../includes/data_store.h"
#include "../includes/data_store_file.h"
#include "../includes/string_data.h"


DataStore_File::DataStore_File(std::string fileName, Crypto* crypto):DataStore(crypto), myFileName(fileName){

}
DataStore_File::~DataStore_File(){

}



bool DataStore_File::save(std::vector<String_Data> &myVector){

	std::fstream myFile;
    openFile(myFile,myFileName, std::ios_base::out);
    if(myVector.empty()){
    	std::cout<<"Ya dude... EMPTY"<<std::endl;
    }
    for(unsigned int i = 0; i< myVector.size();i++){
    	std::string word = myVector.at(i).serialize();
    	encrypt(word);
    	//std::cout<<word<<std::endl;
    	myFile<<word<<std::endl;
    }

   closeFile(myFile);

    return true;
}





bool DataStore_File::load(std::vector<String_Data> &myVector){
    std::fstream myFile;
    std::string filename = myFileName;
    std::string line;
    String_Data hold("",0);
    std::string hold_deez ="";
    int num =0;
    openFile(myFile,filename, std::ios_base::in);
    while(std::getline(myFile,line)){
    	decrypt(line);
    	hold.parseData(line,hold_deez, num );
    	String_Data temp(hold_deez, num);
    	myVector.push_back(temp);
    }
    closeFile(myFile);

    return true;
}
bool DataStore_File::openFile(std::fstream& myfile,const std::string& myFileName, std::ios_base::openmode mode){
    if(myfile.is_open()){
            myfile.close();
    }
    myfile.open(myFileName.c_str(),mode);
    return myfile.is_open();
}
void DataStore_File::closeFile(std::fstream& myfile){
    if(myfile.is_open()){
            myfile.close();
    }
}
