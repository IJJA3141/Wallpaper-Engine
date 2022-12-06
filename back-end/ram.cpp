#include <Windows.h>
#include "ram.h"

RAM::RAM()
{
	mMs.dwLength = sizeof(MEMORYSTATUSEX);
	mMi = ULONGLONG();
	
	uRp = 0;
	uRGo = 0;
	sRGo = 0;

	GetPhysicallyInstalledSystemMemory(&mMi);
	sRGo = mMi / 1048576;
}

RAM::~RAM()
{
	delete& uRp;
	delete& uRGo;
	delete& sRGo;
	delete& mMi;
	delete& mMs;
	delete this;
}

void RAM::refresh() {
	GlobalMemoryStatusEx(&mMs);
	
	uRp = mMs.dwMemoryLoad;
	uRGo = mMs.dwMemoryLoad * (mMi / 1048576) / 100;
}