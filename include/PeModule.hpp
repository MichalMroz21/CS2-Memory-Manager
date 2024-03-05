#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <PeLib.h>

class PeModule {
public:

	PeModule(std::string name, std::vector<uint8_t> data) {
		this->name = name;
		this->data = data;

		convertBytesToPE();

		PE = PeLib::openPeFile("temp_pe.exe");
	}

	void convertBytesToPE() {
		std::ofstream outFile("temp_pe.exe", std::ios::binary | std::ios::trunc);

		if (outFile.is_open()) {
			outFile.write(reinterpret_cast<char*>(this->data.data()), this->data.size());
			outFile.close();

			std::cout << "PE file saved to temp_pe.exe" << std::endl;
		}
		else {
			std::cerr << "Error: Unable to open temp_pe.exe for writing" << std::endl;
			return;
		}
	}

	std::string name{};
	std::vector<uint8_t> data{};
	PeLib::PeFile* PE;
};