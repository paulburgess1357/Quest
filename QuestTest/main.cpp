#include "pch.h"
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Running Test from Main" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}