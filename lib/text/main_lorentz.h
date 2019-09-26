#pragma once
#include "../template.h"
#include "z_function.h"

struct Sqr {
	int begin, end, len;
};

// Main-Lorentz algorithm for finding
// all squares in given word; time: O(n lg n)
// Results are in compressed form:
// (b, e, l) means that for each b <= i < e
// there is square at position i of size 2l.
// Each square is present in only one interval.
vector<Sqr> lorentz(const string& s) {
	int n = sz(s);
	if (n <= 1) return {};
	auto a = s.substr(0, n/2), b = s.substr(n/2);

	auto ans = lorentz(a);
	each(p, lorentz(b))
		ans.pb({p.begin+n/2, p.end+n/2, p.len});

	string ra(a.rbegin(), a.rend());
	string rb(b.rbegin(), b.rend());

	rep(j, 0, 2) {
		Vi z1 = prefPref(ra), z2 = prefPref(b+a);
		z1.pb(0); z2.pb(0);

		rep(c, 0, sz(a)) {
			int l = sz(a)-c;
			int x = c - min(l-1, z1[l]);
			int y = c - max(l-z2[sz(b)+c], j);
			if (x > y) continue;

			if (j)
				ans.pb({n-y-l*2, n-x-l*2+1, l});
			else
				ans.pb({x, y+1, l});
		}

		a.swap(rb);
		b.swap(ra);
	}

	return ans;
}
