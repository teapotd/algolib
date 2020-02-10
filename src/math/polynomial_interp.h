#pragma once
#include "../template.h"

// Interpolates set of points (i, vec[i])
// and returns it evaluated at x; time: O(n)
template<class T>
T polyExtend(vector<T>& vec, T x) {
	int n = sz(vec);
	vector<T> fac(n, 1), suf(n, 1);

	rep(i, 1, n) fac[i] = fac[i-1] * i;
	for (int i=n; --i;) suf[i-1] = suf[i]*(x-i);

	T pref = 1, ret = 0;
	rep(i, 0, n) {
		T d = fac[i] * fac[n-i-1] * ((n-i)%2*2-1);
		ret += vec[i] * suf[i] * pref / d;
		pref *= x-i;
	}
	return ret;
}
