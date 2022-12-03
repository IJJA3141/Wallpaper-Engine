#include <iostream>
#include "crow.h"
#include "WMI.h"
#include "cpu.h"
#include "ram.h"
#include "disc.h"

crow::SimpleApp app;
crow::json::wvalue constRES = NULL;
crow::json::wvalue refreshRES = NULL;

std::vector<int> diskSIZE;
std::vector<int> diskFREEsize;
std::vector<std::string> diskNAME;
std::vector<crow::json::wvalue> tempCROWarray;

void serverSetUp() {
	CROW_ROUTE(app, "/getConst")([]() {
		ram.get();
		test(&diskSIZE, &diskFREEsize, &diskNAME);
		for (int i = 0; i < diskSIZE.size(); i++) {
			crow::json::wvalue diskRES = { {"name", diskNAME[i]}, {"size", diskSIZE[i]}, {"sizeFree", diskFREEsize[i]} };
			tempCROWarray.push_back(diskRES);
		}
		constRES["disc"] = crow::json::wvalue::list(tempCROWarray);
		constRES["ram"] = { {"size", ram.sizeGo}, {"used%", ram.usedP}, {"usedGo", ram.usedGo} };
		constRES["cpu"] = cpu.int_getCPUload();
		return constRES;
	});

	CROW_ROUTE(app, "/refresh")([]() {
		ram.refresh();
		refreshRES["ram"] = { {"used%", ram.usedP}, {"usedGo", ram.usedGo} };
		refreshRES["cpu"] = cpu.int_getCPUload();
		return refreshRES;
	});
}

int main() {
	serverSetUp();
	app.port(18080).run();

	return 0;
}