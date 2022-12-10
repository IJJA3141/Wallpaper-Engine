#pragma once
#include "crow/json.h"

class DISK
{
public:
	DISK();
	~DISK();

	std::vector<crow::json::wvalue> get();

private:
	std::vector<__int64> mSd;
	std::vector<__int64> mFsd;
	std::vector<std::string> mNd;
};

extern DISK disk;