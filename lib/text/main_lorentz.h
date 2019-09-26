#pragma once
#include "../template.h"
#include "z_function.h"

struct Sqr {
	int begin, end, len;
};

// Main-Lorentz algorithm for finding
// all squares in given word; time: O(n lg n)
// Results are in compressed form:
// (l, r, s) means that for each l <= i < r
// there is square at position i of size 2s
// UNFINISHED
vector<Sqr> lorentz(const string& s) {
	if (sz(s) <= 1) return {};
	auto a = s.substr(0, sz(s)/2);
	auto b = s.substr(sz(a));

	auto ans = lorentz(a);
	each(p, lorentz(b))
		ans.pb({p.begin+sz(a),p.end+sz(a),p.len});

	string ra(a.rbegin(), a.rend());
	string rb(b.rbegin(), b.rend());

	rep(i, 0, 2) {
		Vi z1 = prefPref(ra), z2 = prefPref(b+"#"+a);
		z1.pb(0); z2.pb(0);

		rep(c, 0, sz(a)) {
			int l = sz(a)-c;
			int k1 = z1[sz(a)-c], k2 = z2[sz(b)+c+1];
			if (k1+k2 < l) continue;

			int first = c - min(l-1, k1);
			int last = c - max(l-k2, 1-i);
			if (first > last) continue;

			if (i) {
				ans.pb({sz(s)-last-l*2, sz(s)-first-l*2+1, l});
			} else {
				ans.pb({first, last+1, l});
			}
		}

		a.swap(rb);
		b.swap(ra);
	}

	return ans;
}
