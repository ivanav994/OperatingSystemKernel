#include "tajmer.h"
#include <dos.h>
#include "pcb.h"
#include "thread.h"
#include "schedule.h"
#include "lista.h"
#include "kernsem.h"

void tick();

pInterrupt Tajmer::stariTajmer;
Time Tajmer::brojac;

void Tajmer::ubaci() {
	stariTajmer = getvect(8);
	setvect(8, mojTajmer);
}

void Tajmer::izbaci() {
	setvect(8, stariTajmer);
}

void interrupt Tajmer::mojTajmer(...) {
	stariTajmer();
	obidjiUspavane();
	tick();
	if (PCB::running == PCB::idle) {
		dispatch();
	}
	else if (PCB::running->vreme > 0) {
		if (++brojac >= PCB::running->vreme) {
			dispatch();
		}
	}
}

void Tajmer::obidjiUspavane() {
	PCB::srtLista->osvezi();
	while (1) {
		PCB* pcb = PCB::srtLista->izbaciPrvi();
		if (!pcb)
			break;
		Scheduler::put(pcb);
		pcb->stanje = PCB::SPREMNA;
		pcb->sem->izbaci(pcb);
		pcb->sem = 0;
		pcb->rez = 0;
	}
}

void Tajmer::resetujVreme() {
	brojac = 0;
}

