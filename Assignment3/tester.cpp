/*
 * tester.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: wade
 */

#include "tester.h"
#include "print_ts.h"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

using namespace std;
bool cancelIt = false;

std::vector<std::thread> threads;
mutex m;
void print(string s, WHICH_PRINT wp) {

	switch (wp) {
	case P1: {
		PRINT1(s);
		break;
	}
	case P2: {
		PRINT2(s, s);
		break;
	}
	case P3: {
		PRINT3(s, s, s);
		break;
	}
	case P4: {
		PRINT4(s, s, s, s);
		break;
	}
	case P5: {
		PRINT5(s, s, s, s, s);
		break;
	}
	default:
		break;
	}
}

void checkIfCancel(int timesToPrint, string s, WHICH_PRINT wp) {
	int i = 0;
	while (!cancelIt) {
		std::lock_guard<std::mutex> lock { m };

		if (i < timesToPrint) {
			print(s, wp);
			i++;
		}
	}
	cout << USER_CHOSE_TO_CANCEL << endl;

}
/*
 * starts cancelable threads
 * string s			-the string to print
 * numThreads 		-the number of threads to start
 * wp 				-which print statement should be used
 * numTimesToPrint 	-the number of PRINT statements each thread will call
 * millisecond_delay- how long (in milliseconds) to wait between prints
 */

void startThreads(std::string s, int numThreads, WHICH_PRINT wp,
		int numTimesToPrint, int millisecond_delay) {

	for (int i = 0; i < numThreads; ++i) {
		cout << "Thread " << i << endl;
		m.lock();
		threads.push_back(std::thread(checkIfCancel, numTimesToPrint, s, wp));
		m.unlock();

	}
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecond_delay));
}

/*
 * if bCanceled== true then causes all running threads to print USER_CHOSE_TO_CANCEL and then exit
 * if false then just reset logic used to cancel threads
 */
void setCancelThreads(bool bCancel) {
	if (bCancel) {
		cancelIt = bCancel;
	}

}

/*
 * waits for all threads to complete
 */
void joinThreads() {
	for (auto& th : threads)
		if (th.joinable()) {
			th.join();
		}
}

