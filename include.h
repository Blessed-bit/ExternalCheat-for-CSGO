#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <typeinfo>
#include <Windows.h>
#include <TlHelp32.h>


#include <cstdint>
#include <string_view>
#include "Windows.h"
#include "memory.h"
#include "offsets.h"
#include "Color.h"
#include "HeaderClass.h"

using namespace offsets::signatures;
using namespace offsets::netvars;

inline std::uintptr_t g_client_base;

