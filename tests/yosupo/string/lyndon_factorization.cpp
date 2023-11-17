#include "../../../src/text/lyndon_factorization.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	int cur = 0;
	each(t, duval(s)) {
		cout << cur << ' ';
		cur += sz(t);
	}
	cout << cur;
	return 0;
}
