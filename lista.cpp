#include "lista.h"
#include "pcb.h"

#include <iostream.h>


SrtLista::SrtLista() {
	vel = 0;
	prvi = 0;
}

SrtLista::~SrtLista() {
	while (prvi) {
		izbaciPrvi();
	}
}

void SrtLista::ubaci(PCB* pcb, Time vreme) {
	Elem* novi = new Elem(pcb, vreme);
	
	Elem* pret = 0;
	Elem* tek = prvi;
	
	while (tek && tek->vreme < novi->vreme) {
		novi->vreme -= tek->vreme;
		pret = tek;
		tek = tek->sled;
	}
	
	if (pret)
		pret->sled = novi;
	else
		prvi = novi;
	
	novi->sled = tek;
	
	if (tek)
		tek->vreme -= novi->vreme;
	
	vel++;
}

PCB* SrtLista::izbaci(PCB* pcb) {
	if (prvi == 0)
		return 0;
	
	Elem* pret = 0;
	Elem* tek = prvi;
	
	while (tek && tek->pcb != pcb) {
		pret = tek;
		tek = tek->sled;
	}
	
	if (tek) {
		if (pret)
			pret->sled = tek->sled;
		else
			prvi = tek->sled;
		
		if (tek->sled)
			tek->sled->vreme += tek->vreme;
		
		delete tek;
		vel--;
		return pcb;
	}
	
	return 0;
}

PCB* SrtLista::izbaciPrvi() {
	if (prvi == 0 || prvi->vreme)
		return 0;
	
	Elem* stari = prvi;
	prvi = prvi->sled;
	if (prvi)
		prvi->vreme += stari->vreme;
	PCB* pcb = stari->pcb;
	delete stari;
	vel--;
	return pcb;
}

void SrtLista::osvezi() {
	if (prvi && prvi->vreme)
		prvi->vreme--;
}

int SrtLista::dohvatiVel() {
	return vel;
}


// SrtLista::SrtLista() {
	// vel = 0;
	// prvi = 0;
// }

// SrtLista::~SrtLista() {
	// while (dohvatiVel() > 0) {
		// prvi->vreme = 0;
		// izbaci(prvi->pcb);
	// }
// }

// void SrtLista::ubaci(PCB* pcb, Time vreme) {
	// Elem* novi = new Elem(pcb, vreme);
	// Elem* tek = prvi;
	// Elem* pret = 0;
	// while (tek) {
		// if (novi->vreme <= tek->vreme) {
			// novi->sled = tek;
			// if (pret)
				// pret->sled = novi;
			// else
				// prvi = novi;
			// tek->vreme -= novi->vreme;
			// vel++;
			// return;
		// }
		// else {
			// novi->vreme -= tek->vreme;
			// pret = tek;
			// tek = tek->sled;
		// }
	// }
	
	// novi->sled = 0;
	// if (pret)
		// pret->sled = novi;
	// else
		// prvi = novi;
	// vel++;
// }

// PCB* SrtLista::izbaci(PCB* pcb) {
	// Elem* tek = prvi;
	// Elem* pret = 0;
	// while (tek) {
		// if (tek->pcb == pcb) {
			// Elem* stari = tek;
			// tek = tek->sled;
			// if (pret) {
				// pret->sled = tek;
			// }
			// else {
				// prvi = tek;
			// }
			// if (tek)
				// tek->vreme += stari->vreme;
			// delete stari;
			// vel--;
			// return pcb;
		// }
		// else {
			// pret = tek;
			// tek = tek->sled;
		// }
	// }
	
	// return 0;
// }

// PCB* SrtLista::izbaciPrvi() {
	// if (!vel || prvi->vreme)
		// return 0;
	// else {
		// return izbaci(prvi->pcb);
	// }
// }

// void SrtLista::osvezi() {
	// if (vel && prvi->vreme > 0) {
		// prvi->vreme--;
	// }
// }

// int SrtLista::dohvatiVel() {
	// return vel;
// }


Lista::Lista() {
	vel = 0;
	prvi = 0;
	posl = 0;
}

Lista::~Lista() {
	while (izbaciPrvi() != 0) {
		// nista
	}
}

void Lista::ubaci(PCB* pcb) {
	ubaciPoslednji(pcb);
}

PCB* Lista::izbaci(PCB* pcb) {
	if (prvi == 0) {
		return 0;
	}
	
	Elem* pret = 0;
	Elem* tek = prvi;
	
	while (tek) {
		if (tek->pcb == pcb) {
			if (!pret)
				prvi = tek->sled;
			else
				pret->sled = tek->sled;
			PCB* p = tek->pcb;
			if (posl == tek)
				posl = pret;
			delete tek;
			vel--;
			return p;
		}
		
		pret = tek;
		tek = tek->sled;
	}
	
	return 0;
}

void Lista::ubaciPoslednji(PCB* pcb) {
	if (prvi) {
		posl = posl->sled = new Elem(pcb);
	}
	else {
		prvi = posl = new Elem(pcb);
	}
	vel++;
}

PCB* Lista::izbaciPrvi() {
	if (!prvi)
		return 0;
	
	PCB* pcb = izbaci(prvi->pcb);
	return pcb;
}

PCB* Lista::nadji(ID id) {
	Elem* tek = prvi;
	while (tek) {
		if (tek->pcb->dohvatiId() == id) {
			return tek->pcb;
		}
		else {
			tek = tek->sled;
		}
	}
	
	return 0;
}

int Lista::dohvatiVel() {
	return vel;
}

