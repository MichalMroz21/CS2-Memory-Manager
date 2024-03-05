#include "Manager.hpp"

template <typename FunctionType>
Manager::Manager(FunctionType readMemory, FunctionType writeMemory){

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	//Building Manager
	readMemory = readMemory;
	writeMemory = writeMemory;

	dumper = new Dumper();

	dumper->dump_schemas();
	dumper->dump_interfaces();
	dumper->dump_offsets();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	PrintMsg("Built Manager in " + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) + "[ns]");
}

Manager::~Manager() {
	free(dumper);
}