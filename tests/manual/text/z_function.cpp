#include "../../../src/text/z_function.h"
#include "../testing.h"

Vi naivePrefPref(const string& str) {
	Vi ret(sz(str));

	rep(i, 0, sz(str)) {
		int k = 0;
		while (i+k < sz(str) && str[k] == str[i+k]) {
			k++;
		}
		ret[i] = k;
	}

	return ret;
}

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	Vi naive = naivePrefPref(str);
	Vi fast = prefPref(str);
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
