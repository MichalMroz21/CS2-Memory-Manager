#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <LIEF/LIEF.hpp>

class PeModule {
public:

	PeModule(std::string name, std::vector<uint8_t> data);

	void convertBytesToPE();

	std::string name{};
	std::vector<uint8_t> data{};
};