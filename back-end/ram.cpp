#include <Windows.h>
#include <vector>
#include "crow/json.h"
#include "ram.h"

RAM::RAM()
{
	mMi = ULONGLONG();
	GetPhysicallyInstalledSystemMemory(&mMi);
}

RAM::~RAM()
{
	delete& mMi;
	delete this;
}

std::vector<crow::json::wvalue> RAM::getConst()
{
	MEMORYSTATUSEX memeSize = MEMORYSTATUSEX();
	memeSize.dwLength = sizeof(MEMORYSTATUSEX);
	std::vector < crow::json::wvalue> res;

	GlobalMemoryStatusEx(&memeSize);
	res.push_back({ {"Size", mMi / 1048576}, {"Used", memeSize.dwMemoryLoad * (mMi / 1048576) / 100}, {"Percentage", int(memeSize.dwMemoryLoad)} });
	
	return res;
}

std::vector<crow::json::wvalue> RAM::get()
{
	MEMORYSTATUSEX memeSize = MEMORYSTATUSEX();
	memeSize.dwLength = sizeof(MEMORYSTATUSEX);
	std::vector < crow::json::wvalue> res;
	
	GlobalMemoryStatusEx(&memeSize);
	res.push_back({ {"Used", memeSize.dwMemoryLoad * (mMi / 1048576) / 100}, {"Percentage", int(memeSize.dwMemoryLoad)} });
	
	return res;
}