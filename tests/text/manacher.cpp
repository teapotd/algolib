#include "../../src/text/manacher.h"
#include "../testing.h"

Vi naiveManacher(const string& tmp) {
	string str;
	each(c, tmp) {
		str.pb(c);
		str.pb('#');
	}

	Vi ret(sz(str));

	rep(i, 0, sz(str)) {
		int k = 1;
		while (i+k < sz(str) && i-k >= 0 && str[i-k] == str[i+k]) {
			k++;
		}

		if (str[i-k+1] == '#') k--;
		ret[i] = k/2 + (i%2 == 0);
	}

	return ret;
}

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	Vi naive = naiveManacher(str);
	Vi fast = manacher(str);
	deb(naive, fast);
	assert(naive == fast);
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
