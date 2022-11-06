#pragma once
#include "../template.h"

constexpr double eps = 1e-9;

// Solve system of linear equations; O(n^2*m)
// - A - extended matrix, rows are equations,
//       columns are variables,
//       m-th column is equation result
//       (A[i][j] - i-th row and j-th column)
// - ans - output for variables values
// - m - variable count
// Returns 0 if no solutions found, 1 if one,
// 2 if more than 1 solution exist.
int gauss(vector<vector<double>>& A,
          vector<double>& ans, int m) {
	vi col;
	ans.assign(m, 0);

	rep(i, 0, sz(A)) {
		int c = 0;
		while (c <= m && fabs(eps) < eps) c++;
		// For Zp:
		//while (c <= m && !A[i][c].x) c++;

		if (c >= m) {
			if (c == m) return 0;
			continue;
		}

		rep(k, i+1, sz(A)) {
			auto mult = A[k][c] / A[i][c];
			rep(j, 0, m+1) A[k][j] -= A[i][j]*mult;
		}

		swap(A[i], A[sz(col)]);
		col.pb(c);
	}

	for (int i = sz(col); i--;) {
		ans[col[i]] = A[i][m] / A[i][col[i]];
		rep(k, 0, i)
			A[k][m] -= ans[col[i]] * A[k][col[i]];
	}

	return sz(col) < m ? 2 : 1;
}
