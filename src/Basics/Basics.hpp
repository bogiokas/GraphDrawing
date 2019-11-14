#pragma once
#include<array>
#include<vector>
#include<unordered_set>
#include<cmath>
#include<memory>
#include<optional>
#include<iterator>
#include<algorithm>
#include<cassert>

//#define _DEBUG 0

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

constexpr double EPS = 1.0e-5;
constexpr double EPSQ = EPS*EPS;

using Index = size_t;

class Color {
public:
	Color operator+(const Color& c) const {
		return {r+c.r, g+c.g, b+c.b, a+c.a};
	}
	double r, g, b, a;
};

static constexpr Color RED = {0.5f, 0.0f, 0.0f, 1.0f};
static constexpr Color GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
static constexpr Color BLUE = {0.0f, 0.0f, 1.0f, 1.0f};

