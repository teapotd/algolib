#pragma once
#include "../template.h"
#include "flow_edmonds_karp.h"
//#include "flow_push_relabel.h" // if you need

// Flow with demands; time: O(maxflow)
struct FlowDemands {
	MaxFlow net;
	vector<vector<flow_t>> demands;
	flow_t total{0};

	// Initialize for k vertices
	FlowDemands(int k = 0) : net(2) {
		while (k--) addVert();
	}

	// Add new vertex
	int addVert() {
		int v = net.addVert();
		demands.pb({});
		net.addEdge(0, v, 0);
		net.addEdge(v, 1, 0);
		return v-2;
	}

	// Add edge from u to v with demand dem
	// and capacity cap (dem <= flow <= cap).
	// Returns edge index in adjacency list of u.
	int addEdge(int u, int v,
	            flow_t dem, flow_t cap) {
		demands[u].pb(dem);
		demands[v].pb(0);
		total += dem;
		net.G[0][v].cap += dem;
		net.G[u+2][1].cap += dem;
		return net.addEdge(u+2, v+2, cap-dem) - 2;
	}

	// Check if there exists a flow with value f
	// for source src and destination dst.
	// For circulation, you can set args to 0.
	bool canFlow(int src, int dst, flow_t f) {
		net.addEdge(dst += 2, src += 2, f);
		f = net.maxFlow(0, 1);
		net.G[src].pop_back();
		net.G[dst].pop_back();
		return f == total;
	}

	// Get flow through e-th edge of vertex v
	flow_t getFlow(int v, int e) {
		return net.getFlow(v+2,e+2)+demands[v][e];
	}
};
