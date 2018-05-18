#include "thread.h"
#include "pcb.h"
#include "tipovi.h"


void dispatch() {
	lock
	PCB::zameniNit();
	unlock
}

Thread::~Thread() {
	waitToComplete();
	// lock
	zakljucaj();
	delete myPCB;
	otkljucaj();
	// unlock
}

Thread::Thread(StackSize stekVel, Time vreme) {
	// lock
	zakljucaj();
	myPCB = new PCB(stekVel, vreme, this);
	otkljucaj();
	// unlock
}

void Thread::start() {
	// lock
	zakljucaj();
	if (myPCB->mozeStart()) {
		myPCB->start();
	}
	otkljucaj();
	// unlock
}

void Thread::waitToComplete() {
	// lock
	zakljucaj();
	if (myPCB->trebaDaCeka()) {
		myPCB->cekajDaZavrsi();
	}
	otkljucaj();
	// unlock
}

