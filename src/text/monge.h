#pragma once
#include "../template.h"

// Invert subpermutation.
// Missing values are set to `def`.
Vi invert(const Vi& P, int def = -1) {
	Vi ret(sz(P), def);
	rep(i, 0, sz(P))
		if (P[i] >= 0 && P[i] < sz(P))
			ret[P[i]] = i;
	return ret;
}

// Split permutation P into half `lo` with low
// values and half `hi` with high values.
// Missing rows from `lo` and `hi` are removed,
// original indices are in `loInd` and `hiInd`.
void split(const Vi& P, Vi& lo, Vi& hi,
           Vi& loInd, Vi& hiInd) {
  int i = 0;
	each(e, P) {
		if (e < sz(P)/2) lo.pb(e), loInd.pb(i++);
		else hi.pb(e - sz(P)/2), hiInd.pb(i++);
	}
}

// Expand permutation into subpermutation
// of length `n` on given indices sets.
Vi expand(const Vi& P, Vi& ind1, Vi& ind2,
          int n, int def) {
	Vi ret(n, def);
	rep(k, 0, sz(P)) ret[ind1[k]] = ind2[P[k]];
	return ret;
}

// Compute (min, +) product of square
// simple unit-Monge matrices given their
// permutation representations; O(n log n)
//! Source: https://arxiv.org/pdf/0707.3619.pdf
Vi mongeMul(const Vi& P, const Vi& Q) {
	int n = sz(P);
	if (n <= 1) return P;

	Vi p1, p2, q1, q2, i1, i2, j1, j2;
	split(P, p1, p2, i1, i2);
	split(invert(Q), q1, q2, j1, j2);

	p1 = mongeMul(p1, invert(q1));
	p2 = mongeMul(p2, invert(q2));

	p1 = expand(p1, i1, j1, n, -1);
	p2 = expand(p2, i2, j2, n, n);
	q1 = invert(p1, -1);
	q2 = invert(p2, n);

	Vi ans(n, -1);
	int delta = 0, j = n;

	rep(i, 0, n) {
		ans[i] = (p1[i] < 0 ? p2[i] : p1[i]);
		while (j > 0 && delta >= 0)
			delta -= (q2[--j] < i || q1[j] >= i);

		if (p2[i] < j || p1[i] >= j)
			if (delta++ < 0)
				if (q2[j] < i || q1[j] >= i)
					ans[i] = j;
	}

	return ans;
}
