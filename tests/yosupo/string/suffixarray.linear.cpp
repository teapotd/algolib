#include "../../../src/text/suffix_array_linear.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	Vi sufs = sufArray(s);
	each(k, sufs) cout << k << ' ';
	cout << '\n';
	return 0;
}
