#pragma once
#include "../template.h"

// Customizable segment tree with lazy
// propagation. Configure by modifying:
// - T - data type for updates (stored type)
// - ID - neutral element for extra
// - Node - details in comments
struct SegmentTree {
	using T = int;
	static constexpr T ID = 0;          // +
	// static constexpr T ID = INT_MIN; // max/=

	struct Node {
		T extra{ID}; // Value to lazy propagate
		T sum{0}, great{INT_MIN}, nGreat{0};
		DBP(extra, sum, great, nGreat);

		// Merge with node R on the right
		void merge(const Node& R) {
			if (great < R.great)    nGreat =R.nGreat;
			else if(great==R.great) nGreat+=R.nGreat;

			sum += R.sum;
			great = max(great, R.great);
		}

		// Initialize as leaf node with value x
		void leaf(T x) {
			sum = great = x;
			nGreat = 1;
		}

		// + (apply update to node)
		void apply(T x, int size) {
			extra += x;
			sum += x*size;
			great += x;
		}

		// MAX
		// void apply(T x, int size) {
		// 	if (great <= x) nGreat = size;
		// 	extra = max(extra, x);
		// 	great = max(great, x);
		// 	// sum doesn't work here
		// }

		// =
		// void apply(T x, int size) {
		// 	extra = x;
		// 	sum = x*size;
		// 	great = x;
		// 	nGreat = size;
		// }
	};

	vector<Node> V;
	int len;

	SegmentTree(int n=0, T def=ID) {init(n,def);}

	void init(int n, T def) {
		for (len = 1; len < n; len *= 2);
		V.assign(len*2, {});
		rep(i, len, len+n) V[i].leaf(def);
		for (int i = len-1; i > 0; i--) update(i);
	}

	void update(int i) {
		V[i] = {};
		V[i].merge(V[i*2]);
		V[i].merge(V[i*2+1]);
	}

	void push(int i, int size) {
		if (V[i].extra != ID) {
			V[i*2].apply(V[i].extra, size/2);
			V[i*2+1].apply(V[i].extra, size/2);
			V[i].extra = ID;
		}
	}

	// Modify [vBegin;end) with x; time: O(lg n)
	void modify(int vBegin, int vEnd, T x,
	            int i = 1,
	            int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin) return;

		if (vBegin <= begin && end <= vEnd) {
			V[i].apply(x, end-begin);
			return;
		}

		int mid = (begin + end) / 2;
		push(i, end-begin);
		modify(vBegin, vEnd, x, i*2, begin, mid);
		modify(vBegin, vEnd, x, i*2+1, mid, end);
		update(i);
	}

	// Query [vBegin;vEnd); time: O(lg n)
	// Returns base nodes merged together
	Node query(int vBegin, int vEnd, int i = 1,
	           int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin)
			return {};
		if (vBegin <= begin && end <= vEnd)
			return V[i];

		int mid = (begin + end) / 2;
		push(i, end-begin);
		Node x = query(vBegin,vEnd,i*2,begin,mid);
		x.merge(query(vBegin,vEnd,i*2+1,mid,end));
		return x;
	}
};
