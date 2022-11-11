#include <Windows.h>
#include <iostream>
#include "RAM.h"
#include <filesystem>

int main()
{
	/*
	std::filesystem::path;
	int i = 0;
	for (const auto& part : pathToShow)
		std::cout << "path: " << i++ << " = " << part;
	*/




	RAM ram = RAM();

	for (int x = 0; x < 20; x++) {
		ram.debug();
		/*
		std::cout << "####################################################" << std::endl;
		std::cout << "\n";
		std::cout << "Load: " << ram.load() << "% || Size: " << ram.size() << "Kb || used memory: " << ram.freeSize() << "Kb" << std::endl;
		std::cout << "\n";
		*/
		Sleep(2000);
	}
	ram.~RAM();
}