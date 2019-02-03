/*
 * utilities.cpp
 *
 * @author: Wade Madden
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "utilities.h"

using namespace std;
vector<process_stats> temp;
process_stats ans;
vector<process_stats> vec;

//clears vector holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to a vector
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename) {
	vec.clear();
	ans.cpu_time = 0;
	ans.process_number = 0;
	ans.start_time = 0;

	ifstream myfile;
	myfile.open(filename);
	if (!myfile) {
		return COULD_NOT_OPEN_FILE;
	}
	string temp;
	while (getline(myfile, temp)) {
		std::stringstream var(temp);
		int i = 0;
		while (getline(var, temp, ',')) {
			int t = std::stoi(temp);
			if (i == 0) {
				ans.process_number = t;
			} else if (i == 1) {
				ans.start_time = t;
			} else if (i == 2) {
				ans.cpu_time = t;
			}
			i++;
		}
		vec.push_back(ans);
	}
	return SUCCESS;
}

//attempt to open file 'filename' to write, and serialize a
//vector full of process_stats structs to it.  Should be in the same
//format as original file but not necessarily the same order or length
//if the file exists, overwrite its contents.
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int saveData(const char* filename) {
	ofstream myfile;
	myfile.open(filename);
	if (!myfile) {
		return COULD_NOT_OPEN_FILE;
	}
	myfile.clear();
	for (unsigned i = 0; i < vec.size(); i++) {
		string str;
		if (i == vec.size() - 1) {
			str = std::to_string(vec[i].process_number) + ","
					+ std::to_string(vec[i].start_time) + ","
					+ std::to_string(vec[i].cpu_time);
		} else {
			str = std::to_string(vec[i].process_number) + ","
					+ std::to_string(vec[i].start_time) + ","
					+ std::to_string(vec[i].cpu_time) + "\n";
		}
		myfile << str;
	}
	return SUCCESS;
}

//Helper method for sorting
//reduces code length
void sortHelper(int comp, int sort, process_stats y) {
	for (unsigned j = 0; j < vec.size(); j++) {
		int cal;
		if (sort == PROCESS_NUMBER) {
			cal = temp[j].process_number;
		} else if (sort == START_TIME) {
			cal = temp[j].start_time;
		} else if (sort == CPU_TIME) {
			cal = temp[j].cpu_time;
		}
		if (comp <= cal) {
			temp.insert(temp.begin() + j, y);
			break;
		} else if (temp.size() == 1) {
			temp.push_back(y);
			break;
		} else if (j == temp.size()) {
			temp.push_back(y);
			break;
		}
	}
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {
	for (unsigned i = 0; i < vec.size(); i++) {
		process_stats y = vec[i];
		if (temp.size() == 0) {
			temp.push_back(y);
		} else {
			if (mySortOrder == PROCESS_NUMBER) {
				sortHelper(y.process_number, mySortOrder, y);
			} else if (mySortOrder == START_TIME) {
				sortHelper(y.start_time, mySortOrder, y);
			} else if (mySortOrder == CPU_TIME) {
				sortHelper(y.cpu_time, mySortOrder, y);
			}
		}
	}
	vec = temp;
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats ret;
	if (!vec.empty()) {
		ret = vec.front();
		vec.erase(vec.begin());
	}
	return ret;
}
