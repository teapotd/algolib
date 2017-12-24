#include "testing.h"
#include "../lib/template.h"

struct Vert {
	int weight;
	vector<int> edges;

	DPR(weight, edges);
};

vector<Vert> graph;

int main() {
	graph.resize(10);

	each(v, graph) {
		v.weight = r(1, 5);
		v.edges.resize(r(0, 9));
		each(x, v.edges) x = r(0, 9);
	}

	rep(i, 0, sz(graph)) dbg(i, graph[i]);

	auto kek = mp(mp(12, 34), "abcde");
	vector<int> vec{1,2,3,4};

	dbg(kek, vec);

	map<char, int> test;
	test['d'] = 4;
	test['b'] = 2;
	test['a'] = 1;
	test['c'] = 3;

	dbg(test);
	return 0;
}
