#include "../includes_usr/constants.h"
#include "../includes_usr/dispatcher.h"
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"
#include "../includes_usr/logger_single_thread.h"
#include <queue>

using namespace std;
PCB runningPCB;
std::queue<PCB> ready_Q;
queue<PCB> blocked_Q;

void dispatcher::init() {
	runningPCB.cpu_time = UNINITIALIZED;
	runningPCB.start_time = UNINITIALIZED;
	runningPCB.io_time = UNINITIALIZED;
	runningPCB.process_number = UNINITIALIZED;
	queue<PCB> empty;
	swap(ready_Q, empty);
	swap(blocked_Q, empty);
}

PCB dispatcher::getCurrentJob() {
	return runningPCB;
}

void dispatcher::addJob(PCB &myPCB) {
	ready_Q.push(myPCB);
}

int dispatcher::processInterrupt(int interrupt) {
	if (interrupt == SWITCH_PROCESS) {
		if (ready_Q.size() != 0) {
			PCB temp = ready_Q.front(); //tempPCB
			if (runningPCB.cpu_time != UNINITIALIZED
					&& runningPCB.start_time != UNINITIALIZED
					&& runningPCB.io_time != UNINITIALIZED
					&& runningPCB.process_number != UNINITIALIZED) {
				ready_Q.push(runningPCB);
			}
			runningPCB.cpu_time = temp.cpu_time;
			runningPCB.start_time = temp.start_time;
			runningPCB.io_time = temp.io_time;
			runningPCB.process_number = temp.process_number;
			ready_Q.pop();

			return PCB_SWITCHED_PROCESSES;

		} else {
			if (blocked_Q.size() != 0) {
				return BLOCKED_JOBS;
			} else {
				return NO_JOBS;
			}
		}
	} else if (interrupt == IO_COMPLETE) {
		if (blocked_Q.empty()) {
			return PCB_BLOCKED_QUEUE_EMPTY;
		}
		while (!blocked_Q.empty()) {
			ready_Q.push(blocked_Q.front());
			blocked_Q.pop();
		}
		return PCB_MOVED_FROM_BLOCKED_TO_READY;
	}
	return PCB_UNIMPLEMENTED;
}

int dispatcher::doTick() {
	int returnval = 0;
	if (runningPCB.cpu_time == UNINITIALIZED
			&& runningPCB.start_time == UNINITIALIZED
			&& runningPCB.io_time == UNINITIALIZED
			&& runningPCB.process_number == UNINITIALIZED) {
		if (ready_Q.empty()) {
			if (blocked_Q.empty()) {
				return NO_JOBS;
			}
			return BLOCKED_JOBS;
		} else {
			runningPCB = ready_Q.front();
			ready_Q.pop();
			return PCB_MOVED_FROM_READY_TO_RUNNING;
		}
	} else {
		if (runningPCB.cpu_time > 0) {
			runningPCB.cpu_time--;
		}
		if (runningPCB.cpu_time == 0) {
			if (runningPCB.io_time > 0) {
				runningPCB.io_time = 0;
				blocked_Q.push(runningPCB);
				returnval = PCB_ADDED_TO_BLOCKED_QUEUE;
				runningPCB.cpu_time = UNINITIALIZED; // unsure if this is marking as invalid
				runningPCB.start_time = UNINITIALIZED; // unsure if this is marking as invalid
				runningPCB.io_time = UNINITIALIZED; // unsure if this is marking as invalid
				runningPCB.process_number = UNINITIALIZED; // unsure if this is marking as invalid
				return returnval;
			} else {
				returnval = PCB_FINISHED;
				runningPCB.cpu_time = UNINITIALIZED; // unsure if this is marking as invalid
				runningPCB.start_time = UNINITIALIZED; // unsure if this is marking as invalid
				runningPCB.io_time = UNINITIALIZED; // unsure if this is marking as invalid
				runningPCB.process_number = UNINITIALIZED; // unsure if this is marking as invalid
				return returnval;
			}
		} else {
			return PCB_CPUTIME_DECREMENTED;
		}
	}
	return NO_JOBS;
}
