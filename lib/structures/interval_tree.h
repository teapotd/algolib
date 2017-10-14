#pragma once

#include "../template.h"

struct IntervalTree {
	using T = int;

	// (+, max)
	static constexpr T T_IDENT = INT_MIN;
	#define opModify(x, y) ((x)+(y))
	#define opQuery(x, y)  max(x, y)
	#define opTimes(x, t)  (x)

	// (max, max)
	// static constexpr T T_IDENT = INT_MIN;
	// #define opModify(x, y) max(x, y)
	// #define opQuery(x, y)  max(x, y)
	// #define opTimes(x, t)  (x)

	// (+, +)
	// static constexpr T T_IDENT = 0;
	// #define opModify(x, y) ((x)+(y))
	// #define opQuery(x, y)  ((x)+(y))
	// #define opTimes(x, t)  ((x)*(t))

	// (=, max)
	// static constexpr T T_IDENT = INT_MIN;
	// #define opQuery(x, y)  max(x, y)
	// #define opTimes(x, t)  (x)

	struct Node {
		T   val{0}, extra{0};
		int nEqual{1};       // EXTENSION: min/max element count
		bool current{false}; // EXTENSION: (set, ?) tree
	};

	vector<Node> tree;
	int len;

	IntervalTree(int size) {
		for (len = 1; len < size; len *= 2);
		tree.resize(len*2);

		// EXTENSION: min/max element count
		repd(i, len-1, 0) tree[i].nEqual = tree[i*2].nEqual + tree[i*2+1].nEqual;
	}

	T query(int vStart, int vFinish, int i = 1, int begin = 0, int end = -1) {
		if (end < 0) end = len;
		// push(i, begin, end); // EXTENSION: (set, ?) tree

		if (vStart >= vFinish || vFinish <= begin || end <= vStart) return T_IDENT;
		if (vStart <= begin && end <= vFinish)                      return tree[i].val;

		int mid = (begin + end) / 2;
		T tmp = opQuery(query(vStart, vFinish, i*2, begin, mid),
			            query(vStart, vFinish, i*2+1, mid, end));

		// return tmp; // EXTENSION: (set, ?) tree -> use this instead of following line
		return opModify(tmp, opTimes(tree[i].extra, min(end, vFinish)-max(begin, vStart)));
	}

	// EXTENSION: min/max element count -> use this instead of above
	T queryCount(int vStart, int vFinish, int& count, int i = 1, int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vStart >= vFinish || vFinish <= begin || end <= vStart) return T_IDENT;
		// push(i, begin, end); // EXTENSION: (set, ?) tree

		if (vStart <= begin && end <= vFinish) {
			count = tree[i].nEqual;
			return tree[i].val;
		}

		int eq1 = 0, eq2 = 0, mid = (begin + end) / 2;
		T v1  = queryCount(vStart, vFinish, eq1, i*2, begin, mid);
		T v2  = queryCount(vStart, vFinish, eq2, i*2+1, mid, end);
		T tmp = opQuery(v1, v2);

		count = (v1 == tmp ? eq1 : 0) + (v2 == tmp ? eq2 : 0);
		// return tmp; // EXTENSION: (set, ?) tree -> use this instead of following line
		return opModify(tmp, opTimes(tree[i].extra, min(end, vFinish)-max(begin, vStart)));
	}

	void modify(int vStart, int vFinish, T val, int i = 1, int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vFinish <= begin || end <= vStart) return;

		if (vStart > begin || end > vFinish) {
			int mid = (begin + end) / 2;
			modify(vStart, vFinish, val, i*2, begin, mid);
			modify(vStart, vFinish, val, i*2+1, mid, end);
		} else {
			tree[i].extra = opModify(tree[i].extra, val);
		}

		if (i < len) tree[i].val = opModify(opQuery(tree[i*2].val, tree[i*2+1].val),
			                                opTimes(tree[i].extra, end-begin));
		else         tree[i].val = tree[i].extra;

		// EXTENSION: min/max element count
		tree[i].nEqual = (i >= len);
		if (i < len) {
			T tmp = opQuery(tree[i*2].val, tree[i*2+1].val);
			if (tmp == tree[i*2].val)   tree[i].nEqual += tree[i*2].nEqual;
			if (tmp == tree[i*2+1].val) tree[i].nEqual += tree[i*2+1].nEqual;
		}
	}

	// EXTENSION: (set, ?) tree -> use this instead of above
	// void modify(int vStart, int vFinish, T val, int i = 1, int begin = 0, int end = -1) {
	// 	if (end < 0) end = len;
	// 	if (vFinish <= begin || end <= vStart) return;
	// 	push(i, begin, end);

	// 	if (vStart > begin || end > vFinish) {
	// 		int mid = (begin + end) / 2;
	// 		modify(vStart, vFinish, val, i*2, begin, mid);
	// 		modify(vStart, vFinish, val, i*2+1, mid, end);
	// 	} else {
	// 		tree[i].extra = val;
	// 		tree[i].val = opTimes(val, end-begin);
	// 		tree[i].current = true;
	// 		tree[i].nEqual = end-begin; // EXTENSION: min/max element count
	// 		return;
	// 	}

	// 	if (i < len) tree[i].val = opQuery(tree[i*2].val, tree[i*2+1].val);

	// 	// EXTENSION: min/max element count
	// 	tree[i].nEqual = (i >= len);
	// 	if (i < len) {
	// 		T tmp = opQuery(tree[i*2].val, tree[i*2+1].val);
	// 		if (tmp == tree[i*2].val)   tree[i].nEqual += tree[i*2].nEqual;
	// 		if (tmp == tree[i*2+1].val) tree[i].nEqual += tree[i*2+1].nEqual;
	// 	}
	// }

	// EXTENSION: (set, ?) tree
	void push(int i, int begin, int end) {
		if (!tree[i].current || i >= len) return;
		tree[i*2].val     = tree[i*2+1].val     = opTimes(tree[i].extra, (end-begin)/2);
		tree[i*2].extra   = tree[i*2+1].extra   = tree[i].extra;
		tree[i*2].current = tree[i*2+1].current = true;
		tree[i].current   = false;

		// EXTENSION: min/max element count
		tree[i*2].nEqual = tree[i*2+1].nEqual = (end-begin)/2;
	}
};
