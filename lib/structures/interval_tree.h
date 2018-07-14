#pragma once
#include "../template.h"
// UNTESTED

struct IntervalTree {
	using T = int;
	static constexpr T NONE = INT_MIN;

	// (=, +)
	struct Node {
		T extra{NONE}, sum{0};

		void apply(T x, int size) {
			extra = x;
			sum = x*size;
		}

		void merge(const Node& R) {
			sum += R.sum;
		}
	};

	// ---

	vector<Node> V;
	int len;

	IntervalTree(int n) {
		for (len = 1; len < n; len *= 2);
		V.resize(len*2);
		for (int i = len-1; i > 0; i--) update(i);
	}

	void update(int i) {
		V[i] = {};
		V[i].merge(V[i*2]);
		V[i].merge(V[i*2+1]);
	}

	void push(int i, int size) {
		if (V[i].extra != NONE) {
			V[i*2].apply(V[i].extra, size/2);
			V[i*2+1].apply(V[i].extra, size/2);
			V[i].extra = NONE;
		}
	}

	void modify(int vBegin, int vEnd, T x,
		          int i = 0,
		          int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin) return;
		if (vBegin <= begin && end <= vEnd)
			V[i].apply(x, end-begin);

		int mid = (begin + end) / 2;
		push(i, end-begin);
		modify(vBegin, vEnd, x, i*2, begin, mid);
		modify(vBegin, vEnd, x, i*2+1, mid, end);
		update(i);
	}

	Node query(int vBegin, int vEnd, int i = 0,
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
