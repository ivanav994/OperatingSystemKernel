#include "idlethre.h"


void IdleThread::run() {
	while (1)
		dispatch();
}

