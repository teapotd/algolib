#include "../template.h"
#include "../structures/find_union.h"

// Rectilinear Minimum Spanning Tree
// (MST in Manhattan metric); time: O(n lg n)
// Returns MST weight. Outputs spanning tree
// to G, vertex indices match point indices.
// Edge in G is pair (target, weight).
ll rmst(vector<Pii>& points,
        vector<vector<Pii>>& G) {
	int n = sz(points);
	vector<pair<int, Pii>> edges;
	vector<Pii> close;
	Vi ord(n), merged(n);
	iota(all(ord), 0);

	function<void(int,int)> octant =
			[&](int begin, int end) {
		if (begin+1 >= end) return;

		int mid = (begin+end) / 2;
		octant(begin, mid);
		octant(mid, end);

		int j = mid;
		Pii best = {INT_MAX, -1};
		merged.clear();

		rep(i, begin, mid) {
			int v = ord[i];
			Pii p = points[v];

			while (j < end) {
				int e = ord[j];
				Pii q = points[e];
				if (q.x-q.y > p.x-p.y) break;
				best = min(best,make_pair(q.x+q.y, e));
				merged.pb(e);
				j++;
			}

			if (best.y != -1) {
				int alt = best.x-p.x-p.y;
				if (alt < close[v].x)
					close[v] = {alt, best.y};
			}
			merged.pb(v);
		}

		while (j < end) merged.pb(ord[j++]);
		copy(all(merged), ord.begin()+begin);
	};

	rep(i, 0, 4) {
		rep(j, 0, 2) {
			sort(all(ord), [&](int l, int r) {
				return points[l] < points[r];
			});
			close.assign(n, {INT_MAX, -1});
			octant(0, n);
			rep(k, 0, n) {
				Pii p = close[k];
				if (p.y != -1) edges.pb({p.x,{k,p.y}});
				points[k].x *= -1;
			}
		}
		each(p, points) p = {p.y, -p.x};
	}

	ll sum = 0;
	FAU fau(n);
	sort(all(edges));
	G.assign(n, {});

	each(e, edges) if (fau.join(e.y.x, e.y.y)) {
		sum += e.x;
		G[e.y.x].pb({e.y.y, e.x});
		G[e.y.y].pb({e.y.x, e.x});
	}
	return sum;
}
