#define TREE_PLUS 1
#include "../../../../../src/segtree/general_fixed.h"
#include "../../../testing.hpp"

auto asTuple(const SegTree::Agg& a) {
	return make_tuple(a.sum, a.vMax, a.nMax);
}

bool operator==(const SegTree::Agg& lhs, const SegTree::Agg& rhs) {
	return asTuple(lhs) == asTuple(rhs);
}

int sampleUpdate() {
	return randInt(-5, 5);
}

struct Naive {
	std::vector<int> seq;

	Naive(int n = 0) : seq(n, 0) {}

	void update(int vb, int ve, int val) {
		for (int i = vb; i < ve; i++) {
			seq[i] += val;
		}
	}

	SegTree::Agg query(int vb, int ve) {
		if (vb >= ve) return {};
		SegTree::Agg ret;
		ret.sum = accumulate(seq.begin()+vb, seq.begin()+ve, 0);
		ret.vMax = *max_element(seq.begin()+vb, seq.begin()+ve);
		ret.nMax = int(count(seq.begin()+vb, seq.begin()+ve, ret.vMax));
		return ret;
	}
};

#include "test.hpp"
