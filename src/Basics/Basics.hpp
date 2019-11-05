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

template<class T> struct Unique_Ptr_Eq {
public:
	bool operator()(const std::unique_ptr<T>& ptr1, const std::unique_ptr<T>& ptr2) const { return *ptr1 == *ptr2; }
};

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

