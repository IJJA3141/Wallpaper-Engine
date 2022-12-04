#include <fstream>
#include <string>
#include <vector>
#include "crow/json.h"
#include "fs.h"

int write(std::vector<std::string> v) {
	std::ofstream notes;
	notes.open("notes.txt");
	if (notes.is_open()) {
		notes.clear();
		for (int i = 0; i < v.size(); i++) {
			notes << v[i] << "\n";
		}
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