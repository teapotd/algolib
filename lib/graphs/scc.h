#pragma once
#include "../template.h"

// Tarjan's algorithm for SCC; time: O(n+m)
// UNTESTED

struct Vert {
	Vi edges; // comp is SCC index
	int pre{-1}, low{-1}, comp{-1};
};

struct Comp {
	Vi verts;
};

vector<Vert> G;
vector<Comp> scc; // Components
stack<int> partial;
int counter;

void tarjan(int i) {
	G[i].pre = G[i].low = ++counter;
	partial.push(i);

	each(e, G[i].edges) {
		if (G[e].pre < 0) {
			tarjan(e);
			G[i].low = min(G[i].low, G[e].low);
		} else if (G[e].comp < 0) {
			G[i].low = min(G[i].low, G[e].pre);
		}
	}

	if (G[i].pre == G[i].low) {
		int j, x = sz(scc);
		scc.emplace_back();
		do {
			j = partial.top();
			partial.pop();
			scc[x].verts.pb(j);
			G[j].comp = j;
		} while (i != j);
	}
}

void findSCC() { // Call me
	rep(i, 0, sz(G)) if (G[i].pre < 0) tarjan(i);
}
