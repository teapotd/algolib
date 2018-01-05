#pragma once
#include "../template.h"

constexpr int ALPHA = 26;

struct PalTree {
	Vi str{-1}, len{0, -1}, link{1, 0};
	vector<array<int, ALPHA>> to{ {}, {} };
	int last{0};

	Vi diff, slink, series, ans; //ext: min split

	int ext(int i) {
		while(str.rbegin()[len[i]+1] != str.back())
			i = link[i];
		return i;
	}

	void add(int x) {
		str.pb(x);
		last = ext(last);

		if (!to[last][x]) {
			len.pb(len[last]+2);
			link.pb(to[ext(link[last])][x]);
			to[last][x] = sz(to);
			to.emplace_back();

			// Extension: min split
			diff.pb(len.back() - len[link.back()]);
			slink.pb(diff.back() == diff[link.back()]
				? slink[link.back()] : link.back());
		}
		last = to[last][x];

		// Extension: min split
		ans.pb(INT_MAX);
		series.pb(0);

		for (int i=last; len[i]>0; i=slink[i]) {
			series[i] = ans[i-len[slink[i]]+diff[i]];
			if (diff[i] == diff[link[i]])
				series[i] =
					min(series[i], series[link[i]]);
			ans.back() = min(ans.back(),series[i]+1);
		}
	}
};
