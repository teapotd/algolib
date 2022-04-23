#include "../../../src/text/alcs.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int q;
	string s, t;
	cin >> q >> s >> t;

	ALCS alcs(s, t);

	while (q--) {
		int a, b, c;
		cin >> a >> b >> c;
		cout << alcs(a, b, c) << '\n';
	}
	return 0;
}
