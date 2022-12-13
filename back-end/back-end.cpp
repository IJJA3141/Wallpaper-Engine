﻿#include "crow.h"
#include "cpu.h"
#include "disk.h"
#include "ram.h"
#include "fs.h"
#include "WMI.h"

WMIQuery q = WMIQuery();
DISK disk = DISK();
CPU cpu = CPU();
PEN pen = PEN();
RAM ram = RAM();

#define CROW_ENFORCE_WS_SPEC
crow::SimpleApp app;

void serverSetUp() 
{
	CROW_ROUTE(app, "/getConst")([]() {
	crow::json::wvalue crowRes = NULL;

	crowRes["ram"] = crow::json::wvalue::list(ram.getConst());
	crowRes["notes"] = crow::json::wvalue::list(pen.get());
	crowRes["disc"] = crow::json::wvalue::list(disk.get());
	crowRes["cpu"] = cpu.get();
	
	return crowRes;
	});

	CROW_ROUTE(app, "/refresh")([]() {
	crow::json::wvalue crowRes = NULL;
	
	crowRes["cpu"] = cpu.get();
	crowRes["ram"] = crow::json::wvalue::list(ram.get());

	return crowRes;
	});

	CROW_ROUTE(app, "/write").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
	pen.set(req.body.data());
	
	return 200;
	});
}

int main() {
	FreeConsole();
	serverSetUp();
	app.loglevel(crow::LogLevel::Warning);
	app.port(18080).run();
	return 0;
}