/*
 * main.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: wade
 */

#include"tester.h"

int main(){
	startThreads("s",3,P5,2,1000);
	//startThreads("t",3,P5,2,1000);
	setCancelThreads(true);
	joinThreads();

}

