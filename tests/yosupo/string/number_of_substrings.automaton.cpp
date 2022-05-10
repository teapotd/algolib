#include "../../../src/text/suffix_automaton.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	ll ans = SufDFA(s).paths[0] - 1;
	cout << ans << '\n';
	return 0;
}
