#ifndef _IDLETHRE_H_
#define _IDLETHRE_H_

#include "thread.h"

class IdleThread : public Thread {
public:
	void run();
};

#endif