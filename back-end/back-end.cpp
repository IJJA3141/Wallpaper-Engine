#include "crow.h"
#include "cpu.h"
#include "disk.h"
#include "ram.h"
#include "fs.h"

crow::SimpleApp app;

void serverSetUp() {
	CROW_ROUTE(app, "/getConst")([]() {
	crow::json::wvalue crowRes = NULL;

	crowRes.clear();

	ram.refresh();

	crowRes["notes"] = crow::json::wvalue::list(pen.get());
	crowRes["disc"] = crow::json::wvalue::list(disk.get());
	crowRes["ram"] = { {"size", ram.sRGo}, {"used%", ram.uRp}, {"usedGo", ram.uRGo} };
	crowRes["cpu"] = cpu.get();

	return crowRes;
	});

	CROW_ROUTE(app, "/refresh")([]() {
	crow::json::wvalue crowRes = NULL;
	crowRes.clear();
	ram.refresh();
	
	crowRes["ram"] = { {"used%", ram.uRp}, {"usedGo", ram.uRGo} };
	crowRes["cpu"] = cpu.get();

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