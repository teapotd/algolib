#pragma once
#include "../template.h"

using Row = vector<double>;
using Matrix = vector<Row>;
constexpr double eps = 1e-9;

// Given a system of n linear equations A
// over m variables, find dimensionality D
// of solution subspace, matrix M and vector t
// such that:
// - matrix M is orthogonal (i.e. M*M^T = I)
// - x is a solution <=> (Mx+t)[D..] = 0
// - x[D..] = 0 <=> M^T(x-t) is a solution
//   (in particular -M^T*t is a solution)
// Returns number of dimensions D, or -1 if
// there is no solution; time: O(n^2*m + n*m^2)
// Warning: numerical stability is kinda sus
int orthoGauss(Matrix& A, Matrix& M,
               Row& t, int m) {
	int d = m;
	t.assign(m, 0);
	M.assign(m, Row(m));
	rep(i, 0, m) M[i][i] = 1;

	rep(i, 0, sz(A)) {
		auto& w = A[i];
		double s = 0;
		rep(j, 0, d) s += w[j]*w[j];
		if (fabs(s) < eps) {
			if (fabs(w[m]) > eps) return -1;
			continue;
		}

		double r = sqrt(s);
		if (w[d-1] < 0) r = -r;
		s = sqrt((s + w[d-1]*r)*2);
		w[d-1] += r;
		rep(j, 0, d) w[j] /= s;
		r = w[m] / (w[d-1] * r * 2);

		rep(j, i+1, sz(A)) {
			s = 0;
			rep(k, 0, d) s += A[j][k] * w[k];
			s *= 2;
			rep(k, 0, d) A[j][k] -= s * w[k];
			A[j][m] -= s*r;
		}

		rep(j, 0, m) {
			s = 0;
			rep(k, 0, d) s += M[k][j] * w[k];
			s *= 2;
			rep(k, 0, d) M[k][j] -= s * w[k];
		}

		s = -r;
		rep(k, 0, d) s += t[k] * w[k];
		s *= 2;
		rep(k, 0, d) t[k] -= s * w[k];
		d--;
	}

	return d;
}
