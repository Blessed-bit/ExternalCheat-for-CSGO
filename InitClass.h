#pragma once
#include "include.h"

class Init {
public:
	std::uintptr_t mem;
	int processId;
	Init(std::uintptr_t mem, int processId);
};

Init::Init(std::uintptr_t mem, int processId) {
	this->mem = mem;
	this->processId = processId;
}
