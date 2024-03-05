#pragma once

#include <iostream>
#include <functional>
#include <chrono>
#include <string>

#include "Dumper.hpp"

class Manager {
public:
	template <typename FunctionType>
	Manager(FunctionType readMemory, FunctionType writeMemory);
	~Manager();

private:
	std::function<void(const void*)> readMemory, writeMemory;
	Dumper* dumper;
};