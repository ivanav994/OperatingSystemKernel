#ifndef _LISTA_H_
#define _LISTA_H_

#include "tipovi.h"
class PCB;

class SrtLista {
	struct Elem {
		Elem(PCB* p, Time t) {
			pcb = p;
			vreme = t;
			sled = 0;
		}
		PCB* pcb;
		Time vreme;
		Elem* sled;
	};
	Elem* prvi;
	int vel;
public:
	SrtLista();
	~SrtLista();
	void ubaci(PCB* pcb, Time vreme);
	PCB* izbaci(PCB* pcb);
	PCB* izbaciPrvi();	// izbacuje prvi ako ga ima i ako mu je vreme 0
	void osvezi();
	int dohvatiVel();
};

class Lista {
	struct Elem {
		Elem(PCB* p) {
			pcb = p;
			sled = 0;
		}
		PCB* pcb;
		Elem* sled;
	};
	Elem* prvi;
	Elem* posl;
	int vel;
public:
	Lista();
	~Lista();
	void ubaci(PCB* pcb);
	PCB* izbaci(PCB* pcb);
	void ubaciPoslednji(PCB* pcb);
	PCB* izbaciPrvi();
	PCB* nadji(ID id);
	int dohvatiVel();
};

#endif