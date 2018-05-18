#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include "tipovi.h"

class IVTEntry {
	friend class KernelEv;
	
	IVTNo ivtNo;
	pInterrupt novaRutina;
	pInterrupt staraRutina;
	KernelEv* dog;
	static IVTEntry* ulazi[];
public:
	IVTEntry(IVTNo ivtNo, pInterrupt novaRutina);
	~IVTEntry();
	static IVTEntry* dohvati(IVTNo ivtNo);
	KernelEv* dohvatiDog();
	void postaviDog(KernelEv* dog);
	void zoviPrekid(int stara);
};

#endif