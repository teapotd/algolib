#pragma once
#include "../template.h"

using dbl = double;

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

	vi nxt(n);
	deque<dbl> que;
	dbl r = wrap*4;
	sort(all(inters));

	for (int i = n*2-1; i--;) {
		r = min(r, inters[i].y);
		que.push_front(inters[i].x);
		while (!que.empty() && que.back() > r)
			que.pop_back();
		if (i < n) nxt[i] = i+sz(que);
	}

	int a = 0, b = 0;
	do {
		a = nxt[a] % n;
		b = nxt[nxt[b]%n] % n;
	} while (a != b);

	int ans = 0;
	while (b < a+n) {
		b += nxt[b%n] - b%n;
		ans++;
	}
	return ans;
}
