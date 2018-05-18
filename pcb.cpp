#include "pcb.h"
#include "schedule.h"
#include "thread.h"
#include <dos.h>
#include "tajmer.h"

PCB *PCB::running;
ID PCB::sledId = 1;
SrtLista *PCB::srtLista;
PCB *PCB::idle;


PCB::~PCB() {
	delete lista;
	delete[] stek;
}

PCB::PCB(StackSize stVel, Time vr, Thread *nit) {
	vreme = vr;
	mojaNit = nit;
	stekVel = stVel;
	stek = 0;
	stanje = NOVA;
	id = sledId;
	sledId++;
	lista = new Lista();
}

PCB::Stanje PCB::dohvatiStanje() {
	return stanje;
}

void PCB::postaviStanje(PCB::Stanje st) {
	stanje = st;
}

ID PCB::dohvatiId() {
	return id;
}

void interrupt PCB::zameniNit() {
	// OVE KOMENTARE OBRISATI
	// interrupt rutina - auto push:
	// psw (flags), cs, ip - hardverski
	// ax, bx, cx, dx, es, ds, si, di, bp - softverski
	
	// running->ss = _SS;
	// running->sp = _SP;
	// running->bp = _BP;
	
	// Scheduler::put(running);
	// running = Scheduler::get();
	
	// _SS = running->ss;
	// _SP = running->sp;
	// _BP = running->bp;
	
	if (zakljucano) {
		zoviDispatch = 1;
		return;
	}
	
	zoviDispatch = 0;
	
	static unsigned int pomss, pomsp, pombp;
	asm {
		mov pomss, ss
		mov pomsp, sp
		mov pombp, bp
	}
	running->ss = pomss;
	running->sp = pomsp;
	running->bp = pombp;
	
	if (running->stanje == SPREMNA && running != idle)
		Scheduler::put(running);
	running = Scheduler::get();
	if (!running)
		running = idle;
	
	pomss = running->ss;
	pomsp = running->sp;
	pombp = running->bp;
	asm {
		mov ss, pomss
		mov sp, pomsp
		mov bp, pombp
	}
	
	Tajmer::brojac = 0;
	
	// interrupt rutina - auto pop:
	// isto, samo obrnutim redom
}

void PCB::wrapper() {
	running->mojaNit->run();
	gasiNit();
}

void PCB::gasiNit() {
	// gasi running nit
	running->postaviStanje(ZAVRSILA);
	while (running->lista->dohvatiVel()) {
		PCB* pcb = running->lista->izbaciPrvi();
		pcb->postaviStanje(SPREMNA);
		Scheduler::put(pcb);
	}
	dispatch();
}

int PCB::mozeStart() {
	return dohvatiStanje() == NOVA;
}

void PCB::start() {
	napraviStek();
	Scheduler::put(this);
	postaviStanje(SPREMNA);
}

void PCB::napraviStek() {
	stek = new unsigned char[stekVel];
	stek[stekVel - 1] = 0x02;
	stek[stekVel - 2] = 0x00;
	stek[stekVel - 3] = FP_SEG(wrapper) >> 8;
	stek[stekVel - 4] = FP_SEG(wrapper);
	stek[stekVel - 5] = FP_OFF(wrapper) >> 8;
	stek[stekVel - 6] = FP_OFF(wrapper);
	for (int i = 7; i <= 24; i++)
		stek[stekVel - i] = 0;
	
	ss = FP_SEG(&stek[stekVel - 24]);
	sp = FP_OFF(&stek[stekVel - 24]);
	bp = 0;
}

int PCB::trebaDaCeka() {
	if (this != idle && stanje != ZAVRSILA && running != this && stanje != NOVA)
		return 1;
	else
		return 0;
}

void PCB::cekajDaZavrsi() {
	running->stanje = BLOKIRANA;
	lista->ubaci(running);
	dispatch();
}

PCB* PCB::dohvatiRunning() {
	return running;
}

int PCB::dohvatiRez() {
	return rez;
}

