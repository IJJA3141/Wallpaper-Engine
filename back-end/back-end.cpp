﻿#include "crow.h"
#include "cpu.h"
#include "disk.h"
#include "ram.h"
#include "fs.h"

crow::SimpleApp app;
crow::json::wvalue constRES = NULL;
crow::json::wvalue refreshRES = NULL;
crow::json::wvalue::list res;

void serverSetUp() {
	CROW_ROUTE(app, "/getConst")([]() {
	ram.get();
	disk.generateCROWres();
	fsCROWres(&res);

	constRES["notes"] = crow::json::wvalue::list(res);
	constRES["disc"] = crow::json::wvalue::list(disk.diskARRAY);
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

	CROW_ROUTE(app, "/write").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
	write(req.body.data());
	return 200;
	});
}

int main() {
	serverSetUp();
	app.port(18080).run();
	return 0;
}