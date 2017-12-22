#include "testing.h"
#include "../lib/template.h"

struct Vert {
	int pre;
};

int main() {
	auto kek = mp(mp(12, 34), string("abcde"));
	vector<int> vec{1,2,3,4};
	Vert vert{5};

	dbg(vert.pre, kek, vec);

	vector<pair<char, int>> test{mp('a', 1), mp('b', 2), mp('c', 3), mp('d', 4)};
	dbg(test);
	return 0;
}
