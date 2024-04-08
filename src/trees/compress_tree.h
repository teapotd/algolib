#pragma once
#include "../template.h"

#include "lca.h" // or lca_linear.h

using vpi = vector<pair<int, int>>;

// Given a rooted tree and a subset S of nodes,
// compute the minimal subtree that contains
// all the nodes by adding all pairwise LCA's
// and compressing edges; time: O(|S| log |S|)
// Returns a list of (par, orig\_index)
// representing a tree rooted at 0.
// The root points to itself.
//! Source: https://github.com/jacynkaa/kactl/blob/main/content/graph/CompressTree.h
vpi compressTree(LCA& lca, const vi& subset) {
	static vi rev; rev.resize(sz(lca.pre));
	vi li = subset, &T = lca.pre;
	auto cmp = [&](int a, int b) {
		return T[a] < T[b];
	};
	sort(all(li), cmp);
	int m = sz(li)-1;
	rep(i, 0, m) {
		int a = li[i], b = li[i+1];
		li.push_back(lca(a, b));
	}
	sort(all(li), cmp);
	li.erase(unique(all(li)), li.end());
	rep(i, 0, sz(li)) rev[li[i]] = i;
	vpi ret = {pii(0, li[0])};
	rep(i, 0, sz(li)-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca(a, b)], b);
	}
	return ret;
}
