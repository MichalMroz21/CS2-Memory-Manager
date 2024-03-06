#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Assert.hpp"

class Dumper {
public:
	Dumper();
	DWORD get_process_id();
	HANDLE get_process_handle();
	void get_loaded_modules();
	bool read_memory_bytes(uintptr_t address, LPVOID buffer, SIZE_T size);

	void dump_schemas();
	void dump_interfaces();
	void dump_offsets();

	void find_pattern(std::string module_name, std::string pattern);
	std::vector<int> pattern_to_bytes(const std::string& pattern);

	template<typename T>
	T read_memory_one_val(uintptr_t address);

private:
	DWORD cs2_pid{};
	HANDLE cs2_handle{};
	std::unordered_map<std::string, std::vector<uint8_t>> modules{};
};
