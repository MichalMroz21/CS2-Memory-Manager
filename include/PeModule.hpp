#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

#include <LIEF/PE.hpp>
#include <LIEF/logging.hpp>

class PeModule {
public:

	PeModule(std::string name, std::vector<uint8_t> data);

	std::string name{};
	std::vector<uint8_t> data{};
	std::unique_ptr<const LIEF::PE::Binary> PE{};
};