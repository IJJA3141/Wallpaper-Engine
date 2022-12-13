#pragma once
class CPU
{
public:
	CPU();
	~CPU();

	int get();

private:
	bool calculate_CPU_load(int* ptrO);
};

extern CPU cpu;