#pragma once
#include "../template.h"

// Run `count` binary searches on [begin;end),
// `cmp` arguments:
// 1) vector<Pii>& - pairs (value, index)
//    which are queries if value of index is
//    greater or equal to value,
//    sorted by value
// 2) vector<bool>& - true at index i means
//    value of i-th query is >= queried value
// Returns vector of found values.
// Time: O((n+c) lg n), where c is cmp time.
template<class T>
Vi multiBS(int begin,int end,int count,T cmp) {
	vector<Pii> ranges(count, {begin, end});
	vector<Pii> queries(count);
	vector<bool> answers(count);

	rep(i,0,count) queries[i]={(begin+end)/2,i};

	for (int k = uplg(end-begin); k > 0; k--) {
		int last = 0, j = 0;
		cmp(queries, answers);

		rep(i, 0, sz(queries)) {
			Pii &q = queries[i], &r = ranges[q.y];
			if (q.x != last) last = q.x, j = i;

			(answers[i] ? r.x : r.y) = q.x;
			q.x = (r.x+r.y) / 2;

			if (!answers[i])
				swap(queries[i], queries[j++]);
		}
	}

	Vi ret;
	each(p, ranges) ret.pb(p.x);
	return ret;
}
