#include <iostream>
#include "crow.h"
#include "WMI.h"
#include "cpu.h"

crow::SimpleApp app;
crow::json::wvalue ConstRES = NULL;
crow::json::wvalue refreshRES = NULL;

void serverSetUp() {
	CROW_ROUTE(app, "/getConst")([]() {
		return "not implemented yet !";
	});

	CROW_ROUTE(app, "/refresh")([]() {
		refreshRES["cpu"] = cpu.int_getCPUload();
		return refreshRES;
	});
}

int main() {	
	serverSetUp();
	app.port(18080).run();

	return 0;
}