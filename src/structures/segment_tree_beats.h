#pragma once
#include "../template.h"

constexpr ll INF = 1e18;

// Segment tree with min/+ update and
// sum/max query; time: amortized O(n lg^2 n)
// or O(n lg n) if not using + operation
struct SegmentTree {
	using T = ll;
	vector<T> sum, plus, max1, max2, cnt1;
	int len;

	SegmentTree(int n = 0) {
		for (len = 1; len < n; len *= 2);
		sum.resize(len*2);
		plus.resize(len*2);
		max1.resize(len*2);
		max2.assign(len*2, -INF);
		cnt1.assign(len*2, 1);
		for (int i = len-1; i > 0; i--) update(i);
	}

	void apply(int i, T m, T p, int size) {
		plus[i] += p; sum[i] += p*size;
		max1[i] += p; max2[i] += p;
		if (m < max1[i]) {
			sum[i] -= (max1[i]-m)*cnt1[i];
			max1[i] = m;
		}
	}

	void update(int i) {
		int a = i*2, b = i*2+1;
		sum[i] = sum[a] + sum[b];
		plus[i] = 0;
		max1[i] = max1[a];
		max2[i] = max2[a];
		cnt1[i] = cnt1[a];

		if (max1[b] > max1[i]) {
			max2[i] = max1[i];
			max1[i] = max1[b];
			cnt1[i] = cnt1[b];
		} else if (max1[b] == max1[i]) {
			cnt1[i] += cnt1[b];
		} else if (max1[b] > max2[i]) {
			max2[i] = max1[b];
		}
		max2[i] = max(max2[i], max2[b]);
	}

	void push(int i, int s) {
		rep(j, 0, 2)
			apply(i*2+j, max1[i], plus[i], s/2);
		plus[i] = 0;
	}

	// Apply min with x on [vBegin;vEnd)
	// time: amortized O(lg n) or O(lg^2 n)
	void setMin(int vBegin, int vEnd, T x,
	            int i = 1,
	            int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin ||
				max1[i] < x) return;

		if (begin >= vBegin && end <= vEnd &&
		    max2[i] < x)
			return apply(i, x, 0, end-begin);

		int mid = (begin+end) / 2;
		push(i, end-begin);
		setMin(vBegin, vEnd, x, i*2, begin, mid);
		setMin(vBegin, vEnd, x, i*2+1, mid, end);
		update(i);
	}

	// Add x on [vBegin;vEnd); time: O(lg n)
	void add(int vBegin, int vEnd, T x,
	         int i = 1,
	         int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin) return;
		if (begin >= vBegin && end <= vEnd)
			return apply(i, INF, x, end-begin);

		int mid = (begin+end) / 2;
		push(i, end-begin);
		add(vBegin, vEnd, x, i*2, begin, mid);
		add(vBegin, vEnd, x, i*2+1, mid, end);
		update(i);
	}

	// Query sum of [vBegin;vEnd); time: O(lg n)
	T getSum(int vBegin, int vEnd, int i = 1,
	         int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd<=begin || end<=vBegin) return 0;
		if (vBegin <= begin && end <= vEnd)
			return sum[i];
		int mid = (begin+end) / 2;
		push(i, end-begin);
		return getSum(vBegin,vEnd,i*2,begin,mid) +
		       getSum(vBegin,vEnd,i*2+1,mid,end);
	}

	// Query max of [vBegin;vEnd); time: O(lg n)
	T getMax(int vBegin, int vEnd, int i = 1,
	         int begin = 0, int end = -1) {
		if (end < 0) end = len;
		if (vEnd <= begin || end <= vBegin)
			return -INF;
		if (vBegin <= begin && end <= vEnd)
			return max1[i];
		int mid = (begin+end) / 2;
		push(i, end-begin);
		return max(
			getMax(vBegin, vEnd, i*2, begin, mid),
			getMax(vBegin, vEnd, i*2+1, mid, end)
		);
	}
};
