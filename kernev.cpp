#include "kernev.h"
#include "pcb.h"
#include "ivtentry.h"
#include "thread.h"
#include "schedule.h"

#include <iostream.h>


KernelEv::KernelEv(IVTNo ivtNo) {
	imaBlokirana = 0;
	bioJeSignal = 0;
	vlasnik = PCB::running;
	this->ivtNo = ivtNo;
	
	IVTEntry* ulaz = IVTEntry::dohvati(this->ivtNo);
	if (ulaz == 0) {
		return;
	}
	if (ulaz->dog == 0) {
		ulaz->dog = this;
	}
}

KernelEv::~KernelEv() {
	signal();
	
	IVTEntry* ulaz = IVTEntry::dohvati(this->ivtNo);
	if (ulaz == 0) {
		return;
	}
	if (ulaz->dog == this) {
		ulaz->dog = 0;
	}
}

void KernelEv::cekaj() {
	if (vlasnik != PCB::running) {
		return;
	}
	else if (bioJeSignal) {
		bioJeSignal = 0;
	}
	else if (imaBlokirana == 0) {
		imaBlokirana = 1;
		PCB::running->stanje = PCB::BLOKIRANA;
		dispatch();
	}
}

void KernelEv::signal() {
	if (imaBlokirana) {
		imaBlokirana = 0;
		vlasnik->stanje = PCB::SPREMNA;
		Scheduler::put(vlasnik);
	}
	else if (bioJeSignal == 0) {
		bioJeSignal = 1;
	}
}

