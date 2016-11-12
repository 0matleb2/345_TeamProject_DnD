#pragma once
#include <iostream>
#include <string>

void fatalError(std::string errorString) {

	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit: ";

	getchar();

	exit(1);
}