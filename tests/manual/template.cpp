#include "testing.h"
#include "../../src/template.h"

struct Vert {
	int weight;
	vi edges;

	DBP(weight, edges);
};

int main() {
	vector<Vert> graph;

	rep(i, 0, 10) {
		Vert v;
		v.weight = i + 100;
		rep(j, 0, i+2) v.edges.pb(i+j);
		graph.pb(v);
	}

	deb(graph);
	rep(i, 0, sz(graph)) deb(i, graph[i]);

	auto kek = make_pair(make_pair(12, 34), "abcde");
	vector<int> vec{1,2,3,4};

	deb(kek, vec);

	map<char, int> test;
	test['d'] = 4;
	test['b'] = 2;
	test['a'] = 1;
	test['c'] = 3;

	deb(test, string("xd"));

	vector<bool> boolVec(5);
	boolVec[1] = 1;
	deb(boolVec);

	auto tmp = make_pair(make_pair(0, 1), 2);
	deb(tmp, 3, 4);

	// This doesn't compile, because of order...
	// pair<vi, pii> nested = make_pair(vi{1,2,3}, pii(4,5));
	// deb(nested);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"

	// This doesn't parse properly anymore.
	deb((0,1,2),(3,4,5));

	// This exotic case doesn't work
	struct WeirdStruct { DBP((0,1,2)); };
	WeirdStruct weird;
	deb(weird);

#pragma GCC diagnostic pop

	bitset<16> bitSet;
	bitSet.set(5);
	deb(bitSet);

	vi emptyVec;
	deb(emptyVec);

	cout << string("abcdef") << endl;
	return 0;
}
