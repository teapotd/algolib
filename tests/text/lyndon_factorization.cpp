#include "../../src/text/lyndon_factorization.h"
#include "../testing.h"

bool isSimple(const string& str) {
	rep(i, 1, sz(str)) {
		if (str >= str.substr(i)) return 0;
	}
	return 1;
}

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	vector<string> fact = duval(str);
	deb(str, fact);

	string full;

	each(s, fact) {
		assert(isSimple(s));
		full += s;
	}

	rep(i, 1, sz(fact)) {
		assert(fact[i-1] >= fact[i]);
	}

	assert(full == str);
}

int main() {
	rep(alpha, 1, 10) rep(n, 1, 20) {
		deb(n, alpha);
		rep(i, 0, 100) {
			test(n, alpha);
		}
	}
	return 0;
}
