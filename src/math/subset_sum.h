#pragma once
#include "../template.h"
#include "polynomial.h"

// Count number of possible subsets that sum
// to t for each t = 1, ..., n; O(n log n)
// Input elements are given by frequency array,
// i.e. counts[x] = how many times elements x
// is contained in the multiset.
// Requires counts[0] == 0.
//! Source: https://arxiv.org/pdf/1807.11597.pdf
Poly subsetSum(Poly counts, int n) {
	assert(counts[0].x == 0);
	Poly mul(n);
	rep(i, 0, n)
		mul[i] = Zp(i).inv() * (i%2 ? 1 : -1);
	counts.resize(n);
	for (int i = n-2; i > 0; i--)
		for (int j = 2; i*j < n; j++)
			counts[i*j] += mul[j] * counts[i];
	return exp(counts, n);
}
