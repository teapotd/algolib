#define FLOATING_POINT_GEOMETRY 0
#include "../../../src/geo2d/rmst.h"
#include "common.hpp"

vec::T naiveRMST(const vector<vec>& points) {
	vector<pair<vec::T, pii>> edges;
	rep(i, 0, sz(points)) {
		rep(j, i+1, sz(points)) {
			auto p = points[i] - points[j];
			edges.pb({ abs(p.x)+abs(p.y), {i, j} });
		}
	}

	FAU dsu(sz(points));
	vec::T ret = 0;
	sort(all(edges));

	for (auto [w, e] : edges) {
		if (dsu.join(e.x, e.y)) {
			ret += w;
		}
	}
	return ret;
}

void check(const vector<vec>& points) {
	vector<pair<ll, pii>> edges;
	auto fast = rmst(points, edges);
	auto naive = naiveRMST(points);

	assert(equalWithEps(fast, naive));

	if (points.empty()) {
		assert(edges.empty());
		return;
	}

	assert(sz(edges) == sz(points)-1);

	FAU dsu(sz(points));
	ll weightSum = 0;

	for (auto [w, e] : edges) {
		assert(dsu.join(e.x, e.y));
		weightSum += w;
	}

	assert(equalWithEps(weightSum, naive));
}

void deterministic() {
	constexpr vec::T big = 1e9;
	check({});
	check({{5,6}});
	check({{-big,-big}, {big,big}});
	check({{-big,-big}, {-big,big}, {big,-big}, {big,big}});
}

void fuzz() {
	rep(i, 0, 50'000) {
		int n = randInt(2, 30);
		auto mx = randCoord(1*U, 100*U);
		auto points = randVecsFromSquare(n, -mx, mx);
		check(points);
	}
}

void benchmark() {
	auto points = randVecsFromSquare(1e6, -1e9, 1e9);

	measure("rmst N=1e6", 5, [&] {
		vector<pair<ll, pii>> edges;
		auto weight = rmst(points, edges);
		consume(&edges);
		consume(weight);
	});
}
