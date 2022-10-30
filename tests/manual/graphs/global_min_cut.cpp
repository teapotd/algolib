#include "../../../src/graphs/global_min_cut.h"
#include "../../../src/graphs/gomory_hu.h"
#include "../testing.h"

void check(const vector<vector<ll>>& mat) {
	int n = sz(mat);
	vi cut;
	ll val = minCut(mat, cut);

	vector<bool> side(n);
	each(e, cut) side[e] = 1;
	ll actualVal = 0;
	rep(i, 0, n) rep(j, i+1, n) if (side[i] != side[j]) actualVal += mat[i][j];

	assert(val == actualVal);

	ll optVal = INT64_MAX;
	vector<Edge> edges;
	rep(i, 0, n) rep(j, i+1, n) edges.pb({i, j, int(mat[i][j])});
	each(e, gomoryHu(edges, n)) optVal = min(optVal, ll(e.w));

	assert(val == optVal);
}

int main() {
	rep(t, 0, 10) {
		int n = r(2, 100);
		vector<vector<ll>> mat(n, vector<ll>(n));
		rep(i, 0, n) rep(j, i+1, n) mat[i][j] = mat[j][i] = r(0, 100);
		check(mat);
	}
	return 0;
}
