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

vector<Vert> V;
vector<Comp> comps;
stack<int> partial;
int counter;

void tarjan(int i) {
	V[i].pre = V[i].low = ++counter;
	partial.push(i);

	each(e, V[i].edges) {
		if (V[e].pre < 0) {
			tarjan(e);
			V[i].low = min(V[i].low, V[e].low);
		} else if (V[e].comp < 0) {
			V[i].low = min(V[i].low, V[e].pre);
		}
	}

	if (V[i].pre == V[i].low) {
		int j, x = sz(comps);
		comps.emplace_back();
		do {
			j = partial.top();
			partial.pop();
			comps[x].verts.pb(j);
			V[j].comp = j;
		} while (i != j);
	}
}

void scc() {
	rep(i, 0, sz(V)) if (V[i].pre < 0) tarjan(i);
}
