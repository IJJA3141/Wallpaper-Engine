#include <Windows.h>
#include <iostream>
#include "RAM.h"

int main()
{
	RAM ram = RAM();

	for (int x = 0; x < 20; x++) {
		std::cout << "####################################################" << std::endl;
		std::cout << "\n";
		std::cout << "Load: " << ram.load() << "% || Size: " << ram.size() << "Kb || used memory: " << ram.freeSize() << "Kb" << std::endl;
		std::cout << "\n";
		Sleep(2000);
	}
	ram.~RAM();
}