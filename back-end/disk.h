#pragma once
#include "crow/json.h"

class DISK
{
public:
	DISK();
	~DISK();

	bool generateCROWres();
	std::vector<crow::json::wvalue> diskARRAY;

private:
	bool getDISKdata(std::vector<int>* size, std::vector<int>* sizeFREE, std::vector<std::string>* name);

	std::vector<int> _diskSIZE;
	std::vector<int> _diskFREEsize;
	std::vector<std::string> _diskNAME;
};

extern DISK disk;