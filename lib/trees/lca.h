#pragma once
#include "../template.h"

struct Vert {
	Vi edges, jumps;
	int level, pre, post;
	DBP(edges, jumps, level, pre, post);
};

int counter;

void initLCA(vector<Vert>& V, int i,
	           int parent = -1, int d = 0) {
	V[i].level = d;
	V[i].jumps.pb(parent < 0 ? i : parent);
	V[i].pre = ++counter;
	each(e, V[i].edges) if (e != parent)
		initLCA(V, e, i, d+1);
	V[i].post = ++counter;

	if (parent != -1) return;
	int depth = int(log2(sz(V))) + 2;
	rep(j, 0, depth) {
		each(vert, V)
			vert.jumps.pb(V[vert.jumps[j]].jumps[j]);
	}
}

bool isAncestor(vector<Vert>& V, int a, int b){
	return V[a].pre <= V[b].pre &&
	       V[b].post <= V[a].post;
}

int laq(vector<Vert>& V, int a, int level) {
	for (int j = sz(V[a].jumps)-1; j >= 0; j--) {
		int k = V[a].jumps[j];
		if (level < V[k].level) a = k;
	}
	return V[a].level<=level ? a : V[a].jumps[0];
}

int lca(vector<Vert>& V, int a, int b) {
	for (int j = sz(V[a].jumps)-1; j >= 0; j--) {
		int k = V[a].jumps[j];
		if (!isAncestor(V, k, b)) a = k;
	}
	return isAncestor(V,a,b) ? a : V[a].jumps[0];
}

int distance(vector<Vert>& V, int a, int b) {
	return V[a].level + V[b].level
	       - V[lca(V, a, b)].level*2;
}
