#include "../../../src/text/monge.h"
#include "../testing.h"

vector<Vi> permToMongeMatrix(const Vi& perm) {
	int n = sz(perm);
	vector<Vi> mat(n+1, Vi(n+1));
	for (int i = n-1; i >= 0; i--) {
		for (int j = 1; j <= n; j++) {
			mat[i][j] = mat[i+1][j] + mat[i][j-1] - mat[i+1][j-1] + (perm[i] == j-1);
		}
	}
	return mat;
}

Vi mongeMatrixToPerm(const vector<Vi>& mat) {
	int n = sz(mat)-1;
	Vi perm(n);
	rep(i, 0, n) rep(j, 1, n+1) {
		int p = mat[i][j] - (mat[i+1][j] + mat[i][j-1] - mat[i+1][j-1]);
		if (p) perm[i] = j-1;
	}
	return perm;
}

vector<Vi> distanceMul(const vector<Vi>& A, const vector<Vi>& B) {
	vector<Vi> C(sz(A), Vi(sz(B[0])));
	rep(i, 0, sz(A)) rep(j, 0, sz(B[0])) {
		C[i][j] = INT_MAX;
		rep(k, 0, sz(A[0])) {
			C[i][j] = min(C[i][j], A[i][k]+B[k][j]);
		}
	}
	return C;
}

Vi mongeMulNaive(const Vi& P, const Vi& Q) {
	auto A = permToMongeMatrix(P);
	auto B = permToMongeMatrix(Q);
	auto C = distanceMul(A, B);
	return mongeMatrixToPerm(C);
}

void testMongeMul(const Vi& P, const Vi& Q) {
	Vi expected = mongeMulNaive(P, Q);
	Vi got = mongeMul(P, Q, sz(P));
	if (got != expected) {
		deb(P);
		deb(Q);
		deb(expected);
		deb(got);
		assert(0);
	}
}

void testMongeMulAll(int n) {
	Vi P(n);
	iota(all(P), 0);
	do {
		Vi Q(n);
		iota(all(Q), 0);
		do {
			testMongeMul(P, Q);
		} while (next_permutation(all(Q)));
	} while (next_permutation(all(P)));
}

int main() {
	constexpr int MAX_LENGTH_ALL = 6;
	constexpr int MAX_LENGTH_RAND = 100;

	rep(n, 0, MAX_LENGTH_ALL+1) {
		deb(n);
		testMongeMulAll(n);
	}

	for (int cnt = 1;; cnt++) {
		int n = r(MAX_LENGTH_ALL+1, MAX_LENGTH_RAND);
		Vi P(n), Q(n);
		iota(all(P), 0);
		iota(all(Q), 0);
		shuffle(all(P), rnd);
		shuffle(all(Q), rnd);
		testMongeMul(P, Q);
		if (cnt%1000 == 0) {
			deb(cnt);
		}
	}

	return 0;
}
