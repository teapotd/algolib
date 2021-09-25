#pragma once
#include "../template.h"

// Bipartite edge coloring; time: O(nm)
// `edges` is list of (left vert, right vert),
// where vertices on both sides are indexed
// from 0 to n-1. Returns number of used colors
// (which is equal to max degree).
// col[i] = color of i-th edge [0..max_deg-1]
//! Source: https://github.com/koosaga/olympiad/blob/master/Library/codes/graph_etc/edgecolor_bipartite.cpp
int colorEdges(vector<Pii>& edges,
               int n, Vi& col) {
	int m = sz(edges), c[2] = {}, ans = 0;
	Vi deg[2];
	vector<vector<Pii>> has[2];
	col.assign(m, 0);
	rep(i, 0, 2) {
		deg[i].resize(n+1);
		has[i].resize(n+1, vector<Pii>(n+1));
	}

	function<void(int,int)> dfs =
		[&](int x, int p) {
			Pii i = has[p][x][c[!p]];
			if (has[!p][i.x][c[p]].y) dfs(i.x, !p);
			else has[!p][i.x][c[!p]] = {};
			has[p][x][c[p]] = i;
			has[!p][i.x][c[p]] = {x, i.y};
			if (i.y) col[i.y-1] = c[p]-1;
		};

	rep(i, 0, m) {
		int x[2] = {edges[i].x+1, edges[i].y+1};
		rep(d, 0, 2) {
			deg[d][x[d]]++;
			ans = max(ans, deg[d][x[d]]);
			for (c[d] = 1; has[d][x[d]][c[d]].y;)
				c[d]++;
		}
		if (c[0]-c[1]) dfs(x[1], 1);
		rep(d, 0, 2)
			has[d][x[d]][c[0]] = {x[!d], i+1};
		col[i] = c[0]-1;
	}
	return ans;
}
