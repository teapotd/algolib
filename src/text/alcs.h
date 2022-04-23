#pragma once
#include "../template.h"

// All-substrings common sequences algorithm.
// Given strings A and B, algorithm computes:
//   C(i,j,k) = |LCS(A[:i), B[j:k))|
// in compressed form; time and space: O(n^2)
// To describe the compression, note that:
// 1. C(i,j,k-1) <= C(i,j,k) <= C(i,j,k-1)+1
// 2. If j < k and C(i,j,k) = C(i,j,k-1)+1,
//    then C(i,j+1,k) = C(i,j+1,k-1)+1
// 3. If j >= k, then C(i,j,k) = 0
// This allows us to store just the following:
//   ih(i,k) = min j s.t. C(i,j,k-1) < C(i,j,k)
//! Source: https://www.sciencedirect.com/science/article/pii/S0166218X07002727.
struct ALCS {
	string A, B;
	vector<Vi> ih;

	ALCS() {}

	// Precompute compressed matrix; time: O(nm)
	ALCS(string s, string t) : A(s), B(t) {
		int n = sz(A), m = sz(B);
		vector<Vi> iv(n+1, Vi(m+1));
		ih.resize(n+1, Vi(m+1));
		iota(all(ih[0]), 0);
		rep(l, 1, n+1) rep(j, 1, m+1) {
			if (A[l-1] != B[j-1]) {
				ih[l][j] = max(iv[l][j-1], ih[l-1][j]);
				iv[l][j] = min(iv[l][j-1], ih[l-1][j]);
			} else {
				ih[l][j] = iv[l][j-1];
				iv[l][j] = ih[l-1][j];
			}
		}
	}

	// Compute |LCS(A[:i), B[j:k))|; time: O(k-j)
	// Note: You can precompute data structure
	// to answer these queries in O(log n)
	// or compute all answers for fixed `i`.
	int operator()(int i, int j, int k) {
		int ret = 0;
		rep(q, j, k) ret += (ih[i][q+1] <= j);
		return ret;
	}

	// Compute subsequence LCS(A[:i), B[j:k));
	// time: O(k-j)
	string recover(int i, int j, int k) {
		string ret;
		while (i > 0 && j < k) {
			if (ih[i][k--] <= j) {
				ret.pb(B[k]);
				while (A[--i] != B[k]);
			}
		}
		reverse(all(ret));
		return ret;
	}

	// Compute LCS'es of given prefix of A,
	// and all prefixes of given suffix of B.
	// Returns vector L of length |B|+1 s.t.
	// L[k] = |LCS(A[:i), B[j:k))|; time: O(|B|)
	Vi row(int i, int j) {
		Vi ret(sz(B)+1);
		rep(k, j+1, sz(ret))
			ret[k] = ret[k-1] + (ih[i][k] <= j);
		return ret;
	}

	// Compute LCS'es of given prefix of A,
	// and all substrings of B; time: O(n^2)
	// Return matrix M such that:
	// M[j][k] = |LCS(A[:i), B[j:j+k))|
	vector<Vi> matrix(int i) {
		vector<Vi> ret;
		rep(j, 0, sz(B)+1) ret.pb(row(i, j));
		return ret;
	}
};
