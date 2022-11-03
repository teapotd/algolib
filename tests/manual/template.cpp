#include "testing.h"
#include "../../src/template.h"

struct Vert {
	pii weight;
	vi edges;
	DBP(weight, edges);
};

struct Elem {
	const char *name;
	string value;
	DBP(name, value);
};

struct Nested {
	Elem A, B;
	int n;
	DBP(A, B, n);
};

int main() {
	vector<Vert> graph = {
		{ {1,2}, {3,4,5,6,7}, },
		{ {9,8}, {7,6,5,4}, },
		{ {10,20}, {30}, },
		{ {-1,-2}, {}, },
	};

	deb(graph);
	rep(i, 0, sz(graph)) {
		deb(i, graph[i]);
	}

	Nested nestedStructs = {
		{"AAA", "alpha"},
		{"BBB", "beta"},
		123,
	};

	deb(nestedStructs);

	auto nestedPairs1 = make_pair(make_pair(0, 1), make_pair(2, 3));
	deb(nestedPairs1, 3, 4);

	auto nestedPairs2 = make_pair(make_pair(12, 34), "abcde");
	vector<pii> vecOfPairs = { {10,20}, {20,30}, {40,50}, {50,60} };

	deb(nestedPairs2, vecOfPairs);

	map<char, int> charMap;
	charMap['d'] = 4;
	charMap['b'] = 2;
	charMap['a'] = 1;
	charMap['c'] = 3;

	deb(charMap, string("inline"));

	vector<bool> vecOfBools(5);
	vecOfBools[1] = 1;
	deb(vecOfBools);

	bitset<16> bitSet;
	bitSet.set(1);
	bitSet.set(5);
	deb(bitSet, bitSet);

	vi emptyVec;
	deb(emptyVec);

	deb(1, 2, "inline");
	deb(1,2,"inline");

	cerr << 1 << ' ' << "qwerty" << endl;
	cerr << string("abcdef") << endl;

	// This doesn't compile if operators are not defined in std namespace.
	//pair<vi, pii> vecInPair = make_pair(vi{1,2,3}, pii(4,5));
	//deb(vecInPair);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"

	// This doesn't parse properly anymore, but we don't care.
	deb((0, 1, 2), (3, 4, 5));

#pragma GCC diagnostic pop
	return 0;
}
