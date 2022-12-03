#include <Windows.h>
#include "ram.h"
#include <iostream>

RAM::RAM()
{
	_memSTAT.dwLength = sizeof(MEMORYSTATUSEX);
	_memINSTALED = ULONGLONG();
	
	usedP = 0;
	usedGo = 0;
	sizeGo = 0;
}

RAM::~RAM()
{
	delete this;
}

void RAM::get() {
	GetPhysicallyInstalledSystemMemory(&_memINSTALED);
	sizeGo = _memINSTALED / 1048576;
	refresh();
}

void RAM::refresh() {
	GlobalMemoryStatusEx(&_memSTAT);
	
	usedP = _memSTAT.dwMemoryLoad;
	usedGo = _memSTAT.dwMemoryLoad * (_memINSTALED / 1048576) / 100;
}

RAM ram = RAM();