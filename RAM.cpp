#include <Windows.h>
#include <iostream>
#include "RAM.h"

#define DIV 1024;

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

void RAM::debug()
{
	GetPhysicallyInstalledSystemMemory(&_instaledRAM);
	GlobalMemoryStatusEx(&_memInfo);

	float a = static_cast<float>(_memInfo.dwMemoryLoad) * _memInfo.ullTotalVirtual / 100;
	float b = static_cast<float>(_memInfo.dwMemoryLoad) * _instaledRAM / 1000000 / 100;

	std::cout << "###########" << std::endl;
	std::cout << "freeSize: " << b << std::endl;
	std::cout << "test: " << a << std::endl;

	std::cout << "total: " << _instaledRAM / 1000000 << std::endl;
	std::cout << "load: " << _memInfo.dwMemoryLoad << std::endl;
	std::cout << "k: " << _memInfo.ullAvailExtendedVirtual / DIV;
	std::cout << "\n";
	std::cout << "ullAvailPageFile: " << _memInfo.ullAvailPageFile / DIV;
	std::cout << "\n";
	std::cout << "ullAvailPhys: " << _memInfo.ullAvailPhys / DIV;
	std::cout << "\n";
	std::cout << "ullAvailVirtual: " << _memInfo.ullAvailVirtual / DIV;
	std::cout << "\n";
	std::cout << "ullTotalPageFile: " << _memInfo.ullTotalPageFile / DIV;
	std::cout << "\n";
	std::cout << "ullTotalPhys: " << _memInfo.ullTotalPhys / DIV;
	std::cout << "\n";
	std::cout << "ullTotalVirtual: " << _memInfo.ullTotalVirtual / DIV;
	std::cout << "\n";
}
