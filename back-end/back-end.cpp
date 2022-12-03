#include <iostream>
#include "crow.h"
#include "WMI.h"
#include "cpu.h"
#include "ram.h"

crow::SimpleApp app;
crow::json::wvalue constRES = NULL;
crow::json::wvalue refreshRES = NULL;

void serverSetUp() {
	CROW_ROUTE(app, "/getConst")([]() {
		ram.get();
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