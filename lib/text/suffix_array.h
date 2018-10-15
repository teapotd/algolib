#pragma once
#include "../template.h"
#include "kmr.h"

// Compute suffix array for KMR-precomputed
// string; time: O(n lg n)
Vi sufArray(const KMR& kmr) {
	Vi sufs(sz(kmr.ids.back()));
	iota(all(sufs), 0);
	sort(all(sufs), [&](int l, int r) {
		return kmr.ids.back()[l]<kmr.ids.back()[r];
	});
	return sufs;
}

// Compute Longest Common Prefix array for
// given string and it's suffix array; O(n)
template<class T>
Vi lcpArray(const T& str, const Vi& sufs) {
	int n = sz(str), k = 0;
	Vi pos(n), lcp(n-1);

	rep(i, 0, n) pos[sufs[i]] = i;

	rep(i, 0, n) {
		if (pos[i] < n-1) {
			int j = sufs[pos[i]+1];
			while (i+k < n && j+k < n &&
					str[i+k] == str[j+k]) k++;
			lcp[pos[i]] = k;
		}
		if (k > 0) k--;
	}
	return lcp;
}
