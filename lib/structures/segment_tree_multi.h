#pragma once
#include "../template.h"

//!!IGNORE unfinished

struct SegmentTreeMulti {
	using T = int;
	static constexpr T ID = INT_MIN;
	static T merge(T a, T b) { return max(a,b); }

	struct Node {
		int E[3] = {-1, -1, -1};
		T val{ID};
	};

	vector<Node> G;
	Vi dims;

	SegmentTreeMulti(Vi d = {}) { init(d); }

	void init(Vi d) {
		dims = d; G.assign(1, {});
	}

	int child(int i, int j) {
		if (G[i].E[j] < 0) {
			G[i].E[j] = sz(G);
			G.emplace_back();
		}
		return G[i].E[j];
	}

	int L(int i)   { return child(i, 0); }
	int R(int i)   { return child(i, 1); }
	int sub(int i) { return child(i, 2); }
	
	T subQuery(int i) { return G[i].val; }

	template<class ...D>
	T subQuery(int i, D... pos) {
		int k = sz(dims) - int(sizeof...(D)/2);
		return queryImpl(sub(i), 0, dims[k],
			               pos...);
	}

	template<class ...D>
	T queryImpl(int i, int begin, int end,
	            int vBegin, int vEnd, D... pos) {
		if (vEnd <= begin || end <= vBegin)
			return ID;
		if (vBegin <= begin && end <= vEnd) {
			return subQuery(i, pos...);
		}

		int mid = (begin + end) / 2;
		return merge(
			queryImpl(L(i),begin,mid,
			          vBegin,vEnd,pos...),
			queryImpl(R(i),mid,end,
			          vBegin,vEnd,pos...));
	}

	template<class ...D>
	T query(D... pos) {
		assert(sizeof...(D) == sz(dims)*2);
		return queryImpl(0, 0, dims[0], pos...);
	}

	// void setImpl(int i, int begin, int end,
	//              T val, int pos) {
	// 	if (begin+1 == end) {
	// 		G[i].val = val;
	// 	} else {
	// 		int mid = (begin+end) / 2;
	// 		if (pos < mid) {
	// 			setImpl(L(i), begin, mid, val, pos);
	// 		} else {
	// 			setImpl(R(i), mid, end, val, pos);
	// 		}
	// 	}
	// }

	// template<class ...D>
	// void setImpl(int i, int begin, int end,
	//              T val, D... pos) {
	// }

	// template<class ...D>
	// void set(D... pos, T val) {
	// 	assert(sizeof...(D) == sz(dims));
	// 	setImpl(0, 0, dims[0], val, pos...);
	// }
};
