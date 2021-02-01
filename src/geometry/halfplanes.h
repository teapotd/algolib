#pragma once
#include "../template.h"
#include "vec2.h"
#include "line2.h"

// Intersect halfplanes given by `lines`
// and output hull vertices to `out`
// in counter-clockwise order. Returns true
// if intersection is non-empty and bounded.
// Unbounded cases are not supported,
// add bounding-box if necessary. Works only
// with floating point vec2/line2; O(n lg n)
// PARTIALLY TESTED
//! Source: https://github.com/koosaga/DeobureoMinkyuParty/blob/e4778e32145a4410e866f0059790417dcbc83d98/teamnote.tex#L1725-L1767
//! Source: https://github.com/kth-competitive-programming/kactl/pull/90/files
bool intersectHalfplanes(vector<line2> in,
                         vector<vec2>& out) {
	sort(all(in), [](line2 a, line2 b) {
		return (a.v.angleCmp(b.v) ?:
		        a.c*b.v.len() - b.c*a.v.len()) < 0;
	});

	int a = 0, b = 0, n = sz(in);
	vector<line2> dq(n+5);
	out.resize(n+5);
	dq[0] = in[0];

	rep(i, 1, n+1) {
		if (i == n) in.pb(dq[a]);
		if (!in[i].v.angleCmp(in[i-1].v)) continue;
		while (a < b && in[i].side(out[b-1]) > 0)
			b--;
		while (i!=n && a<b && in[i].side(out[a])>0)
			a++;
		if (in[i].intersect(dq[b], out[b]))
			dq[++b] = in[i];
	}

	out.resize(b);
	out.erase(out.begin(), out.begin()+a);
	return b-a > 2;
}
