#include "../template.h"
#include "vector.h"
#include "../structures/find_union.h"

// Rectilinear Minimum Spanning Tree
// (MST in Manhattan metric); time: O(n lg n)
// Returns MST weight. The spanning tree edges
// are saved in `out` as triples (dist, (u,v)).
// Depends on vec: -
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ManhattanMST.h
ll rmst(vector<vec> points,
        vector<pair<ll, pii>>& edges) {
	vector<pair<ll, pii>> span;
	vi id(sz(points));
	iota(all(id), 0);

	rep(k, 0, 4) {
		map<ll, ll> S;
		sort(all(id), [&](int i, int j) {
			return (points[i]-points[j]).x <
			       (points[j]-points[i]).y;
		});
		each(i, id) {
			auto it = S.lower_bound(-points[i].y);
			for (; it != S.end(); S.erase(it++)) {
				vec d = points[i] - points[it->y];
				if (d.y > d.x) break;
				span.push_back({d.x+d.y, {i, it->y}});
			}
			S[-points[i].y] = i;
		}
		each(p, points) {
			if (k % 2) p.x = -p.x;
			else swap(p.x, p.y);
		}
	}

	FAU fau(sz(id));
	ll sum = 0;
	sort(all(span));
	edges.clear();
	each(e, span) if (fau.join(e.y.x, e.y.y))
		edges.pb(e), sum += e.x;
	return sum;
}
