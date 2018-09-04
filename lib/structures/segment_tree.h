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

		// Initialize node with default value x
		void init(T x, int size) {
			sum = x*size; great = x; nGreat = size;
		}

		// Merge with node R on the right
		void merge(const Node& R) {
			if (great < R.great)    nGreat =R.nGreat;
			else if(great==R.great) nGreat+=R.nGreat;

			sum += R.sum;
			great = max(great, R.great);
		}

		// + version
		// Apply modification to node, return
		// value to be applied to node on right
		T apply(T x, int size) {
			extra += x;
			sum += x*size;
			great += x;
			return x;
		}

		// MAX
		// T apply(T x, int size) {
		// 	if (great <= x) nGreat = size;
		// 	extra = max(extra, x);
		// 	great = max(great, x);
		// 	// sum doesn't work here
		//  return x;
		// }

		// =
		// T apply(T x, int size) {
		// 	extra = x;
		// 	sum = x*size;
		// 	great = x;
		// 	nGreat = size;
		//  return x;
		// }
	};

	vector<Node> V;
	int len;
	// vector<array<int, 3>> links; // [DYNAMIC]
	// T defVal;                    // [DYNAMIC]

	SegmentTree(int n=0, T def=ID) {init(n,def);}

	void init(int n, T def) {
		for (len = 1; len < n; len *= 2);

		// [STATIC] version
		V.assign(len*2, {});
		rep(i, len, len+n) V[i].init(def, 1);
		for (int i = len-1; i > 0; i--) update(i);

		// [DYNAMIC] version
		// defVal = def;
		// links.assign(2, {-1, -1, len});
		// V.assign(2, {});
		// V[1].init(def, len);
	}

	// [STATIC] version
	int getChild(int i, int j) { return i*2+j; }

	// [DYNAMIC] version
	// int getChild(int i, int j) {
	// 	if (links[i][j] < 0) {
	// 		int size = links[i][2] / 2;
	// 		links[i][j] = sz(V);
	// 		links.push_back({ -1, -1, size });
	// 		V.emplace_back();
	// 		V.back().init(defVal, size);
	// 	}
	// 	return links[i][j];
	// }

	int L(int i) { return getChild(i, 0); }
	int R(int i) { return getChild(i, 1); }

	void update(int i) {
		int a = L(i), b = R(i);
		V[i] = {};
		V[i].merge(V[a]);
		V[i].merge(V[b]);
	}

	void push(int i, int size) {
		int e = V[i].extra;
		if (e != ID) {
			e = V[L(i)].apply(e, size/2);
			V[R(i)].apply(e, size/2);
			V[i].extra = ID;
		}
	}

	// Modify [vBegin;end) with x; time: O(lg n)
	T modify(int vBegin, int vEnd, T x,
	         int i = 1,
	         int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin)
			return x;

		if (vBegin <= begin && end <= vEnd) {
			return V[i].apply(x, end-begin);
		}

		int mid = (begin + end) / 2;
		push(i, end-begin);
		x = modify(vBegin,vEnd,x,L(i),begin,mid);
		x = modify(vBegin,vEnd,x,R(i),mid,end);
		update(i);
		return x;
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

	// TODO: generalize?
	// Find longest suffix of given interval
	// such that max value is smaller than val.
	// Returns suffix begin index; time: O(lg n)
	T search(int vBegin, int vEnd, int val,
	         int i=1, int begin=0, int end=-1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin)
			return begin;

		if (vBegin <= begin && end <= vEnd) {
			if (V[i].great < val) return begin;
			if (begin+1 == end) return end;
		}

		int mid = (begin+end) / 2;
		push(i, end-begin);

		int ind = search(vBegin, vEnd, val,
		                 R(i), mid, end);
		if (ind > mid) return ind;
		return search(vBegin, vEnd, val,
		              L(i), begin, mid);
	}
};
