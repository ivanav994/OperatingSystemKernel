#ifndef _KERNEV_H_
#define _KERNEV_H_

#include "tipovi.h"

class PCB;

class KernelEv {
	PCB* vlasnik;
	int imaBlokirana;
	int bioJeSignal;
	IVTNo ivtNo;
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void cekaj();
	void signal();
};

#endif