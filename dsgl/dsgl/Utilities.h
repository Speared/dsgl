#pragma once
#include <fstream>
#include <string>
static std::string LoadFile(const char* Filename) {
	std::ifstream infile{ Filename };
	if (!infile) {
		fprintf(stderr, "could not open shader %s\n", Filename);
		return 0;
	}
	std::string fileContents{ std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
	return fileContents;
}
