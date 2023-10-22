#pragma once
#include "../template.h"

// Compute Longest Common Prefix array for
// given string and it's suffix array; O(n)
// In order to compute suffix array use kmr.h
// or suffix_array_linear.h
vi lcpArray(auto& str, vi& sufs) {
	int n = sz(str), k = 0;
	vi pos(n), lcp(n-1);
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
