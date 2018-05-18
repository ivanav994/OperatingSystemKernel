#include "pcb.h"
#include "thread.h"
#include "tajmer.h"
#include "idlethre.h"
#include "schedule.h"


int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	int rez = 0;
	
	PCB::srtLista = new SrtLista();
	
	Tajmer::ubaci();
	PCB::running = new PCB(0, defaultTimeSlice, 0);
	
	IdleThread *idleThread = new IdleThread();
	idleThread->start();
	PCB::idle = Scheduler::get();
	
	rez = userMain(argc, argv);
	
	delete idleThread;
	
	delete PCB::running;
	Tajmer::izbaci();
	
	delete PCB::srtLista;
	
	return rez;
}

