#include "ivtentry.h"
#include <dos.h>
#include "kernev.h"
#include "thread.h"

IVTEntry* IVTEntry::ulazi[256] = {0};


IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt novaRutina) {
	this->novaRutina = novaRutina;
	staraRutina = 0;
	this->ivtNo = ivtNo;
	dog = 0;
	
	lock
	if (ulazi[this->ivtNo] == 0) {
		ulazi[this->ivtNo] = this;
		this->staraRutina = getvect(this->ivtNo);
		setvect(this->ivtNo, this->novaRutina);
	}
	unlock
}

IVTEntry::~IVTEntry() {
	lock
	if (ulazi[this->ivtNo] == this) {
		ulazi[this->ivtNo] = 0;
		setvect(this->ivtNo, this->staraRutina);
		(*this->staraRutina)();
	}
	unlock
}

IVTEntry* IVTEntry::dohvati(IVTNo ivtNo) {
	return ulazi[ivtNo];
}

KernelEv* IVTEntry::dohvatiDog() {
	return dog;
}

void IVTEntry::postaviDog(KernelEv* dog) {
	this->dog = dog;
}

void IVTEntry::zoviPrekid(int stara) {
	if (stara) {
		if (staraRutina != 0) {
			(*staraRutina)();
		}
	}
	if (dohvatiDog()) {
		dohvatiDog()->signal();
	}
	dispatch();
}

