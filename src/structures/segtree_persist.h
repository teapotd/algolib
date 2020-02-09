#pragma once
#include "../template.h"

// UNTESTED
struct SegTree {
	#include "seg_tree_config.h"

	vector<Agg> agg;
	vector<T> lazy;
	Vi L, R;
	int len{1};

	SegTree(int n = 0, T def = 0) {
		int k = 1;
		while (len < n) len *= 2, k++;

		agg.resize(k);
		lazy.resize(k);
		L.resize(k);
		R.resize(k);
		agg[--k].leaf(def);

		while (k--) {
			(agg[k] = agg[k+1]).merge(agg[k+1]);
			L[k] = R[k] = k+1;
		}
	}

	int fork(int i) {
		L.pb(L[i]); R.pb(R[i]);
		agg.pb(agg[i]); lazy.pb(lazy[i]);
		return sz(L)-1;
	}

	void push(int i, int s, bool w) {
		bool has = (lazy[i] != ID);
		if (has || w) {
			int a = fork(L[i]), b = fork(R[i]);
			L[i] = a; R[i] = b;
		}
		if (has) {
			agg[L[i]].apply(lazy[L[i]],lazy[i],s/2);
			agg[R[i]].apply(lazy[R[i]],lazy[i],s/2);
			lazy[i] = ID;
		}
	}

	T update(int i, int vb, int ve, T val,
	         int b = 0, int e = -1) {
		if (e < 0) e = len;
		if (vb >= e || b >= ve) return val;

		if (b >= vb && e <= ve &&
		    agg[i].apply(lazy[i], val, e-b))
			return val;

		int m = (b+e) / 2;
		push(i, e-b, 1);
		val = update(L[i], vb, ve, val, b, m);
		val = update(R[i], vb, ve, val, m, e);
		(agg[i] = agg[L[i]]).merge(agg[R[i]]);
		return val;
	}

	Agg query(int i, int vb, int ve,
	          int b = 0, int e = -1) {
		if (e < 0) e = len;
		if (vb >= e || b >= ve) return {};
		if (b >= vb && e <= ve) return agg[i];

		int m = (b+e) / 2;
		push(i, e-b, 0);
		Agg t = query(L[i], vb, ve, b, m);
		t.merge(query(R[i], vb, ve, m, e));
		return t;
	}
};
