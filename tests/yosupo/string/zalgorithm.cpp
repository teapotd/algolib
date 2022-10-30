#include "../../../src/text/z_function.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	vi z = prefPref(s);
	each(a, z) cout << a << ' ';
	cout << '\n';
	return 0;
}
