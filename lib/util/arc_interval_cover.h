#pragma once
#include "../template.h"

// Find size of smallest set of points
// such that each arc contains at least one
// of them; time: O(n lg n)
int arcCover(vector<pair<dbl, dbl>>& inters,
             dbl wrap) {
	int n = sz(inters);

	rep(i, 0, n) {
		auto& e = inters[i];
		e.x = fmod(e.x, wrap);
		e.y = fmod(e.y, wrap);
		if (e.x < 0) e.x += wrap, e.y += wrap;
		if (e.x > e.y) e.x += wrap;
		inters.pb({e.x+wrap, e.y+wrap});
	}

	vector<Vi> jmp(n*2+1, {n*2});
	deque<dbl> que;
	dbl r = wrap*4;
	sort(all(inters));

	for (int i = n*2-1; i--;) {
		r = min(r, inters[i].y);
		que.push_front(inters[i].x);
		while (!que.empty() && que.back() > r)
			que.pop_back();
		jmp[i][0] = i+sz(que);
	}

	int lg = 32-__builtin_clz(n), ans = n;
	rep(i, 0, lg) each(v,jmp) v.pb(jmp[v[i]][i]);

	rep(i, 0, n) {
		int v = i, k = 0;
		for (int j = lg; j--;) {
			if (jmp[v][j] < i+n) {
				k += 1<<j;
				v = jmp[v][j];
			}
		}
		ans = min(ans, k+1);
	}

	return ans;
}
