#include "semaphor.h"
#include "tipovi.h"
#include "kernsem.h"
#include "pcb.h"


Semaphore::Semaphore(int init) {
	lock
	myImpl = new KernelSem(init);
	unlock
}

Semaphore::~Semaphore() {
	lock
	delete myImpl;
	unlock
}

int Semaphore::wait(Time maxVreme) {
	lock
	myImpl->cekaj(maxVreme);
	unlock
	PCB* pcb = PCB::dohvatiRunning();
	// return pcb->dohvatiRez();
	return PCB::running->rez;
}

void Semaphore::signal() {
	lock
	myImpl->signal();
	unlock
}

int Semaphore::val() const {
	lock
	int vred = myImpl->dohvatiVred();
	unlock
	return vred;
}

