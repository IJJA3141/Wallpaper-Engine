#pragma once

class RAM
{
public:
	RAM();
	~RAM();
	DWORD load();
	DWORD size();
	float freeSize();
	void debug();
private:
	DWORD getLoad();
	ULONGLONG getSize();
	ULONGLONG _instaledRAM;
	MEMORYSTATUSEX _memInfo;
	DWORD _load;
	DWORD _size;
	float _freeSize;
};