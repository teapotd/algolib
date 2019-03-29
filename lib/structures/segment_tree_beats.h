#pragma once
#include "../template.h"

constexpr ll INF = 1e18;

//!!IGNORE
// NOT WORKING YET

// Segment tree with min/+ update and
// sum/max query; time: amortized O(n lg^2 n)
// or O(n lg n) if not using + operation
struct SegmentTree {
	using T = ll;

	struct Node {
		T sum{0},add{0},max1{0},max2{-INF},cnt1{1};
		void apply(T m, T p, int size) {
			add += p; sum += p*size;
			max1 += p; max2 += p;
			if (m < max1) {
				sum -= (max1-m)*cnt1;
				max1 = m;
			}
		}
	};

	vector<Node> V;
	int len;

	SegmentTree(int n = 0) { init(n); }
	void init(int n) {
		for (len = 1; len < n; len *= 2);
		V.assign(len*2, {});
	}

	void update(int i) {
		auto &v = V[i] = V[i*2], &r = V[i*2+1];
		v.sum += r.sum;
		if (r.max1 > v.max1) {
			v.max2 = v.max1;
			v.max1 = r.max1;
			v.cnt1 = r.cnt1;
		} else if (r.max1 == v.max1) {
			v.cnt1 += r.cnt1;
		} else if (r.max1 > v.max2) {
			v.max2 = r.max1;
		}
		v.max2 = max(v.max2, r.max2);
	}

	void push(int i, int s) {
		V[i*2].apply(V[i].max1, V[i].add, s/2);
		V[i*2+1].apply(V[i].max1, V[i].add, s/2);
		V[i].add = 0;
	}

	void setMin(int vBegin, int vEnd, T x,
	            int i = 1,
	            int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin ||
		    V[i].max1 < x) return;

		if (begin >= vBegin && end <= vEnd &&
		    V[i].max2 < x) {
			V[i].apply(x, 0, end-begin);
			return;
		}

		int mid = (begin+end) / 2;
		push(i, end-begin);
		setMin(vBegin, vEnd, x, begin, mid, i*2);
		setMin(vBegin, vEnd, x, mid, end, i*2+1);
		update(i);
	}

	void add(int vBegin, int vEnd, T x,
	         int i = 1,
	         int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin) return;

		if (begin >= vBegin && end <= vEnd) {
			V[i].apply(INF, x, end-begin);
			return;
		}

		int mid = (begin+end) / 2;
		push(i, end-begin);
		add(vBegin, vEnd, x, begin, mid, i*2);
		add(vBegin, vEnd, x, mid, end, i*2+1);
		update(i);
	}

	T sum(int vBegin, int vEnd, int i = 1,
	      int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd<=begin || end<=vBegin) return 0;
		if (vBegin <= begin && end <= vEnd)
			return V[i].sum;
		int mid = (begin+end) / 2;
		push(i, end-begin);
		return sum(vBegin, vEnd, i*2, begin, mid) +
		       sum(vBegin, vEnd, i*2+1, mid, end);
	}

	T getMax(int vBegin, int vEnd, int i = 1,
	         int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin)
			return -INF;
		if (vBegin <= begin && end <= vEnd)
			return V[i].max1;
		int mid = (begin+end) / 2;
		push(i, end-begin);
		return max(
			getMax(vBegin, vEnd, i*2, begin, mid),
			getMax(vBegin, vEnd, i*2+1, mid, end)
		);
	}
};
