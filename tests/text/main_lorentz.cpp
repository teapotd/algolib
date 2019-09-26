#include "../../lib/text/main_lorentz.h"
#include "../testing.h"

// http://e-maxx.ru/algo/string_tandems

vector<pair<Pii, int>> inters;

vector<int> z_function (const string & s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}

void output_tandems (const string &, int shift, bool left, int cntr, int l, int k1, int k2) {
	int first = max(l-k2, 1);
	int last = min(left ? l-1 : l, k1);
	if (first > last) return;

	int firstPos = (left ? cntr-first : cntr-first-(l-first)-first+1) + shift;
	int lastPos = (left ? cntr-last : cntr-last-(l-last)-last+1) + shift;
	if (firstPos > lastPos) swap(firstPos, lastPos);

	inters.pb({ {firstPos, lastPos+1}, l });

	// for (int pos = firstPos; pos <= lastPos; pos++) {
	// 	cerr << "[" << pos << ".." << pos+2*l-1 << "] = " << s.substr (pos-shift, 2*l) << '\n';
	// }
}

inline int get_z (const vector<int> & z, int i) {
	return 0<=i && i<(int)z.size() ? z[i] : 0;
}

void find_tandems (string s, int shift = 0) {
	int n = (int) s.length();
	if (n == 1)  return;

	int nu = n/2,  nv = n-nu;
	string u = s.substr (0, nu),
		   v = s.substr (nu);
	string ru = string (u.rbegin(), u.rend()),
		   rv = string (v.rbegin(), v.rend());

	find_tandems (u, shift);
	find_tandems (v, shift + nu);

	vector<int> z1 = z_function (ru),
		z2 = z_function (v + '#' + u),
		z3 = z_function (ru + '#' + rv),
		z4 = z_function (v);
	for (int cntr=0; cntr<n; ++cntr) {
		int l, k1, k2;
		if (cntr < nu) {
			l = nu - cntr;
			k1 = get_z (z1, nu-cntr);
			k2 = get_z (z2, nv+1+cntr);
		}
		else {
			l = cntr - nu + 1;
			k1 = get_z (z3, nu+1 + nv-1-(cntr-nu));
			k2 = get_z (z4, (cntr-nu)+1);
		}
		if (k1 + k2 >= l)
			output_tandems (s, shift, cntr<nu, cntr, l, k1, k2);
	}
}

// ---

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	inters.clear();
	find_tandems(str);
	sort(all(inters));

	vector<pair<Pii, int>> our;
	each(p, lorentz(str)) our.pb({{p.begin, p.end}, p.len});
	sort(all(our));

	deb(inters);
	deb(our);
	assert(inters == our);
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
