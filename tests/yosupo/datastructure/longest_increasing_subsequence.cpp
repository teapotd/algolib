#include "../../../src/util/longest_inc_subseq.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;

	vi seq(n);
	each(p, seq) cin >> p;

	vi ans = lis(seq);
	cout << sz(ans) << '\n';
	each(i, ans) cout << i << ' ';
	cout << '\n';

	return 0;
}
