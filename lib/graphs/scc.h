#pragma once
#include "../template.h"

// UNTESTED

struct Vert {
	Vi edges;
	int pre{-1}, low{-1}, comp{-1};
};

struct Comp {
	Vi verts;
};

vector<Vert> G;
vector<Comp> comps;
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
		int j, x = sz(comps);
		comps.emplace_back();
		do {
			j = partial.top();
			partial.pop();
			comps[x].verts.pb(j);
			G[j].comp = j;
		} while (i != j);
	}
}

void scc() {
	rep(i, 0, sz(G)) if (G[i].pre < 0) tarjan(i);
}
