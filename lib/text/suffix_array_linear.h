#pragma once
#include "../template.h"
#include "../util/radix_sort.h"

// KS algorithm for suffix array; time: O(n)
// Input values are assumed to be in [1;k]
// UNTESTED and NOT OPTIMIZED
Vi sufArray(Vi str, int k) {
	int n = sz(str);
	Vi suf(n);
	str.resize(n+2, 0);

	if (n < 12) { // Adjust naive threshold
		iota(all(suf), 0);
		sort(all(suf), [&](int l, int r) {
			while (l < n && r < n) {
				if (str[l] != str[r])
					return str[l] < str[r];
				l++; r++;
			}
			return l > r;
		});
		return suf;
	}

	// Compute triples codes
	Vi tmp(n), code(n+2);
	iota(all(tmp), 0);

	rep(j, 0, 3) countSort(tmp,
		[&](int i) { return str[i+2-j]; }, k);

	int last = 0, j = -1;

	each(i, tmp) {
		if (j == -1 || str[i] != str[j] ||
		    str[i+1] != str[j+1] ||
		    str[i+2] != str[j+2]) last++;
		code[i] = last;
		j = i;
	}

	// Compute suffix array of 2/3
	tmp.clear();
	for (int i=1; i < n; i += 3) tmp.pb(code[i]);
	tmp.pb(0);
	int thr = sz(tmp);
	for (int i=2; i < n; i += 3) tmp.pb(code[i]);
	tmp = sufArray(move(tmp), n);

	// Compute partial suffix arrays
	Vi third;
	if (n%3 == 1) third.pb(n-1);
	rep(i, 1, sz(tmp)) {
		int e = tmp[i];
		tmp[i-1] = (e < thr ? e*3+1 : (e-thr)*3+2);
		code[tmp[i-1]] = i;
		if (e < thr) third.pb(e*3);
	}

	tmp.pop_back();
	countSort(third,
		[&](int i) { return str[i]; }, k);

	// Merge suffix arrays
	merge(all(third), all(tmp), suf.begin(),
		[&](int l, int r) {
			while (l%3 == 0 || r%3 == 0) {
				if (str[l] != str[r])
					return str[l] < str[r];
				l++; r++;
			}
			return code[l] < code[r];
		});

	return suf;
}

// KS algorithm for suffix array; time: O(n)
Vi sufArray(const string& str) {
	return sufArray(Vi(all(str)), 255);
}
