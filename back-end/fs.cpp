#include <fstream>
#include <string>
#include <vector>
#include "crow/json.h"
#include "fs.h"

bool PEN::set(std::string s) {
	std::string delimiter = "//n//";
	size_t pos = 0;
	std::string token;
	std::ofstream notes;
	notes.open("notes.txt");
	s.erase(0, 1);
	s.erase(s.length() - 1, s.length() - 1);
	if (notes.is_open()) {
		notes.clear();
		while ((pos = s.find(delimiter)) != std::string::npos) {
			std::cout << "toke:" << token << std::endl;
			token = s.substr(0, pos);
			notes << token << "\n";
			s.erase(0, pos + delimiter.length());
		};
		notes.close();
		return true;
	}
	return false;
}

void PEN::read(std::vector<std::string>* v) {
	v->clear();
	std::string currentL;
	std::ifstream notes;
	notes.open("notes.txt");
	if (notes.is_open()) {
		while (getline(notes, currentL))
		{
			v->push_back(currentL);
		}
		notes.close();
	}
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