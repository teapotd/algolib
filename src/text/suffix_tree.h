#pragma once
#include "../template.h"

constexpr int ALPHA = 26;

// Ukkonen's algorithm for online suffix tree
// construction; space: O(n*ALPHA); time: O(n)
// Real tree nodes are called dedicated nodes.
// "Nodes" lying on compressed edges are called
// implicit nodes and are represented
// as pairs (lower node, label index).
// Labels are represented as intervals [L;R)
// which refer to substrings [L;R) of txt.
// Leaves have labels of form [L;infinity),
// use getR to get current right endpoint.
// Suffix links are valid only for internal
// nodes (non-leaves).
struct SufTree {
	vi txt; // Text for which tree is built
	// to[v][c] = edge with label starting with c
	//            from node v
	vector<array<int, ALPHA>> to{ {} };
	vi L{0}, R{0}; // Parent edge label endpoints
	vi par{0};     // Parent link
	vi link{0};    // Suffix link
	pii cur{0, 0}; // Current state

	// Get current right end of node label
	int getR(int i) { return min(R[i],sz(txt)); }

	// Follow edge `e` of implicit node `s`.
	// Returns (-1, -1) if there is no edge.
	pii next(pii s, int e) {
		if (s.y < getR(s.x))
			return txt[s.y] == e ? mp(s.x, s.y+1)
			                     : mp(-1, -1);
		e = to[s.x][e];
		return e ? mp(e, L[e]+1) : mp(-1, -1);
	}

	// Create dedicated node for implicit node
	// and all its suffixes
	int split(pii s) {
		if (s.y == R[s.x]) return s.x;

		int t = sz(to); to.pb({});
		to[t][txt[s.y]] = s.x;
		L.pb(L[s.x]);
		R.pb(L[s.x] = s.y);
		par.pb(par[s.x]);
		par[s.x] = to[par[t]][txt[L[t]]] = t;
		link.pb(-1);

		int v = link[par[t]], l = L[t] + !par[t];
		while (l < R[t]) {
			v = to[v][txt[l]];
			l += getR(v) - L[v];
		}

		v = split({v, getR(v)-l+R[t]});
		link[t] = v;
		return t;
	}

	// Append letter from [0;ALPHA) to the back
	void add(int x) { // amortized time: O(1)
		pii t; txt.pb(x);
		while ((t = next(cur, x)).x == -1) {
			int m = split(cur);
			to[m][x] = sz(to);
			to.pb({});
			par.pb(m);
			L.pb(sz(txt)-1);
			R.pb(INT_MAX);
			link.pb(-1);
			cur = {link[m], getR(link[m])};
			if (!m) return;
		}
		cur = t;
	}
};
