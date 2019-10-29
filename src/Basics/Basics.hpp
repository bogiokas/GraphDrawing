#pragma once
#include<array>
#include<vector>
#include<cmath>
#include<memory>
#include<optional>
#include<iterator>
#include<algorithm>

//#define _DEBUG 0

constexpr double EPS = 1.0e-5;
constexpr double EPSQ = EPS*EPS;

using Index = size_t;

class Math {
public:
	static Index powInd(Index k, Index n) {
		if(n == 0) return 1;
		if(n % 2 == 1) return k * powInd(k, n-1);
		return powInd(k, n/2) * powInd(k, n/2);
	}
	static Index Factorial(Index n) {
		if(n == 0) return 1;
		return n * Factorial(n-1);
	}
	static Index Combinations(Index n, Index k) {
		return Factorial(n)/(Factorial(k)*Factorial(n-k));
	}
};

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

