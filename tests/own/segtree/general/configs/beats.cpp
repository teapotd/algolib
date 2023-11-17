#define TREE_BEATS 1
#include "../../../../../src/segtree/general_fixed.h"
#include "../../../base_test.hpp"

auto asTuple(const SegTree::Agg& a) {
	return make_tuple(a.vMax, a.nMax, a.max2, a.sum);
}

bool operator==(const SegTree::Agg& lhs, const SegTree::Agg& rhs) {
	return asTuple(lhs) == asTuple(rhs);
}

pii sampleUpdate() {
	int t = randInt(1, 3);
	int add = (t&1 ? randInt(-5, 5) : 0);
	int mn = (t&1 ? randInt(-20, 20) : 0);
	return {add, mn};
}

struct Naive {
	std::vector<int> seq;

	Naive(int n = 0) : seq(n, 0) {}

	void update(int vb, int ve, pii val) {
		for (int i = vb; i < ve; i++) {
			seq[i] = min(seq[i] + val.x, val.y);
		}
	}

	SegTree::Agg query(int vb, int ve) {
		if (vb >= ve) return {};
		SegTree::Agg ret;
		ret.sum = accumulate(seq.begin()+vb, seq.begin()+ve, 0);
		ret.vMax = *max_element(seq.begin()+vb, seq.begin()+ve);
		ret.nMax = int(count(seq.begin()+vb, seq.begin()+ve, ret.vMax));
		ret.max2 = INT_MIN;
		rep(i, vb, ve) {
			if (seq[i] != ret.vMax) {
				ret.max2 = max(ret.max2, seq[i]);
			}
		}
		return ret;
	}
};

#include "test.hpp"
