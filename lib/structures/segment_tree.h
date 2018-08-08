#pragma once
#include "../template.h"

// Optionally dynamic segment tree with lazy
// propagation. Configure by modifying:
// - T - data type for updates (stored type)
// - ID - neutral element for extra
// - Node - details in comments
struct SegmentTree {
	using T = int;
	static constexpr T ID = 0;          // +
	// static constexpr T ID = INT_MIN; // max/=

	struct Node {
		T extra{ID}; // Lazy propagated value
		// Aggregates: sum, max, count of max
		T sum{0}, great{INT_MIN}, nGreat{0};

		// int len, E[2] = {-1, -1}; // [DYNAMIC]

		// Initialize node with default value x
		void init(T x, int size) {
			sum = x*size; great = x; nGreat = 1;
			// len = size; // [DYNAMIC]
		}

		// Merge with node R on the right
		void merge(const Node& R) {
			if (great < R.great)    nGreat =R.nGreat;
			else if(great==R.great) nGreat+=R.nGreat;

			sum += R.sum;
			great = max(great, R.great);
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
	// T defVal; // [DYNAMIC]

	SegmentTree(int n=0, T def=ID) {init(n,def);}

	void init(int n, T def) {
		for (len = 1; len < n; len *= 2);

		// [STATIC] version
		V.assign(len*2, {});
		rep(i, len, len+n) V[i].init(def, 1);
		for (int i = len-1; i > 0; i--) update(i);

		// [DYNAMIC] version
		// defVal = def;
		// V.assign(2, {});
		// V[1].init(def, len);
	}

	// [STATIC] version
	int getChild(int i, int j) { return i*2+j; }

	// [DYNAMIC] version
	// int getChild(int i, int j) {
	// 	int& e = V[i].E[j];
	// 	if (e < 0) {
	// 		e = sz(V);
	// 		V.emplace_back();
	// 		V.back().init(defVal, V[i].len/2);
	// 	}
	// 	return e;
	// }

	int L(int i) { return getChild(i, 0); }
	int R(int i) { return getChild(i, 1); }

	void update(int i) {
		V[i] = {};
		V[i].merge(V[L(i)]);
		V[i].merge(V[R(i)]);
	}

	void push(int i, int size) {
		if (V[i].extra != ID) {
			V[L(i)].apply(V[i].extra, size/2);
			V[R(i)].apply(V[i].extra, size/2);
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
		modify(vBegin, vEnd, x, L(i), begin, mid);
		modify(vBegin, vEnd, x, R(i), mid, end);
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
		Node x = query(vBegin,vEnd,L(i),begin,mid);
		x.merge(query(vBegin,vEnd,R(i),mid,end));
		return x;
	}
};
