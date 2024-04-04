#pragma once
#include "../template.h"
#include "vector.h"

using Triple = array<int, 3>;
mt19937 rnd(123);

// 3D convex hull; time and memory: O(n log n)
// Returns list of hull faces with vertices
// in CCW order when "looking from outside".
// Doesn't work if all points are coplanar!
// Depends on vec3: -, dot, cross, len2
//! Source: https://codeforces.com/blog/entry/81768
vector<Triple> convexHull(vector<vec3>& in) {
	int n = sz(in), g = 1;
	vector<Triple> ret, fv, fe;
	vector<vi> fb, bad(n);
	vector<vec3> fq, p(n);
	vi dead, ord(n), link(n, -1);

	iota(all(ord), 0);
	shuffle(all(ord), rnd);
	rep(i, 0, n) p[i] = in[ord[i]];

	// Only needed if there are 4 coplanar points
	vec3 a = p[0], b, c;
	rep(i, 1, n) if (g < 4) {
		swap(p[g], p[i]); swap(ord[g], ord[i]);
		if (g == 1)
			g += sgn((b = p[1]-a).len2());
		else if (g == 2)
			g += sgn((c = b.cross(p[2]-a)).len2());
		else
			g += !!sgn(c.dot(p[3]-a));
	}
	assert(g == 4); // Not everything coplanar

	auto add = [&](int i, int j, int k) {
		fv.pb({i, j, k});
		fe.pb({-1, -1, -1});
		fq.pb((p[j]-p[i]).cross(p[k]-p[i]));
		fb.pb({});
		dead.pb(1e9);
		return sz(fv)-1;
	};

	rep(i, 0, 2) {
		fe[add(0, i+1, 2-i)] = {!i, !i, !i};
		rep(j, 3, n) {
			sc t = fq[i].dot(p[j]-p[0]);
			if (t >= -eps) {
				fb[i].pb(j);
				if (t > eps) bad[j].pb(i);
			}
		}
	}

	rep(i, 3, n) {
		int v = -1;
		each(f, bad[i]) dead[f] = min(dead[f], i);
		each(f, bad[i]) if (dead[f] == i) {
			rep(j, 0, 3) if (dead[fe[f][j]] > i) {
				int u = fv[f][(j+1)%3], e = fe[f][j];
				v = fv[f][j];
				fe[g = link[v] = add(v, u, i)][0] = e;
				set_union(all(fb[f]), all(fb[e]),
					back_inserter(fb[g]));
				erase_if(fb[g], [&](int k) {
					return k <= i ||
						fq[g].dot(p[k]-p[fv[g][0]]) <= eps;
				});
				each(k, fb[g]) bad[k].pb(g);
				rep(k, 0, 3) if (fv[e][k] == u) {
					fe[e][k] = g;
					break;
				}
			}
			vi().swap(fb[f]);
		}
		while (v != -1 && fe[link[v]][1] == -1) {
			int u = fv[link[v]][1];
			fe[link[v]][1] = link[u];
			fe[link[u]][2] = link[v];
			v = u;
		}
		vi().swap(bad[i]);
	}

	rep(i, 0, sz(fv)) if (dead[i] >= n) {
		each(j, fv[i]) j = ord[j];
		ret.pb(fv[i]);
	}
	return ret;
}
