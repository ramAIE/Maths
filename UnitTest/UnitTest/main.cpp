#include "unittest.h"
#include <iostream>

int main() {

	if (runUnitTests() == false) {
		std::cout << "Unit test failed!" << std::endl;
		std::cin.get();
		return -1;
	}
	std::cout << "All tests passed successfully." << std::endl;
	std::cin.get();
	return 0;
}