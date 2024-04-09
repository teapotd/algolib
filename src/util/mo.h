#pragma once
#include "../template.h"
//!!EXCLUDE-FILE

// Modified MO's queries sorting algorithm,
// slightly better results than standard.
// Allows to process q queries in O(n*sqrt(q))

struct Query {
	int begin, end;
};

// Get point index on Hilbert curve
ll hilbert(int x, int y, int s, ll c = 0) {
	if (s <= 1) return c;
	s /= 2; c *= 4;
	if (y < s)
		return hilbert(x&(s-1), y, s, c+(x>=s)+1);
	if (x < s)
		return hilbert(2*s-y-1, s-x-1, s, c);
	return hilbert(y-s, x-s, s, c+3);
}

// Get good order of queries; time: O(n lg n)
vi moOrder(vector<Query>& queries, int maxN) {
	int s = 1;
	while (s < maxN) s *= 2;

	vector<ll> ord;
	each(q, queries)
		ord.pb(hilbert(q.begin, q.end, s));

	vi ret(sz(ord));
	iota(all(ret), 0);
	sort(all(ret), [&](int l, int r) {
		return ord[l] < ord[r];
	});
	return ret;
}
