#pragma once
#include "../template.h"

// NxN matrix A is simple (sub-)unit-Monge
// iff there exists a (sub-)permutation
// (N-1)x(N-1) matrix P such that:
//   A[x,y] = sum i>=x, j<y: P[i,j]
// The first column and last row are always 0.
// We represent these matrices implicitly
// using permutations p s.t. P[i,p(i)] = 1.

// (min, +) product of simple unit-Monge
// matrices represented by permutations P, Q,
// is also a simple unit-Monge matrix.
// The permutation that describes the product
// can be obtained by the following procedure:
// 1. Decompose P, Q into minimal sequences of
//    elementary transpositions.
// 2. Concatenate the transposition sequences.
// 3. Scan from left to right and remove
//    transpositions that decrease
//    inversion count (i.e. second crossings).
// 4. The reduced sequence represents result.

// Invert sub-permutation with values [0;n).
// Missing values should have value `def`.
Vi invert(const Vi& P, int n, int def) {
	Vi ret(n, def);
	rep(i, 0, sz(P)) if (P[i] != def)
		ret[P[i]] = i;
	return ret;
}

// Split permutation P into half `lo`
// with values less than `k`, and half `hi`
// with remaining values, shifted by `k`.
// Missing rows from `lo` and `hi` are removed,
// original indices are in `loInd` and `hiInd`.
void split(const Vi& P, int k, Vi& lo, Vi& hi,
           Vi& loInd, Vi& hiInd) {
  int i = 0;
	each(e, P) {
		if (e < k) lo.pb(e), loInd.pb(i++);
		else hi.pb(e-k), hiInd.pb(i++);
	}
}

// Map sub-permutation into sub-permutation
// of length `n` on given indices sets.
Vi expand(const Vi& P, Vi& ind1, Vi& ind2,
          int n, int def) {
	Vi ret(n, def);
	rep(k, 0, sz(P)) if (P[k] != def)
		ret[ind1[k]] = ind2[P[k]];
	return ret;
}

// Compute (min, +) product of square
// simple unit-Monge matrices given their
// permutation representations; time: O(n lg n)
// Permutation of second matrix is inverted!
//! Source: https://arxiv.org/pdf/0707.3619.pdf
Vi comb(const Vi& P, const Vi& invQ) {
	int n = sz(P);

	if (n < 100) {
		// 5s -> 1s speedup for ALIS for n = 10^5
		Vi ret = invert(P, n, -1);
		rep(i, 0, sz(invQ)) {
			int from = invQ[i];
			rep(j, 0, i) from += invQ[j] > invQ[i];
			for (int j = from; j > i; j--)
				if (ret[j-1] < ret[j])
					swap(ret[j-1], ret[j]);
		}
		return invert(ret, n, -1);
	}

	Vi p1, p2, q1, q2, i1, i2, j1, j2;
	split(P, n/2, p1, p2, i1, i2);
	split(invQ, n/2, q1, q2, j1, j2);

	p1 = expand(comb(p1, q1), i1, j1, n, -1);
	p2 = expand(comb(p2, q2), i2, j2, n, n);
	q1 = invert(p1, n, -1);
	q2 = invert(p2, n, n);

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

// Helper function for `mongeMul`.
void padPerm(const Vi& P, Vi& has, Vi& pad,
            Vi& ind, int n) {
	vector<bool> seen(n);
	rep(i, 0, sz(P)) if (P[i] != -1) {
		ind.pb(i);
		has.pb(P[i]);
		seen[P[i]] = 1;
	}
	rep(i, 0, n) if (!seen[i]) pad.pb(i);
}

// Compute (min, +) product of
// simple sub-unit-Monge matrices given their
// permutation representations; time: O(n lg n)
// Left matrix has size sz(P) x sz(Q).
// Right matrix has size sz(Q) x n.
// Output matrix has size sz(P) x n.
// NON-SQUARE MATRICES ARE NOT TESTED!
//! Source: https://arxiv.org/pdf/0707.3619.pdf
Vi mongeMul(const Vi& P, const Vi& Q, int n) {
	Vi h1, p1, i1, h2, p2, i2;
	padPerm(P, h1, p1, i1, sz(Q));
	padPerm(invert(Q, n, -1), h2, p2, i2, sz(Q));

	h1.insert(h1.begin(), all(p1));
	h2.insert(h2.end(), all(p2));
	Vi ans(sz(P), -1), tmp = comb(h1, h2);

	rep(i, 0, sz(i1)) {
		int j = tmp[i+sz(p1)];
		if (j < sz(i2)) {
			ans[i1[i]] = i2[j];
		}
	}
	return ans;
}

// Range Longest Increasing Subsequence Query;
// preprocessing: O(n lg^2 n), query: O(lg n)
#include "../structures/wavelet_tree.h"
struct ALIS {
	WaveletTree tree;
	ALIS() {}

	// Precompute data structure; O(n lg^2 n)
	ALIS(const Vi& seq) {
		Vi P = build(seq);
		each(k, P) if (k == -1) k = sz(seq);
		tree = {P, sz(seq)+1};
	}

	// Query LIS of s[b;e); time: O(lg n)
	int operator()(int b, int e) {
		return e - b -
			tree.count(b, sz(tree.seq[1]), 0, e);
	}

	Vi build(const Vi& seq) {
		int n = sz(seq);
		if (!n) return {};
		int lo = *min_element(all(seq));
		int hi = *max_element(all(seq));

		if (lo == hi) {
			Vi tmp(n);
			iota(all(tmp), 1);
			tmp.back() = -1;
			return tmp;
		}

		int mid = (lo+hi+1) / 2;
		Vi p1, p2, i1, i2;
		split(seq, mid, p1, p2, i1, i2);

		p1 = expand(build(p1), i1, i1, n, -1);
		p2 = expand(build(p2), i2, i2, n, -1);
		each(j, i1) p2[j] = j;
		each(j, i2) p1[j] = j;
		return mongeMul(p1, p2, n);
	}
};
