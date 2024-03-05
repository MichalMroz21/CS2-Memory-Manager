#pragma once

#include <source_location>
#include <string_view>
#include <iostream>

static void Assert(bool expr, std::string_view msg, std::string_view success_msg = "", std::source_location location = std::source_location::current()) {
	if (!expr) {
		std::cerr << "[CS2-Memory-Manager][X] " << msg << '\n'
			<< "File: " << location.file_name()
			<< "Line: " << location.line() << ":" << location.column() << '\n'
			<< "Function: " << location.function_name();
		abort();
	}
	else if (!success_msg.empty()) std::cout << "[+] " << success_msg << '\n';
}

static void PrintMsg(std::string_view msg) {
	std::cout << "[CS2-Memory-Manager] " << msg << '\n';
}