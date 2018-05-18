#include "tipovi.h"
#include "thread.h"

int zakljucano = 0;
int zoviDispatch = 0;

void zakljucaj() {
	zakljucano = 1;
}

void otkljucaj() {
	zakljucano = 0;
	if (zoviDispatch)
		dispatch();
}

