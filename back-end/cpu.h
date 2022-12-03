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
	bool getCPUdata(long long* ptrL, long long* ptrT);
};

extern CPU cpu;