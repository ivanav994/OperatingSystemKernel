#ifndef _TIPOVI_H_
#define _TIPOVI_H_

typedef unsigned long StackSize;
typedef unsigned int Time;
typedef int ID;
typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

#define lock asm pushf; asm cli;
#define unlock asm popf;

extern int zakljucano;
extern int zoviDispatch;

void zakljucaj();
void otkljucaj();

#define PREPAREENTRY(ivtNo,zvatiStaru)\
void interrupt rutina##ivtNo(...);\
IVTEntry ivtUlaz##ivtNo(ivtNo,&rutina##ivtNo);\
void interrupt rutina##ivtNo(...) {\
	ivtUlaz##ivtNo.zoviPrekid(zvatiStaru);\
}

#endif