#pragma once

#include "../template.h"

struct IntervalTree {
	using T = int;
	static constexpr T T_IDENT = INT_MIN;

	// (+, max)
	#define opModify(x, y) ((x)+(y))
	#define opQuery(x, y)  max(x, y)
	#define opTimes(x, t)  (x)

	// (max, max)
	// #define opModify(x, y) max(x, y)
	// #define opQuery(x, y)  max(x, y)
	// #define opTimes(x, t)  (x)

	// (+, +)
	// #define opModify(x, y) ((x)+(y))
	// #define opQuery(x, y)  ((x)+(y))
	// #define opTimes(x, t)  ((x)*(t))

	struct Node {
		T val{0}, extra{0};
	};

	vector<Node> tree;
	int len;

	IntervalTree(int size) {
		for (len = 1; len < size; len *= 2);
		tree.resize(len*2);
	}

	T query(int vStart, int vFinish, int i, int begin, int end) {
		if (vFinish <= begin || end <= vStart) return T_IDENT;
		if (vStart <= begin && end <= vFinish) return tree[i].val;

		int mid = (begin + end) / 2;
		T tmp = opQuery(query(vStart, vFinish, i*2, begin, mid), query(vStart, vFinish, i*2+1, mid, end));
		return opModify(tmp, opTimes(tree[i].extra, min(end, vFinish)-max(begin, vStart)));
	}

	void modify(int vStart, int vFinish, T val, int i, int begin, int end) {
		if (vFinish <= begin || end <= vStart) return;

		if (vStart > begin || end > vFinish) {
			int mid = (begin + end) / 2;
			modify(vStart, vFinish, val, i*2, begin, mid);
			modify(vStart, vFinish, val, i*2+1, mid, end);
		} else {
			tree[i].extra = opModify(tree[i].extra, val);
		}

		if (i < len) tree[i].val = opModify(opQuery(tree[i*2].val, tree[i*2+1].val), opTimes(tree[i].extra, end-begin));
		else         tree[i].val = tree[i].extra;
	}

	T    query(int begin, int end)         { return query(begin, end, 1, 0, len); }
	void modify(int begin, int end, T val) { modify(begin, end, val, 1, 0, len); }
};
