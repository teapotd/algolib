#pragma once
#include "../template.h"
#include "modular.h"

using Row = vector<Zp>;
using Matrix = vector<Row>;

// Create n x n identity matrix
Matrix ident(int n) {
	Matrix ret(n, Row(n));
	rep(i, 0, n) ret[i][i] = 1;
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

// Square matrix power; time: O(n^3 * lg e)
Matrix pow(Matrix a, ll e) {
	Matrix t = ident(sz(a));
	while (e) {
		if (e % 2) t *= a;
		e /= 2; a *= a;
	}
	return t;
}

// Transpose matrix
Matrix transpose(const Matrix& m) {
	Matrix ret(sz(m[0]), Row(sz(m)));
	rep(i, 0, sz(m)) rep(j, 0, sz(m[0]))
		ret[j][i] = m[i][j];
	return ret;
}

// Transform matrix to echelon form
// and compute its determinant sign and rank.
int echelon(Matrix& A, int& sign) { // O(n^3)
	int rank = 0;
	sign = 1;
	rep(c, 0, sz(A[0])) {
		if (rank >= sz(A)) break;
		rep(i, rank+1, sz(A)) if (A[i][c].x) {
			swap(A[i], A[rank]);
			sign *= -1;
			break;
		}
		if (A[rank][c].x) {
			rep(i, rank+1, sz(A)) {
				auto mult = A[i][c] / A[rank][c];
				rep(j, 0, sz(A[0]))
					A[i][j] -= A[rank][j]*mult;
			}
			rank++;
		}
	}
	return rank;
}

// Compute matrix rank; time: O(n^3)
#define rank rank_
int rank(Matrix A) {
	int s; return echelon(A, s);
}

// Compute square matrix determinant; O(n^3)
Zp det(Matrix A) {
	int s; echelon(A, s);
	Zp ret = s;
	rep(i, 0, sz(A)) ret *= A[i][i];
	return ret;
}

// Invert square matrix if possible; O(n^3)
// Returns true if matrix is invertible.
bool invert(Matrix& A) {
	int s, n = sz(A);
	rep(i, 0, n) A[i].resize(n*2), A[i][n+i] = 1;
	echelon(A, s);
	for (int i = n; i--;) {
		if (!A[i][i].x) return 0;
		auto mult = A[i][i].inv();
		each(k, A[i]) k *= mult;
		rep(k, 0, i) rep(j, 0, n)
			A[k][n+j] -= A[i][n+j]*A[k][i];
	}
	each(r, A) r.erase(r.begin(), r.begin()+n);
	return 1;
}
