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
#include "InitClass.h"

using namespace offsets::signatures;
using namespace offsets::netvars;

inline std::uintptr_t g_client_base;
<<<<<<< HEAD
inline Memory g_mem;
=======

>>>>>>> 2ecc88bb2c945c9a6373089e7bd9f6011df627e5
