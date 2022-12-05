#pragma once
#include "crow/json.h"

class DISK
{
public:
	DISK();
	~DISK();

	std::vector<crow::json::wvalue> get();

private:
	bool get_disk_data(std::vector<int>* pSo, std::vector<int>* pFso, std::vector<std::string>* pNo);

	std::vector<int> mSd;
	std::vector<int> mFsd;
	std::vector<std::string> mNd;
};

extern DISK disk;