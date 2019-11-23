#pragma once
#include "../template.h"
#include "vec2.h"
#include "line2.h"

// Intersect given halfplanes and output
// hull vertices to out.
// Returns 0 if intersection is empty,
// 1 if intersection is non-empty and bounded,
// 2 if intersection is unbounded.
// Vertices ARE ONLY computed if intersection
// is non-empty and bounded.
// Works only with floating point vec2/line2.
// UNTESTED
int intersectHalfPlanes(vector<line2> lines,
                        vector<vec2>& out) {
	deque<line2> H;
	out.clear();
	if (lines.empty()) return 2;

	sort(all(lines), [](line2 a, line2 b) {
		int t = cmp(a.norm.angle(),b.norm.angle());
		return t ? t < 0 : cmp(a.off*b.norm.len(),
			b.off*a.norm.len()) < 0;
	});

	auto bad = [](line2 a, line2 b, line2 c) {
		if (cmp(a.norm.cross(c.norm), 0) <= 0)
			return false;
		vec2 p; assert(a.intersect(c, p));
		return b.side(p) <= 0;
	};

	each(e, lines) {
		if (!H.empty() &&
			!cmp(H.back().norm.angle(),
			e.norm.angle())) continue;
		while (sz(H) > 1 && bad(H[sz(H)-2],
			H.back(), e)) H.pop_back();
		while (sz(H) > 1 && bad(e, H[0], H[1]))
			H.pop_front();
		H.pb(e);
	}

	while (sz(H) > 2 && bad(H[sz(H)-2],
		H.back(), H[0])) H.pop_back();
	while (sz(H) > 2 && bad(H.back(),
		H[0], H[1])) H.pop_back();

	out.resize(sz(H));
	deb(H);

	rep(i, 0, sz(H)) {
		auto a = H[i], b = H[(i+1)%sz(H)];
		if (a.norm.cross(b.norm) < 0) return 2;
		assert(a.intersect(b, out[i]));
	}

	rep(i, 0, sz(H)) {
		auto a = out[i], b = out[(i+1)%sz(H)];
		if (H[i].norm.perp().cross(b-a) <= 0) return 0;
	}
	return 1;
}
