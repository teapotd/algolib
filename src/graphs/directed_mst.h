#pragma once
#include "../template.h"
#include "../structures/find_union_undo.h"

struct Edge {
	int a, b;
	ll w;
};

struct Node {
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};

Node* merge(Node* a, Node* b) {
	if (!a || !b) return a ?: b;
	a->prop(); b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}

void pop(Node*& a) {
	a->prop(); a = merge(a->l, a->r);
}

// Find directed minimum spanning tree
// rooted at vertex `root`; O(m log n)
// Returns weight of found spanning tree.
// out[i] = parent of i-th vertex in the tree,
// out[root] = -1
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/DirectedMST.h
ll dmst(vector<Edge>& edges,
        int n, int root, vi& out) {
	RollbackFAU uf(n);
	vector<Node*> heap(n);

	each(e, edges)
		heap[e.b] = merge(heap[e.b],
			new Node{e, 0, 0, 0});

	ll res = 0;
	vi seen(n, -1), path(n);
	seen[root] = root;

	struct Cycle { int u, t; vector<Edge> e; };
	vector<Edge> Q(n), in(n, {-1, -1, 0}), comp;
	vector<Cycle> cycs;

	rep(s, 0, n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			if (!heap[u]) return out.clear(), -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w; pop(heap[u]);
			Q[qi] = e; path[qi++] = u; seen[u] = s;
			res += e.w; u = uf.find(e.a);
			if (seen[u] == s) {
				Node* cyc = 0;
				int end = qi, time = uf.time();
				do cyc = merge(cyc,heap[w=path[--qi]]);
				while (uf.join(u, w));
				heap[u = uf.find(u)] = cyc;
				seen[u] = -1;
				cycs.pb({u, time, {&Q[qi], &Q[end]}});
			}
		}
		rep(i, 0, qi) in[uf.find(Q[i].b)] = Q[i];
	}

	reverse(all(cycs));
	each(c, cycs) {
		uf.rollback(c.t);
		Edge tmp = in[c.u];
		each(e, c.e) in[uf.find(e.b)] = e;
		in[uf.find(tmp.b)] = tmp;
	}
	out.resize(n);
	rep(i, 0, n) out[i] = in[i].a;
	return res;
}
