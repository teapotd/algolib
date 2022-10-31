#pragma once
#include "../template.h"

// Run `n` binary searches on [b;e) parallely.
// `cmp` should be lambda with arguments:
// 1) vector<pii>& - pairs (v, i)
//    which are queries if value for index i
//    is greater or equal to v;
//    pairs are sorted by v
// 2) vector<bool>& - output vector,
//    set true at index i if value
//    for i-th query is >= queried value
// Returns vector of found values;
// time: O((n+c) lg range), where c is cmp time
template<class T>
vi multiBS(int b, int e, int n, T cmp) {
	if (b >= e) return vi(n, b);
	vector<pii> que(n), rng(n, {b, e});
	vector<bool> ans(n);

	rep(i, 0, n) que[i] = {(b+e)/2, i};

	for (int k = __lg(e-b); k >= 0; k--) {
		int last = 0, j = 0;
		cmp(que, ans);
		rep(i, 0, sz(que)) {
			pii &q = que[i], &r = rng[q.y];
			if (q.x != last) last = q.x, j = i;
			(ans[i] ? r.x : r.y) = q.x;
			q.x = (r.x+r.y) / 2;
			if (!ans[i]) swap(que[i], que[j++]);
		}
	}

	vi ret;
	each(p, rng) ret.pb(p.x);
	return ret;
}
