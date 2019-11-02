#pragma once
#include "../template.h"
#include "edmonds_karp.h"
//#include "push_relabel.h" // if you need

struct Edge {
	int a, b; // vertices
	flow_t w; // weight
};

// Build Gomory-Hu tree; time: O(n*maxflow)
// Gomory-Hu tree encodes minimum cuts between
// all pairs of vertices: mincut for u and v
// is equal to minimum on path from u and v
// in Gomory-Hu tree. n is vertex count.
// Returns vector of Gomory-Hu tree edges.
//! Source: https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.pdf
vector<Edge> gomoryHu(vector<Edge>& edges,
                      int n) {
	MaxFlow flow(n);
	each(e, edges) flow.addEdge(e.a,e.b,e.w,e.w);

	vector<Edge> ret(n-1);
	rep(i, 1, n) ret[i-1] = {i, 0, 0};

	rep(i, 1, n) {
		ret[i-1].w = flow.maxFlow(i, ret[i-1].b);
		rep(j, i+1, n)
			if (ret[j-1].b == ret[i-1].b &&
			    flow.cutSide(j)) ret[j-1].b = i;
	}

	return ret;
}
