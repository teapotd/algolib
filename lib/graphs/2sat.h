#pragma once
#include "../template.h"

// 2-SAT solver; time: O(n+m), space: O(n+m)
// Variables are indexed from 1!
// Pass negative indices to represent negations
// (internally: positive = i*2-1, neg. = i*2-2)
struct SAT2 {
	vector<Vi> G;
	Vi order, values; // Also indexed from 1!
	vector<bool> flags;

	// Init n variables, you can add more later
	SAT2(int n = 0)  { init(n); }
	void init(int n) { G.resize(n*2); }

	// Solve and save assignments in `values`
	bool solve() { // O(n+m), Kosaraju is used
		values.assign(sz(G)/2+1, -1);
		flags.assign(sz(G), 0);
		rep(i, 0, sz(G)) dfs(i);
		while (!order.empty()) {
			if (!propag(order.back()^1, 1)) return 0;
			order.pop_back();
		}
		return 1;
	}

	void dfs(int i) {
		if (flags[i]) return;
		flags[i] = 1;
		each(e, G[i]) dfs(e);
		order.pb(i);
	}

	bool propag(int i, bool first) {
		if (!flags[i]) return 1;
		flags[i] = 0;
		if (values[i/2+1] >= 0) return first;
		values[i/2+1] = i&1;
		each(e, G[i]) if (!propag(e, 0)) return 0;
		return 1;
	}

	void imply(int i, int j) { // i => j
		i = max(i*2-1, -i*2-2);
		j = max(j*2-1, -j*2-2);
		G[i].pb(j);
		G[j^1].pb(i^1);
	}

	void or_(int i, int j) { imply(-i, j); }

	int addVar() { //Add new var and return index
		G.resize(sz(G)+2); return sz(G)/2;
	}

	void atMostOne(Vi& vars) {
		int x = addVar();
		each(i, vars) {
			int y = addVar();
			imply(x, y);
			imply(i, -x);
			imply(i, y);
			x = y;
		}
	}
};
