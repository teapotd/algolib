#include "../../../src/text/manacher.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	vi radius = manacher(s);
	rep(i, 0, sz(s)*2-1) {
		int len = radius[i]*2 - (i%2 ? 0 : 1);
		cout << len << ' ';
	}
	cout << '\n';
	return 0;
}
