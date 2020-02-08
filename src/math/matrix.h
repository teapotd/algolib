#pragma once
#include "../template.h"
#include "modular.h"

// UNTESTED
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
	rep(i, 0, sz(l)) rep(k, 0, sz(l[i]))
		l[i][k] += r[i][k];
	return l;
}
Matrix operator+(Matrix l, const Matrix& r) {
	return l += r;
}

// Subtract matrices
Matrix& operator-=(Matrix& l, const Matrix& r){
	rep(i, 0, sz(l)) rep(k, 0, sz(l[i]))
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

// Raise square matrix to given power
Matrix pow(Matrix a, ll e) {
	Matrix t = ident(sz(a));
	while (e) {
		if (e % 2) t *= a;
		e /= 2; a *= a;
	}
	return t;
}
