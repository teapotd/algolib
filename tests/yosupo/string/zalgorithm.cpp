#include "../../../src/text/z_function.h"

int main() {
	string s; cin >> s;
	Vi z = prefPref(s);
	each(a, z) cout << a << ' ';
	cout << '\n';
	return 0;
}
