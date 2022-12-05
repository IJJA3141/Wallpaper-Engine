#include <fstream>
#include <string>
#include <vector>
#include "crow/json.h"
#include "fs.h"

int write(std::string s) {
	std::string delimiter = "//n//";
	size_t pos = 0;
	std::string token;
	std::ofstream notes;
	notes.open("notes.txt");
	s.erase(0, 0);
	s.erase(s.length() - 1, s.length() - 1);
	if (notes.is_open()) {
		notes.clear();
		while ((pos = s.find(delimiter)) != std::string::npos) {
			std::cout << "toke:" << token << std::endl;
			token = s.substr(0, pos);
			notes << token;
			s.erase(0, pos + delimiter.length());
		};
		notes.close();
		return 0;
	}
	return 1;
}

int read(std::vector<std::string>* v) {
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
		return 0;
	}
	return 1;
}

int fsCROWres(crow::json::wvalue::list* res) {
	res->clear();
	std::cout << "mais" << std::endl;
	std::vector<std::string> readS;
	read(&readS);
	for (int i = 0; i < readS.size(); i++) {
		res->push_back(readS[i]);
	}
	return 0;
}