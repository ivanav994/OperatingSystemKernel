#include "kernsem.h"
#include "pcb.h"
#include "thread.h"
#include "schedule.h"


KernelSem::KernelSem(int init) {
	vred = init;
	lista = new Lista();
}

KernelSem::~KernelSem() {
	while (dohvatiVred() < 0) {
		signal(1);
	}
	delete lista;
}

void KernelSem::cekaj(Time maxVreme) {
	if (--vred < 0) {
		PCB::running->stanje = PCB::BLOKIRANA;
		lista->ubaci(PCB::running);
		if (maxVreme > 0)
			PCB::srtLista->ubaci(PCB::running, maxVreme);
		PCB::running->sem = this;
		dispatch();
	}
	else {
		PCB::running->rez = 1;
	}
}

void KernelSem::signal(int destruktor) {
	if (vred++ < 0) {
		PCB* pcb = lista->izbaciPrvi();
		pcb->rez = destruktor != 1;
		PCB::srtLista->izbaci(pcb);
		pcb->stanje = PCB::SPREMNA;
		Scheduler::put(pcb);
		
		pcb->sem = 0;
	}
}

int KernelSem::dohvatiVred() const {
	return vred;
}

void KernelSem::izbaci(PCB* pcb) {
	// if (lista->izbaci(pcb)) {
		// pcb->sem = 0;
		// vred++;
	// }
	
	lista->izbaci(pcb);
	vred++;
}

