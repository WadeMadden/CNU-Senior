#include <string>
#include "stdlib.h"
#include "../includes/externs.h"

#include "../includes/waiter.h"

using namespace std;
ORDER myOrder;
Waiter::Waiter(int id, std::string filename) :
		id(id), myIO(filename) {
}

Waiter::~Waiter() {
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder) {
	int result = myIO.getNext(anOrder);
	if (result == SUCCESS) {

		return SUCCESS;
	}
	return NO_ORDERS;
}

void Waiter::beWaiter() {
	ORDER anOrder;

	while (myIO.getNext(anOrder) == SUCCESS) {
		{
			unique_lock<mutex> lck(mutex_order_inQ);
			order_in_Q.push(anOrder);
			cout<<"Order "<<anOrder.order_number<<" was added"<<endl;
			//cv_order_inQ.wait(lck);
		}
		cv_order_inQ.notify_all();
	}
	{
		unique_lock<mutex> lck(mutex_order_inQ);
		b_WaiterIsFinished = true;
		cout<<"Waiter is Done"<<endl;
	}
	//cv_order_inQ.wait(lck);
	cv_order_inQ.notify_all();
}
