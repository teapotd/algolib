#include "testing.h"
#include "../lib/template.h"

struct Vert {
	int weight;
	Vi edges;

	DBP(weight, edges);
};

vector<Vert> graph;

int arr[10];

int main() {
	graph.resize(10);

	each(v, graph) {
		v.weight = r(1, 5);
		v.edges.resize(r(0, 9));
		each(x, v.edges) x = r(0, 9);
	}

	rep(i, 0, sz(graph)) deb(i, graph[i]);
	cerr << endl;

	auto kek = mp(mp(12, 34), "abcde");
	vector<int> vec{1,2,3,4};

	deb(kek, vec);

	map<char, int> test;
	test['d'] = 4;
	test['b'] = 2;
	test['a'] = 1;
	test['c'] = 3;

	deb(test, string("xd"));

	vector<bool> boolVec(5);
	deb(boolVec);

	cout << string("abcdef") << endl;

	int i = 5;
	each(x, arr) x = i++;
	const int* constArr = arr;
	deb(span(constArr, 5));

	deb(mp(mp(0, 1), 2), 3, 4);
	return 0;
}
