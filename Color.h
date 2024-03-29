#pragma once
#include "include.h"

struct color {
	constexpr color(float r, float g, float b, float a = 1.f) noexcept :
		r(r), b(b), g(g), a(a) {};
	float r, g, b, a;
};

struct �olorc4 {
	constexpr �olorc4(float r, float g, float b, float a = 1.f) noexcept :
		r(r), b(b), g(g), a(a) {};
	float r, g, b, a;
};

struct bo {
	constexpr bo(bool x = true, bool y = true) noexcept :
		x(x), y(y) {};
	bool x, y;
};
