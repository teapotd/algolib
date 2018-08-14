#include "../template.h"
#include "../structures/find_union.h"

// Rectilinear Minimum Spanning Tree
// (MST in Manhattan metric); time: O(n lg n)
// Set `point` for each vertex and run rmst().
// Algorithm will compute RMST edges and save
// them in E for each vertex.

struct Edge {
	int dst, len;
};

struct Vert {
	Pii point, close;
	vector<Edge> E;
};

vector<Vert> G;
Vi merged;

void octant(Vi& S, int begin, int end) {
	if (begin+1 >= end) return;

	int mid = (begin+end) / 2;
	octant(S, begin, mid);
	octant(S, mid, end);

	merged.clear();
	merged.reserve(sz(S));
	int j = mid;
	Pii best = { INT_MAX, -1 };

	rep(i, begin, mid) {
		int v = S[i];
		Pii p = G[v].point;

		while (j < end) {
			int e = S[j];
			Pii q = G[e].point;
			if (q.x-q.y > p.x-p.y) break;
			int alt = q.x+q.y;
			if (alt < best.x) best = {alt, e};
			merged.pb(e);
			j++;
		}

		if (best.y != -1) {
			int alt = best.x-p.x-p.y;
			if (alt < G[v].close.x)
				G[v].close = {alt, best.y};
		}
		merged.pb(v);
	}

	while (j < end) merged.pb(S[j++]);
	copy(all(merged), S.begin()+begin);
}

ll rmst() {
	vector<pair<int, Pii>> edges;
	Vi sorted(sz(G));
	iota(all(sorted), 0);

	rep(i, 0, 4) {
		rep(j, 0, 2) {
			sort(all(sorted), [](int l, int r) {
				return G[l].point < G[r].point;
			});

			each(v, G) v.close = { INT_MAX, -1 };
			octant(sorted, 0, sz(sorted));

			rep(k, 0, sz(G)) {
				auto p = G[k].close;
				if (p.y != -1)
					edges.pb({ p.x, {k, p.y} });
				G[k].point.x *= -1;
			}
		}
		each(v,G) v.point = {v.point.y,-v.point.x};
	}

	ll sum = 0;
	FAU fau(sz(G));
	sort(all(edges));

	each(e, edges) if (fau.join(e.y.x, e.y.y)) {
		sum += e.x;
		G[e.y.x].E.pb({e.y.y, e.x});
		G[e.y.y].E.pb({e.y.x, e.x});
	}
	return sum;
}
