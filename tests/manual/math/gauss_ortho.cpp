#include "../../../src/math/gauss_ortho.h"
#include "../testing.h"

int gauss(Matrix A, Row& ans, int m) {
	Vi col;
	ans.assign(m, 0);

	rep(i, 0, sz(A)) {
		int c = 0;
		while (c <= m && !cmp(A[i][c], 0)) c++;

		if (c >= m) {
			if (c == m) return -1;
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

	return m - sz(col);
}

// Add rows
Row& operator+=(Row& l, const Row& r){
	rep(i, 0, sz(l)) l[i] += r[i];
	return l;
}
Row operator+(Row l, const Row& r) {
	return l += r;
}

// Subtract rows
Row& operator-=(Row& l, const Row& r){
	rep(i, 0, sz(l)) l[i] -= r[i];
	return l;
}
Row operator-(Row l, const Row& r) {
	return l -= r;
}

// Multiply matrix by vector
Row operator*(const Matrix& l, const Row& r) {
	Row ret(sz(r));
	rep(i, 0, sz(l)) rep(k, 0, sz(r)) ret[i] += l[i][k] * r[k];
	return ret;
}

// Add matrices
Matrix& operator+=(Matrix& l, const Matrix& r){
	rep(i, 0, sz(l)) rep(k, 0, sz(l[0]))
		l[i][k] += r[i][k];
	return l;
}
Matrix operator+(Matrix l, const Matrix& r) {
	return l += r;
}

// Subtract matrices
Matrix& operator-=(Matrix& l, const Matrix& r){
	rep(i, 0, sz(l)) rep(k, 0, sz(l[0]))
		l[i][k] -= r[i][k];
	return l;
}
Matrix operator-(Matrix l, const Matrix& r) {
	return l -= r;
}

// Multiply matrices
Matrix operator*(const Matrix& l,
                 const Matrix& r) {
	Matrix ret(sz(l), Row(sz(r[0])));
	rep(i, 0, sz(l)) rep(j, 0, sz(r[0]))
		rep(k, 0, sz(r))
			ret[i][j] += l[i][k] * r[k][j];
	return ret;
}
Matrix& operator*=(Matrix& l, const Matrix& r){
	return l = l*r;
}

// Transpose matrix
Matrix transpose(const Matrix& m) {
	Matrix ret(sz(m[0]), Row(sz(m)));
	rep(i, 0, sz(m)) rep(j, 0, sz(m[0]))
		ret[j][i] = m[i][j];
	return ret;
}

bool isOrthogonal(const Matrix& M) {
	auto tmp = M * transpose(M);
	rep(i, 0, sz(tmp)) {
		rep(j, 0, sz(tmp)) {
			if (cmp(tmp[i][j], i == j)) {
				return 0;
			}
		}
	}
	return 1;
}

bool isZeroes(const Row& t, int d) {
	rep(i, d, sz(t)) if (cmp(t[i], 0)) return 0;
	return 1;
}

bool isSolution(const Matrix& M, const Row& x) {
	rep(i, 0, sz(M)) {
		double k = 0;
		rep(j, 0, sz(M[0])-1) k += M[i][j] * x[j];
		if (cmp(M[i].back(), k)) return 0;
	}
	return 1;
}

void check(const Matrix& A) {
	int m = sz(A[0])-1;
	// Row ans;
	// int expectedDim = gauss(A, ans, m);

	auto B = A;
	Matrix M;
	Row t;
	int dim = orthoGauss(B, M, t, m);

	// assert(expectedDim == dim);

	if (dim == -1) {
		return;
	}

	Matrix M2 = transpose(M);
	assert(isOrthogonal(M));
	// assert(isZeroes(M*ans + t, dim));

	rep(j, 0, 10) {
		vector<double> x(m);
		rep(i, 0, dim) x[i] = rf(-10, 10);
		assert(isSolution(A, M2*(x-t)));
	}

	deb(0);
}

Matrix randMatrix(int n, int m) {
	Matrix mat(n, Row(m));
	each(vec, mat) each(e, vec) e = double(r(-1, 1));
	return mat;
}

Matrix randMatrix2(int n, int m) {
	Matrix mat(n, Row(m));
	each(vec, mat) each(e, vec) e = rf(-1, 1);
	return mat;
}

int main() {
	while (true) {
		// check(randMatrix(5, 6));
		check(randMatrix2(500, 501));
		deb(1);
	}
	return 0;
}
