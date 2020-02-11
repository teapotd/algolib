#pragma once
#include "../template.h"

// Interpolate set of points (i, vec[i])
// and return it evaluated at x; time: O(n)
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

// Given n points (x, f(x)) compute n-1-degree
// polynomial f that passes through them;
// time: O(n^2)
// For O(n lg^2 n) version see polynomial.h
template<class T>
vector<T> polyInterp(vector<pair<T, T>> P) {
	int n = sz(P);
	vector<T> ret(n), tmp(n);
	T last = 0;
	tmp[0] = 1;

	rep(k, 0, n-1) rep(i, k+1, n)
		P[i].y = (P[i].y-P[k].y) / (P[i].x-P[k].x);

	rep(k, 0, n) rep(i, 0, n) {
		ret[i] += P[k].y * tmp[i];
		swap(last, tmp[i]);
		tmp[i] -= last * P[k].x;
	}
	return ret;
}
