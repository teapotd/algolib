#pragma once
#include "../template.h"

// Stable countingsort; time: O(k+sz(vec))
// See example usage in radixSort for pairs.
template<class F>
void countSort(vi& vec, F key, int k) {
	static vi buf, cnt;
	vec.swap(buf);
	vec.resize(sz(buf));
	cnt.assign(k+1, 0);
	each(e, buf) cnt[key(e)]++;
	rep(i, 1, k+1) cnt[i] += cnt[i-1];
	for (int i = sz(vec)-1; i >= 0; i--)
		vec[--cnt[key(buf[i])]] = buf[i];
}

// Compute order of elems, k is max key; O(n)
vi radixSort(const vector<pii>& elems, int k) {
	vi order(sz(elems));
	iota(all(order), 0);
	countSort(order,
		[&](int i) { return elems[i].y; }, k);
	countSort(order,
		[&](int i) { return elems[i].x; }, k);
	return order;
}
