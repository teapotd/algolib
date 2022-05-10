#include "../../../src/text/kmr.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	Vi sufs = KMR(s).sufArray();
	each(k, sufs) cout << k << ' ';
	cout << '\n';
	return 0;
}
