#pragma once
#include "../template.h"

using dbl = double;
using Row = vector<dbl>;
using Matrix = vector<Row>;
#define mp make_pair

#define ltj(X) if (s == -1 || \
	mp(X[j], N[j]) < mp(X[s], N[s])) s = j

// Simplex algorithm; time: O(nm * pivots)
// Given m x n matrix A, vector b of length m,
// vector c of length n solves the following:
//   maximize c^T x, Ax <= b, x >= 0
// Output vector `x` contains optimal solution
// or some feasible solution in unbounded case.
// Returns objective value if bounded,
// +inf if unbounded, and -inf if no solution.
// You can test if double is inf using `isinf`.
// PARTIALLY TESTED
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/Simplex.h
dbl simplex(const Matrix& A,
            const Row& b, const Row& c,
            Row& x, dbl eps = 1e-8) {
	int m = sz(b), n = sz(c);
	x.assign(n, 0);
	if (!n) return
		*min_element(all(b)) < -eps ? -1/.0 : 0;

	vi N(n+1), B(m);
	Matrix D(m+2, Row(n+2));

	auto pivot = [&](int r, int s) {
		dbl inv = 1 / D[r][s];
		rep(i, 0, m+2)
			if (i != r && abs(D[i][s]) > eps) {
				dbl tmp = D[i][s] * inv;
				rep(j,0,n+2) D[i][j] -= D[r][j] * tmp;
				D[i][s] = D[r][s] * tmp;
			}
		each(k, D[r]) k *= inv;
		each(k, D) k[s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	};

	auto solve = [&](int phase) {
		for (int y = m+phase-1;;) {
			int s = -1, r = -1;
			rep(j, 0, n+1)
				if (N[j] != -phase) ltj(D[y]);
			if (D[y][s] >= -eps) return 1;
			rep(i, 0, m)
				if (D[i][s] > eps && (r == -1 ||
					mp(D[i][n+1] / D[i][s], B[i]) <
					mp(D[r][n+1] / D[r][s], B[r]))) r=i;
			if (r == -1) return 0;
			pivot(r, s);
		}
	};

	rep(i, 0, m) {
		copy(all(A[i]), D[i].begin());
		B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];
	}
	rep(j, 0, n) D[m][N[j] = j] = -c[j];
	N[n] = -1; D[m+1][n] = 1;

	int r = 0;
	rep(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
	if (D[r][n+1] < -eps) {
		pivot(r, n);
		if (!solve(2) || D[m+1][n+1] < -eps)
			return -1/.0;
		rep(i, 0, m) if (B[i] == -1) {
			int s = 0;
			rep(j, 1, n+1) ltj(D[i]);
			pivot(i, s);
		}
	}
	bool ok = solve(1);
	rep(i,0,m) if (B[i] < n) x[B[i]] = D[i][n+1];
	return ok ? D[m][n+1] : 1/.0;
}
