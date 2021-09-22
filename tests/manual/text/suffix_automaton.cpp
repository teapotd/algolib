#include "../../../src/text/suffix_automaton.h"
#include "../testing.h"

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	SufDFA dfa(str);

	rep(i, 0, n) {
		int v = 0;
		rep(j, i, n) {
			v = dfa.to[v][str[j]-'a'];
			assert(v != 0);
		}
	}
}

int main() {
	rep(alpha, 1, 10) rep(n, 1, 20) {
		deb(n, alpha);
		rep(i, 0, 10) {
			test(n, alpha);
		}
	}
	return 0;
}
