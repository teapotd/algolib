#include "../../lib/text/suffix_array.h"
#include "../testing.h"

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	Vi sufs = sufArray(str);

	rep(i, 1, sz(sufs)) {
		assert(strcmp(&str[sufs[i-1]], &str[sufs[i]]) < 0);
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
