#include "../../../src/text/manacher.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	auto radius = manacher(s);
	rep(i, 1, sz(s)*2) {
		int len = radius[i%2][i/2]*2 + i%2;
		cout << len << ' ';
	}
	cout << '\n';
	return 0;
}
