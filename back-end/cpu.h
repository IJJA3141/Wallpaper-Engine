#pragma once
class CPU
{
public:
	CPU();
	~CPU();

	int get();

private:
	int ml;
	bool calculate_CPU_load(int* ptrO);
	bool fetch_CPU_data(long long* ptrL, long long* ptrT);
};

extern CPU cpu;