#include <WbemIdl.h>
#include <comdef.h>
#include "WMI.h"
#include "cpu.h"

CPU::CPU() {};

CPU::~CPU() { delete this; };

bool CPU::calculate_CPU_load(int* ptrO) {
	__int64 l1 = 0;
	__int64 l2 = 0;
	__int64 t1 = 0;
	__int64 t2 = 0;

	if (q.cpu(&l1, &t1))
	{
		Sleep(1000);
		if (q.cpu(&l2, &t2))
		{
			if (l2 != l1 && t2 != t1)
			{
				*ptrO = (100 - (100 * l2 - 100 * l1) / (t2 - t1));

				return true;
			}
		}
	}

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