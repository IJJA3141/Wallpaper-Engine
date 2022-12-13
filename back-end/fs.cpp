#include <fstream>
#include <string>
#include <vector>
#include "crow/json.h"
#include "fs.h"

bool PEN::set(std::string s) {
	std::ofstream notes;

	notes.open("notes.txt");

	if (notes.is_open()) {
		notes.clear();

		notes << s;

		notes.close();
		return true;
	}
	return false;
}

void PEN::read(std::vector<std::string>* v) {
	std::string currentL;
	std::ifstream notes;

	notes.open("notes.txt");

	if (notes.is_open()) {
		while (getline(notes, currentL))
		{
			v->push_back(currentL);
		}

		notes.close();
		return;
	}
	return;
}

crow::json::wvalue::list PEN::get() {
	crow::json::wvalue::list res;
	std::vector<std::string> req;

	read(&req);

	for (int i = 0; i < req.size(); i++) {
		res.push_back(req[i]);
	}

	return res;
}