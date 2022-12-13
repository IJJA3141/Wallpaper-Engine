#include <WbemIdl.h>
#include <comdef.h>
#include <vector>
#include "WMI.h"
#include "disk.h"
#include "crow/json.h"



DISK::DISK() {};

DISK::~DISK() { delete this; };

std::vector<crow::json::wvalue> DISK::get() {
	std::vector<crow::json::wvalue> diskArray_wvalue;
	std::vector<__int64> Sd;
	std::vector<__int64> Fsd;
	std::vector<std::string> Nd;

	if (q.disk(&Sd, &Fsd, &Nd)) {
		for (int i = 0; i < Sd.size(); i++) {
			diskArray_wvalue.push_back({ {"name", Nd[i]}, {"size", Sd[i]}, {"sizeFree", Fsd[i]} });
		}
	}
	else {
		diskArray_wvalue.push_back({ { "name", "-" }, { "size", "-"}, {"sizeFree", "-"} });
	}

	Nd.clear();
	Sd.clear();
	Fsd.clear();
	
	return diskArray_wvalue;
}