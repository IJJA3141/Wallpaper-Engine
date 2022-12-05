#pragma once
class RAM
{
public:
	RAM();
	~RAM();

	int uRp;
	int uRGo;
	int sRGo;

	void refresh();

private:
	MEMORYSTATUSEX mMs;
	ULONGLONG mMi;
};

extern RAM ram;