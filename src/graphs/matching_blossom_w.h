#pragma once
#include "../template.h"

// Edmond's Blossom algorithm for weighted
// maximum matching in general graphs; O(n^3)?
// Weights must be positive (I believe).
//! Source: https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.pdf
struct WeightedBlossom {
	struct edge { int u, v, w; };
	int n, s, nx;
	vector<vector<edge>> g;
	vi lab, match, slack, st, pa, S, vis;
	vector<vi> flo, floFrom;
	queue<int> q;

	// Initialize for k vertices
	WeightedBlossom(int k)
			: n(k), s(n*2+1),
			  g(s, vector<edge>(s)),
			  lab(s), match(s), slack(s), st(s),
			  pa(s), S(s), vis(s), flo(s),
			  floFrom(s, vi(n+1)) {
		rep(u, 1, n+1) rep(v, 1, n+1)
			g[u][v] = {u, v, 0};
	}

	// Add edge between u and v with weight w
	void addEdge(int u, int v, int w) {
		u++; v++;
		g[u][v].w = g[v][u].w = max(g[u][v].w, w);
	}

	// Compute max weight matching.
	// `count` is set to matching size,
	// `weight` is set to matching weight.
	// Returns vector `match` such that:
	// match[v] = vert matched to v or -1
	vi solve(int& count, ll& weight) {
		fill(all(match), 0);
		nx = n;
		weight = count = 0;
		rep(u, 0, n+1) flo[st[u] = u].clear();
		int tmp = 0;
		rep(u, 1, n+1) rep(v, 1, n+1) {
			floFrom[u][v] = (u-v ? 0 : v);
			tmp = max(tmp, g[u][v].w);
		}
		rep(u, 1, n+1) lab[u] = tmp;
		while (matching()) count++;
		rep(u, 1, n+1)
			if (match[u] && match[u] < u)
				weight += g[u][match[u]].w;
		vi ans(n);
		rep(i, 0, n) ans[i] = match[i+1]-1;
		return ans;
	}

