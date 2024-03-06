#include "PeModule.hpp"

PeModule::PeModule(std::string name, std::vector<uint8_t> data) {
	this->name = name;
	this->data = data;

	LIEF::PE::ParserConfig parserConfig = LIEF::PE::ParserConfig();

	parserConfig.parse_signature = false;
	parserConfig.parse_exports = true;
	parserConfig.parse_imports = true;
	parserConfig.parse_reloc = true;
	parserConfig.parse_rsrc = true;

	this->PE = LIEF::PE::Parser::parse(data, parserConfig);
}