#pragma once
#include "../template.h"

// Interpolates set of points (i, vec[i])
// and returns it evaluated at x; time: O(n^2)
// TODO: Improve to linear time
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
