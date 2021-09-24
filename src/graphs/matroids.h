#pragma once
#include "../template.h"

// Find largest subset S of [n] such that
// S is independent in both matroid A and B.
// A and B are given by their oracles,
// see example implementations below.
// Returns vector V such that V[i] = 1 iff
// i-th element is included in found set;
// time: O(r^2*init + r^2*n*add),
// where r is max independent set,
// `init` is max time of oracles init
// and `add` is max time of oracles canAdd.
template<class T, class U>
vector<bool> intersectMatroids(T& A, U& B,
	                             int n) {
	vector<bool> ans(n);
	bool ok = 1;

	// NOTE: for weighted matroid intersection
	// find shortest augmenting paths
	// first by weight change, then by length
	// using Bellman-Ford, and skip this speedup:
	A.init(ans);
	B.init(ans);
	rep(i, 0, n) if (A.canAdd(i) && B.canAdd(i))
		ans[i] = 1, A.init(ans), B.init(ans);

	while (ok) {
		vector<Vi> G(n);
		vector<bool> good(n);
		queue<int> que;
		Vi prev(n, -1);

		A.init(ans);
		B.init(ans);
		ok = 0;

		rep(i, 0, n) if (!ans[i]) {
			if (A.canAdd(i)) que.push(i), prev[i]=-2;
			good[i] = B.canAdd(i);
		}

		rep(i, 0, n) if (ans[i]) {
			ans[i] = 0;
			A.init(ans);
			B.init(ans);
			rep(j, 0, n) if (i != j && !ans[j]) {
				if (A.canAdd(j)) G[i].pb(j);
				if (B.canAdd(j)) G[j].pb(i);
			}
			ans[i] = 1;
		}

		while (!que.empty()) {
			int i = que.front();
			que.pop();

			if (good[i]) {
				ans[i] = 1;
				while (prev[i] >= 0) {
					ans[i = prev[i]] = 0;
					ans[i = prev[i]] = 1;
				}
				ok = 1;
				break;
			}

			each(j, G[i]) if (prev[j] == -1)
				que.push(j), prev[j] = i;
		}
	}

	return ans;
}

// Matroid where each element has color
// and set is independent iff for each color c
// #{elements of color c} <= maxAllowed[c].
struct LimOracle {
	Vi color; // color[i] = color of i-th element
	Vi maxAllowed; // Limits for colors
	Vi tmp;

	// Init oracle for independent set S; O(n)
	void init(vector<bool>& S) {
		tmp = maxAllowed;
		rep(i, 0, sz(S)) tmp[color[i]] -= S[i];
	}

	// Check if S+{k} is independent; time: O(1)
	bool canAdd(int k) {
		return tmp[color[k]] > 0;
	}
};

// Graphic matroid - each element is edge,
// set is independent iff subgraph is acyclic.
struct GraphOracle {
	vector<Pii> elems; // Ground set: graph edges
	int n; // Number of vertices, indexed [0;n-1]
	Vi par;

	int find(int i) {
		return par[i] == -1 ? i
			: par[i] = find(par[i]);
	}

	// Init oracle for independent set S; ~O(n)
	void init(vector<bool>& S) {
		par.assign(n, -1);
		rep(i, 0, sz(S)) if (S[i])
			par[find(elems[i].x)] = find(elems[i].y);
	}

	// Check if S+{k} is independent; time: ~O(1)
	bool canAdd(int k) {
		return
			find(elems[k].x) != find(elems[k].y);
	}
};

// Co-graphic matroid - each element is edge,
// set is independent iff after removing edges
// from graph number of connected components
// doesn't change.
struct CographOracle {
	vector<Pii> elems; // Ground set: graph edges
	int n; // Number of vertices, indexed [0;n-1]
	vector<Vi> G;
	Vi pre, low;
	int cnt;

	int dfs(int v, int p) {
		pre[v] = low[v] = ++cnt;
		each(e, G[v]) if (e != p)
			low[v] = min(low[v], pre[e] ?: dfs(e,v));
		return low[v];
	}

	// Init oracle for independent set S; O(n)
	void init(vector<bool>& S) {
		G.assign(n, {});
		pre.assign(n, 0);
		low.resize(n);
		cnt = 0;
		rep(i, 0, sz(S)) if (!S[i]) {
			Pii e = elems[i];
			G[e.x].pb(e.y);
			G[e.y].pb(e.x);
		}
		rep(v, 0, n) if (!pre[v]) dfs(v, -1);
	}

	// Check if S+{k} is independent; time: O(1)
	bool canAdd(int k) {
		Pii e = elems[k];
		return max(pre[e.x], pre[e.y])
			!= max(low[e.x], low[e.y]);
	}
};

// Matroid equivalent to linear space with XOR
struct XorOracle {
	vector<ll> elems; // Ground set: numbers
	vector<ll> base;

	// Init for independent set S; O(n+r^2)
	void init(vector<bool>& S) {
		base.assign(63, 0);
		rep(i, 0, sz(S)) if (S[i]) {
			ll e = elems[i];
			rep(j, 0, sz(base)) if ((e >> j) & 1) {
				if (!base[j]) {
					base[j] = e;
					break;
				}
				e ^= base[j];
			}
		}
	}

	// Check if S+{k} is independent; time: O(r)
	bool canAdd(int k) {
		ll e = elems[k];
		rep(i, 0, sz(base)) if ((e >> i) & 1) {
			if (!base[i]) return 1;
			e ^= base[i];
		}
		return 0;
	}
};
