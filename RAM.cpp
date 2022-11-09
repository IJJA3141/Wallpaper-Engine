#include <Windows.h>
#include "RAM.h"

RAM::RAM()
{
	_memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	_instaledRAM = ULONGLONG();
}

RAM::~RAM()
{
}

DWORD RAM::getLoad()
{
	GlobalMemoryStatusEx(&_memInfo);
	return _memInfo.dwMemoryLoad;
}

ULONGLONG RAM::getSize()
{
	GetPhysicallyInstalledSystemMemory(&_instaledRAM);
	return _instaledRAM / 1000000;
}

DWORD RAM::load() {
	_load = getLoad();
	return _load;
}

DWORD RAM::size() {
	_size = getSize();
	return _size;
}

float RAM::freeSize() {
	_freeSize = static_cast<float>(_load) * _size / 100;
	return _freeSize;
}