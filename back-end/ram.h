#pragma once
class RAM
{
public:
	RAM();
	~RAM();

	int usedP;
	int usedGo;
	int sizeGo;

	void get();
	void refresh();

private:
	MEMORYSTATUSEX _memSTAT;
	ULONGLONG _memINSTALED;
};

extern RAM ram;