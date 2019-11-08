#pragma once
#include "../template.h"

constexpr int MAX_COLS = 2048;

// Solve system of linear equations over Z_2
// time: O(n^2*m/W), where W is word size
// - A - extended matrix, rows are equations,
//       columns are variables,
//       m-th column is equation result
//       (A[i][j] - i-th row and j-th column)
// - ans - output for variables values
// - m - variable count
// Returns 0 if no solutions found, 1 if one,
// 2 if more than 1 solution exist.
int bitGauss(vector<bitset<MAX_COLS>>& A,
             vector<bool>& ans, int m) {
	Vi col;
	ans.assign(m, 0);

	rep(i, 0, sz(A)) {
		int c = int(A[i]._Find_first());
		if (c >= m) {
			if (c == m) return 0;
			continue;
		}

		rep(k, i+1, sz(A)) if (A[k][c]) A[k]^=A[i];
		swap(A[i], A[sz(col)]);
		col.pb(c);
	}

	for (int i = sz(col); i--;) if (A[i][m]) {
		ans[col[i]] = 1;
		rep(k,0,i) if(A[k][col[i]]) A[k][m].flip();
	}

	return sz(col) < m ? 2 : 1;
}
