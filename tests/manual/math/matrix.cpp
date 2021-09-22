#include "../../../src/math/matrix.h"
#include "../testing.h"

void checkInv(const Matrix& mat) {
	Matrix inv = mat;
	bool invertible = invert(inv);
	deb(mat, invertible);

	if (invertible) {
		deb(inv);
		deb(mat*inv);
	}
}

bool isIdent(const Matrix& mat) {
	int n = sz(mat);
	rep(i, 0, n) {
		if (sz(mat[i]) != n) return 0;
		rep(j, 0, n) if (mat[i][j].x != (i == j)) return 0;
	}
	return 1;
}

int main() {
	Matrix a = {
		{1,2,3},
		{3,4,5},
	};

	Matrix b = {
		{5,10,0},
		{100,200,300},
	};

	Matrix c = {
		{5,10,0},
		{100,200,300},
		{0,0,0},
	};

	Matrix d = {
		{5,10,0},
		{100,200,300},
		{0,0,0},
		{200,300,400},
	};


	Matrix e = {
		{-5,-10,0},
		{100,200,300},
		{1,3,5},
	};

	deb(a);
	deb(b);
	deb(c);
	deb(a+b);
	deb(a*c);
	deb(pow(c, 0));
	deb(pow(c, 3));
	deb(transpose(a));
	deb(transpose(c));

	cerr << endl;
	deb(rank(a), rank(b), rank(c), rank(d), rank(e));
	deb(det(c), det(e));

	cerr << endl;
	checkInv(c);
	checkInv(e);

	cerr << endl;

	rep(t, 0, 10000) {
		int n = r(5, 20);
		Matrix mat(n, Row(n));
		rep(i, 0, n) rep(j, 0, n) mat[i][j] = r(0, MOD-1);

		Matrix inv = mat;
		assert(invert(inv));
		assert(isIdent(mat*inv));
	}

	return 0;
}
