#ifndef _TAJMER_H_
#define _TAJMER_H_

#include "tipovi.h"

class Tajmer {
	friend class PCB;
	static pInterrupt stariTajmer;
	static Time brojac;
public:
	static void ubaci();
	static void izbaci();
	static void interrupt mojTajmer(...);
	static void obidjiUspavane();
	static void resetujVreme();
};

#endif