#include "Dumper.hpp"
#include "PeModule.hpp"

Dumper::Dumper() {
	cs2_pid = get_process_id();
	Assert(cs2_pid != 0, "Couldn't find cs2.exe. Use Manager Class only when cs2.exe is active.");

	cs2_handle = get_process_handle();
	Assert(cs2_handle != 0, "Couldn't get cs2 handle");

	get_loaded_modules();
}

void Dumper::find_pattern(std::string module_name, std::string pattern) {
	/*PeModule* module = new PeModule(module_name, modules[module_name]);

	std::vector<int> patternBytes = pattern_to_bytes(pattern);
	std::vector<uint8_t> moduleData = module->data;

	for (size_t i = 0; i + patternBytes.size() <= moduleData.size(); ++i) {
		// Get the window from the current position
		std::vector<uint8_t> window(moduleData.begin() + i, moduleData.begin() + i + patternBytes.size());

		// Check if the window matches the pattern
		bool match = true;
		for (size_t j = 0; j < window.size(); ++j) {
			if (patternBytes[j] != -1 && window[j] != static_cast<uint8_t>(patternBytes[j])) {
				match = false;
				break;
			}
		}

		if (match) {
			// Pattern found, return the index
			return static_cast<int>(i);
		}
	}

	// Pattern not found
	return -1;*/
}

void Dumper::dump_schemas(){

	

}

void Dumper::dump_interfaces(){



}

void Dumper::dump_offsets(){


}

std::vector<int> Dumper::pattern_to_bytes(const std::string& pattern) {
	/*std::istringstream iss(pattern);
	std::vector<int> result;

	for (std::string token; iss >> token;) {
		if (token == "?") {
			result.push_back(-1);
		}
		else {
			try {
				result.push_back(std::stoi(token, nullptr, 16));
			}
			catch (const std::invalid_argument&) {
				result.push_back(0);
			}
		}
	}

	return result;*/
}

void Dumper::get_loaded_modules() {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, cs2_pid);

	Assert(snapshot != INVALID_HANDLE_VALUE, "Invalid Handle from cs2_pid");

	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(snapshot, &entry)) {

		do {
			std::string name = entry.szModule;
			std::vector<uint8_t> data(entry.modBaseSize);

			Assert(read_memory_bytes((uintptr_t)entry.modBaseAddr, data.data(), entry.dwSize), "Failed to read data of module: " + name);

			modules[name] = data;
		
		} while (Module32Next(snapshot, &entry));
	}
}

template<typename T>
T Dumper::read_memory_one_val(uintptr_t address){
	Assert(std::is_trivially_copyable<T>::value, "Type T must be trivially copyable.");

	T value;
	Assert(read_memory_bytes(cs2_handle, &value, sizeof(T)), "Failed to read memory of a value"); 
	return value;
}

bool Dumper::read_memory_bytes(uintptr_t address, LPVOID buffer, SIZE_T size){
	return ReadProcessMemory(cs2_handle, reinterpret_cast<LPCVOID>(address), buffer, size, nullptr);
}

HANDLE Dumper::get_process_handle() {
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, cs2_pid);
}

DWORD Dumper::get_process_id(){

	DWORD process_id = 0;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (snapshot == INVALID_HANDLE_VALUE)
	return process_id;

	PROCESSENTRY32W entry = {};
	entry.dwSize = sizeof(decltype(entry));

	if (Process32FirstW(snapshot, &entry) == TRUE) {

		if (_wcsicmp(L"cs2.exe", entry.szExeFile) == 0)
			process_id = entry.th32ProcessID;

		else {
			while (Process32NextW(snapshot, &entry) == TRUE) {
				if (_wcsicmp(L"cs2.exe", entry.szExeFile) == 0) {
					process_id = entry.th32ProcessID;
					break;
				}
			}
		}
	}

	CloseHandle(snapshot);
	return process_id;
}