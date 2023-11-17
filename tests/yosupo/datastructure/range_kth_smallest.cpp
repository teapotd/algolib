#include "../../../src/structures/wavelet_tree.h"
#include "../../../src/util/compress_vec.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	vi seq(n);
	vector<int*> tmp;

	each(p, seq) {
		cin >> p;
		tmp.pb(&p);
	}

	vi vals = compressVec(tmp);
	WaveletTree tree(seq, sz(vals));

	while (q--) {
		int b, e, k;
		cin >> b >> e >> k;
		cout << vals[tree.kth(b, e, k)] << '\n';
	}

	return 0;
}
