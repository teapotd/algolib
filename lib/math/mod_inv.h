#pragma once
#include "../template.h"

template<class T>
T modInv(T a, T b) {
	T u = 1, v = 0, x = 0, y = 1, m = b;

	while (a > 0) {
		T q = b / a, r = b % a;
		T m = x - u*q, n = y - v*q;
		b = a; a = r; x = u; y = v; u = m; v = n;
	}
	return (b == 1 ? (x < 0 ? x+m : x) : 0);
}
