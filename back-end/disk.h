#pragma once
#include "crow/json.h"

class DISK
{
public:
	DISK();
	~DISK();

	std::vector<crow::json::wvalue> get();
};

extern DISK disk;