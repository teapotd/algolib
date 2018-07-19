#pragma once
#include "../template.h"

struct Vert {
	Vi edges, jumps;
	int level, pre, post;
};

int counter;
vector<Vert> V;

void initLCA(int i, int parent=-1, int d=0) {
	V[i].level = d;
	V[i].jumps.pb(parent < 0 ? i : parent);
	V[i].pre = ++counter;
	each(e, V[i].edges) if (e != parent)
		initLCA(e, i, d+1);
	V[i].post = ++counter;

	if (parent != -1) return;
	int depth = int(log2(sz(V))) + 2;
	rep(j, 0, depth) each(vert, V)
		vert.jumps.pb(V[vert.jumps[j]].jumps[j]);
}

bool isAncestor(int a, int b) {
	return V[a].pre <= V[b].pre &&
	       V[b].post <= V[a].post;
}

int laq(int a, int level) {
	for (int j = sz(V[a].jumps)-1; j >= 0; j--) {
		int k = V[a].jumps[j];
		if (level < V[k].level) a = k;
	}
	return V[a].level<=level ? a : V[a].jumps[0];
}

int lca(int a, int b) {
	for (int j = sz(V[a].jumps)-1; j >= 0; j--) {
		int k = V[a].jumps[j];
		if (!isAncestor(k, b)) a = k;
	}
	return isAncestor(a,b) ? a : V[a].jumps[0];
}

int distance(int a, int b) {
	return V[a].level + V[b].level
	       - V[lca(a, b)].level*2;
}
