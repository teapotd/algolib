#include "../../../src/text/alcs.h"
#include "../testing.h"

vector<vi> lcs(const string& A, const string& B) {
	vector<vi> ret(sz(A)+1, vi(sz(B)+1));
	rep(i, 0, sz(A)) rep(j, 0, sz(B)) {
		if (A[i] == B[j]) {
			ret[i+1][j+1] = ret[i][j] + 1;
		} else {
			ret[i+1][j+1] = max(ret[i+1][j], ret[i][j+1]);
		}
	}
	return ret;
}

vector<vector<vi>> naiveAlcs(const string& A, const string& B) {
	vector<vector<vi>> ret(sz(A)+1, vector<vi>(sz(B)+1, vi(sz(B)+1)));
	rep(j, 0, sz(B)+1) {
		auto tmp = lcs(A, B.substr(j));
		rep(i, 0, sz(A)+1) rep(k, j, sz(B)+1) {
			ret[i][j][k] = tmp[i][k-j];
		}
	}
	return ret;
}

bool isSubseq(const string& str, const string& sub) {
	int i = 0;
	each(c, sub) {
		while (i < sz(str) && str[i] != c) i++;
		if (i >= sz(str)) return 0;
		i++;
	}
	return 1;
}

void test(int n, int m, int alpha) {
	string A, B;
	rep(i, 0, n) A.pb(char('a' + r(0, alpha-1)));
	rep(i, 0, m) B.pb(char('a' + r(0, alpha-1)));

	ALCS alcs(A, B);
	auto naive = naiveAlcs(A, B);

	rep(i, 0, sz(A)+1) {
		auto fast = alcs.matrix(i);
		assert(fast == naive[i]);

		rep(j, 0, sz(B)+1) rep(k, 0, sz(B)+1) {
			assert(fast[j][k] == alcs(i, j, k));
			string seq = alcs.recover(i, j, k);
			assert(sz(seq) == fast[j][k]);
			assert(isSubseq(A.substr(0, i), seq));
			assert(isSubseq(B.substr(j, k-j), seq));
		}
	}
}

int main() {
	rep(alpha, 1, 10) rep(n, 1, 20) rep(m, 1, 20) {
		deb(n, m, alpha);
		rep(i, 0, 10) {
			test(n, m, alpha);
		}
	}
	for (int i = 0;; i++) {
		int alpha = r(2, 4);
		int n = r(1, 50);
		int m = r(1, 50);
		test(n, m, alpha);
		if (i%1000 == 0) deb(i);
	}
	return 0;
}
