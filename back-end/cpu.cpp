#include <WbemIdl.h>
#include <comdef.h>
#include "WMI.h"
#include "cpu.h"

CPU::CPU()
{
	ml = 0;
}

CPU::~CPU()
{
	delete& ml;
	delete this;
}

bool CPU::calculate_CPU_load(int* ptrO) {
	__int64* l1 = new __int64;
	__int64* l2 = new __int64;
	__int64* t1 = new __int64;
	__int64* t2 = new __int64;

	if (q.cpu(l1, t1))
	{
		Sleep(1000);
		if (q.cpu(l2, t2))
		{
			if (*l2 != *l1 && *t2 != *t1)
			{
				*ptrO = (100 - (100 * *l2 - 100 * *l1) / (*t2 - *t1));
				
				delete l1;
				delete l2;
				delete t1;
				delete t2;

				return true;
			}
		}
	}

	delete l1;
	delete l2;
	delete t1;
	delete t2;

	return false;
}

int CPU::get() {
	int ml = -1;
	if (calculate_CPU_load(&ml)) {
		return ml;
	}
	else
	{
		return -1;
	}
}