#pragma once
#include "../template.h"
#include "vector.h" // FLOATING_POINT_GEOMETRY
#include "line.h"

// Halfplane intersection; time: O(n lg n)
// Behaviour is undefined if intersection
// is unbounded, add bounding-box if necessary!
// Returns:
// - vertices of intersection area in CCW order
//   starting from bottom-leftmost vertex;
// - empty vector if intersection is empty.
// Degenerate cases are supported.
// Works only with floating-point geometry.
// Depends on vec: -, *, /, dot, cross, len,
//                 perp, ==, upper, cmpAngle
// Depends on line: side, intersect
//! Source: https://github.com/koosaga/DeobureoMinkyuParty/blob/e4778e32145a4410e866f0059790417dcbc83d98/teamnote.tex#L1725-L1767
//! Source: https://github.com/kth-competitive-programming/kactl/pull/90/files
vector<vec> intersectHalfs(vector<line> in) {
	sort(all(in), [](line a, line b) {
		return (a.v.perp().cmpAngle(b.v.perp()) ?:
		        a.c*b.v.len() - b.c*a.v.len()) < 0;
	});

	int a = 1, b = 1, k = 0, n = sz(in);
	vector<line> dq(n+2);
	vector<vec> out(n+1);
	dq[1] = in[0];

	rep(i, 1, n+1) {
		line t = (i < n ? in[i] : dq[a]);
		while (a < b && t.side(out[b-1]) > 0) b--;
		while (a < b && t.side(out[a]) > 0) a++;
		if (t.intersect(dq[b], out[b])) dq[++b]=t;
	}

	out[0] = out[--b];
	rep(i, a, b)
		if (out[i] != out[0] && out[i] != out[k])
			out[++k] = out[i];
	out.resize(k+1);
	each(t, in) if (t.side(out[0]) > 0) return{};
	return out;
}
