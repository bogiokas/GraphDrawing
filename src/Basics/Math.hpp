#pragma once
#include "Basics/Basics.hpp"

class Math {
public:
	static Index powInd(Index k, Index n) {
		if(n == 0) return 1;
		if(n % 2 == 1) return k * powInd(k, n-1);
		return powInd(k, n/2) * powInd(k, n/2);
	}
	static Index powOf2(Index n) {
		return powInd(2, n);
	}
	static bool isPowOf2(Index N) {
		return N!=0 && ( (N & (N-1)) == 0 );
	}
	static Index Factorial(Index n) {
		if(n == 0) return 1;
		return n * Factorial(n-1);
	}
	static Index Combinations(Index n, Index k) {
		return Factorial(n)/(Factorial(k)*Factorial(n-k));
	}
};

