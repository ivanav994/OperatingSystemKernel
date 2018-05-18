#ifndef _PCB_H_
#define _PCB_H_

#include "tipovi.h"
#include "lista.h"

class Thread;
class KernelSem;

class PCB {
public:
	enum Stanje { BLOKIRANA, ZAVRSILA, SPREMNA, NOVA };
private:
	friend int main(int argc, char* argv[]);
	friend class Tajmer;
	friend class SrtLista;
	friend class KernelEv;
	friend class KernelSem;
	friend class Semaphore;
	
	Time vreme;
	StackSize stekVel;
	static PCB *running;
	unsigned int ss, sp, bp;
	Thread *mojaNit;
	unsigned char *stek;
	Stanje stanje;
	ID id;
	static ID sledId;
	Lista *lista;
	static SrtLista *srtLista;
	int rez;
	KernelSem *sem;
	static PCB* idle;
public:
	Stanje dohvatiStanje();
	void postaviStanje(Stanje stanje);
	ID dohvatiId();
	static void interrupt zameniNit();
	~PCB();
	PCB(StackSize stekVel, Time vreme, Thread *nit);
	static void wrapper();
	static void gasiNit();
	int mozeStart();
	void start();
	void napraviStek();
	int trebaDaCeka();
	void cekajDaZavrsi();
	static PCB* dohvatiRunning();
	int dohvatiRez();
};

#endif