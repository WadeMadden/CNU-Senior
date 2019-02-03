#include <mutex>
#include "../includes/box.h"
#include "../includes/baker.h"
#include "../includes/externs.h"
#include <iostream>
using namespace std;

Baker::Baker(int id) :
		id(id) {
}

Baker::~Baker() {
}

void Baker::bake_and_box(ORDER &anOrder) {
	Box b;
	//unique_lock<mutex> lck(mutex_order_inQ);
	for (int i = 0; i < anOrder.number_donuts; i++) {
		if (b.size() == 12) {
			anOrder.boxes.push_back(b);
			b.clear();
		}
		DONUT donut;
		b.addDonut(donut);
	}
	anOrder.boxes.push_back(b);
	cout << "box with "<<anOrder.number_donuts<<" added to order "<<anOrder.order_number << endl;

}

void Baker::beBaker() {
	ORDER anOrder;
	while (true) {
		unique_lock<mutex> lck(mutex_order_inQ);
		while (order_in_Q.size() != 0 && !b_WaiterIsFinished)
			cv_order_inQ.wait(lck);


		if (order_in_Q.size() > 0) {
			anOrder = order_in_Q.front();
			bake_and_box(anOrder);
			order_out_Vector.push_back(anOrder);
			order_in_Q.pop();
		}

		if (order_in_Q.size() == 0 && b_WaiterIsFinished) {
			break;
		}

	}
	unique_lock<mutex> lck(mutex_order_inQ);
	cout<<"Consumer exiting"<<endl;
}
