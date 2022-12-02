#pragma once
class CPU
{
public:
	CPU();
	~CPU();

	int int_getCPUload();

private:
	int cpuLOAD;
	bool getCPUload(int* ptrO);
	bool getCPUdata(int* ptrL, int* ptrT);
};

extern CPU cpu;