	int delta(edge& e) {
		return lab[e.u]+lab[e.v]-g[e.u][e.v].w*2;
	}
	void updateSlack(int u, int x) {
		if (!slack[x] || delta(g[u][x]) <
			delta(g[slack[x]][x])) slack[x] = u;
	}
	void setSlack(int x) {
		slack[x] = 0;
		rep(u, 1, n+1) if (g[u][x].w > 0 &&
			st[u] != x && !S[st[u]])
				updateSlack(u, x);
	}
	void push(int x) {
		if (x <= n) q.push(x);
		else rep(i, 0, sz(flo[x])) push(flo[x][i]);
	}
	void setSt(int x, int b) {
		st[x] = b;
		if (x > n) rep(i, 0, sz(flo[x]))
			setSt(flo[x][i],b);
	}
	int getPr(int b, int xr) {
		int pr = int(find(all(flo[b]), xr) -
			flo[b].begin());
		if (pr % 2) {
			reverse(flo[b].begin()+1, flo[b].end());
			return sz(flo[b]) - pr;
		} else return pr;
	}
	void setMatch(int u, int v) {
		match[u] = g[u][v].v;
		if (u <= n) return;
		edge e = g[u][v];
		int xr = floFrom[u][e.u], pr = getPr(u,xr);
		rep(i, 0, pr)
			setMatch(flo[u][i], flo[u][i^1]);
		setMatch(xr, v);
		rotate(flo[u].begin(), flo[u].begin()+pr,
			flo[u].end());
	}
	void augment(int u, int v) {
		while (1) {
			int xnv = st[match[u]];
			setMatch(u, v);
			if (!xnv) return;
			setMatch(xnv, st[pa[xnv]]);
			u = st[pa[xnv]], v = xnv;
		}
	}
	int getLca(int u, int v) {
		static int t = 0;
		for (++t; u||v; swap(u, v)) {
			if (!u) continue;
			if (vis[u] == t) return u;
			vis[u] = t;
			u = st[match[u]];
			if (u) u = st[pa[u]];
		}
		return 0;
	}
	void blossom(int u, int lca, int v) {
		int b = n+1;
		while (b <= nx && st[b]) ++b;
		if (b > nx) ++nx;
		lab[b] = S[b] = 0;
		match[b] = match[lca];
		flo[b].clear();
		flo[b].pb(lca);
		for (int x=u, y; x != lca; x = st[pa[y]]) {
			flo[b].pb(x);
			flo[b].pb(y = st[match[x]]);
			push(y);
		}
		reverse(flo[b].begin()+1, flo[b].end());
		for (int x=v, y; x != lca; x = st[pa[y]]) {
			flo[b].pb(x);
			flo[b].pb(y = st[match[x]]);
			push(y);
		}
		setSt(b, b);
		rep(x, 1, nx+1) g[b][x].w = g[x][b].w = 0;
		rep(x, 1, n+1) floFrom[b][x] = 0;
		rep(i, 0, sz(flo[b])) {
			int xs = flo[b][i];
			rep(x, 1, nx+1) if (!g[b][x].w ||
				delta(g[xs][x]) < delta(g[b][x]))
					g[b][x]=g[xs][x], g[x][b]=g[x][xs];
			rep(x, 1, n+1) if (floFrom[xs][x])
				floFrom[b][x] = xs;
		}
		setSlack(b);
	}
	void blossom(int b) {
		each(e, flo[b]) setSt(e, e);
		int xr = floFrom[b][g[b][pa[b]].u];
		int pr = getPr(b, xr);
		for (int i = 0; i < pr; i += 2) {
			int xs = flo[b][i], xns = flo[b][i+1];
			pa[xs] = g[xns][xs].u;
			S[xs] = 1; S[xns] = slack[xs] = 0;
			setSlack(xns); push(xns);
		}
		S[xr] = 1; pa[xr] = pa[b];
		rep(i, pr+1, sz(flo[b])) {
			int xs = flo[b][i];
			S[xs] = -1; setSlack(xs);
		}
		st[b] = 0;
	}
	bool found(const edge& e) {
		int u = st[e.u], v = st[e.v];
		if (S[v] == -1) {
			pa[v] = e.u; S[v] = 1;
			int nu = st[match[v]];
			slack[v] = slack[nu] = S[nu] = 0;
			push(nu);
		} else if (!S[v]) {
			int lca = getLca(u, v);
			if (!lca) return augment(u, v),
				augment(v, u), 1;
			else blossom(u, lca, v);
		}
		return 0;
	}
	bool matching() {
		fill(S.begin(), S.begin()+nx+1, -1);
		fill(slack.begin(), slack.begin()+nx+1, 0);
		q = {};
		rep(x, 1, nx+1)
			if (st[x] == x && !match[x])
				pa[x] = S[x] = 0, push(x);
		if (q.empty()) return 0;
		while (1) {
			while (q.size()) {
				int u = q.front(); q.pop();
				if (S[st[u]] == 1) continue;
				rep(v, 1, n+1)
					if (g[u][v].w > 0 && st[u] != st[v]){
						if (!delta(g[u][v])) {
							if (found(g[u][v])) return 1;
						} else updateSlack(u, st[v]);
					}
			}
			int d = INT_MAX;
			rep(b, n+1, nx+1)
				if (st[b] == b && S[b] == 1)
					d = min(d, lab[b]/2);
			rep(x, 1, nx+1)
				if (st[x] == x && slack[x]) {
					if (S[x] == -1)
						d = min(d, delta(g[slack[x]][x]));
					else if (!S[x])
						d = min(d,delta(g[slack[x]][x])/2);
				}
			rep(u, 1, n+1) {
				if (!S[st[u]]) {
					if (lab[u] <= d) return 0;
					lab[u] -= d;
				} else if (S[st[u]] == 1) lab[u] += d;
			}
			rep(b, n+1, nx+1) if (st[b] == b) {
				if (!S[st[b]]) lab[b] += d*2;
				else if (S[st[b]] == 1) lab[b] -= d*2;
			}
			q = {};
			rep(x, 1, nx+1)
				if (st[x] == x && slack[x] &&
					st[slack[x]] != x &&
					!delta(g[slack[x]][x]) &&
					found(g[slack[x]][x])) return 1;
			rep(b, n+1, nx+1)
				if (st[b] == b && S[b] == 1 && !lab[b])
					blossom(b);
		}
		return 0;
	}
};
