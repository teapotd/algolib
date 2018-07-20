#pragma once
#include "../template.h"

// Returns W(x), where W is interpolated vec
template<typename T>
T polyExtend(vector<T>& vec, T x) {
	T ret = 0;
	rep(i, 0, sz(vec)) {
		T a = vec[i], b = 1;
		rep(j, 0, sz(vec)) if (i != j) {
			a *= x-j; b *= i-j;
		}
		ret += a/b;
	}
	return ret;
}
