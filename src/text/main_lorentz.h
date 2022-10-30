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
	vector<Sqr> ans;
	vi pos(sz(s)/2+2, -1);

	rep(mid, 1, sz(s)) {
		int part = mid & ~(mid-1), off = mid-part;
		int end = min(mid+part, sz(s));
		auto a = s.substr(off, part);
		auto b = s.substr(mid, end-mid);

		string ra(a.rbegin(), a.rend());
		string rb(b.rbegin(), b.rend());

		rep(j, 0, 2) {
			// Set # to some unused character!
			vi z1 = prefPref(ra);
			vi z2 = prefPref(b+"#"+a);
			z1.pb(0); z2.pb(0);

			rep(c, 0, sz(a)) {
				int l = sz(a)-c;
				int x = c - min(l-1, z1[l]);
				int y = c - max(l-z2[sz(b)+c+1], j);
				if (x > y) continue;

				int sb = (j ? end-y-l*2 : off+x);
				int se = (j ? end-x-l*2+1 : off+y+1);
				int& p = pos[l];

				if (p != -1 && ans[p].end == sb)
					ans[p].end = se;
				else
					p = sz(ans), ans.pb({sb, se, l});
			}

			a.swap(rb);
			b.swap(ra);
		}
	}

	return ans;
}
