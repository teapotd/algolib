#pragma once
#include "../template.h"

struct Vert {
	Vi edges, jumps;
	int level, pre, post;
};

int counter;
vector<Vert> G;

void initLCA(int i, int parent=-1, int d=0) {
	G[i].level = d;
	G[i].jumps.pb(parent < 0 ? i : parent);
	G[i].pre = ++counter;
	each(e, G[i].edges) if (e != parent)
		initLCA(e, i, d+1);
	G[i].post = ++counter;

	if (parent != -1) return;
	int depth = int(log2(sz(G))) + 2;
	rep(j, 0, depth) each(vert, G)
		vert.jumps.pb(G[vert.jumps[j]].jumps[j]);
}

bool isAncestor(int a, int b) {
	return G[a].pre <= G[b].pre &&
	       G[b].post <= G[a].post;
}

int laq(int a, int level) {
	for (int j = sz(G[a].jumps)-1; j >= 0; j--) {
		int k = G[a].jumps[j];
		if (level < G[k].level) a = k;
	}
	return G[a].level<=level ? a : G[a].jumps[0];
}

int lca(int a, int b) {
	for (int j = sz(G[a].jumps)-1; j >= 0; j--) {
		int k = G[a].jumps[j];
		if (!isAncestor(k, b)) a = k;
	}
	return isAncestor(a,b) ? a : G[a].jumps[0];
}

int distance(int a, int b) {
	return G[a].level + G[b].level
	       - G[lca(a, b)].level*2;
}
