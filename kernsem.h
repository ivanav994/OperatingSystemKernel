#ifndef _KERNSEM_H_
#define _KERNSEM_H_

#include "lista.h"

class KernelSem {
	int vred;
	Lista* lista;
public:
	KernelSem(int init = 1);
	~KernelSem();
	void cekaj(Time maxVreme);
	void signal(int destruktor = 0);
	int dohvatiVred() const;
	void izbaci(PCB* pcb);
};

#endif