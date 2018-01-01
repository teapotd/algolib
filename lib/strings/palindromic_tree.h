#pragma once
#include "../template.h"

constexpr int ALPHA = 26;

struct PalTree {
	Vi str{-1}, len{0, -1}, suf{1, 0};
	vector<array<int, ALPHA>> to{ {}, {} };
	int last{0};

	int ext(int i) {
		while(str.rbegin()[len[i]+1] != str.back())
			i = suf[i];
		return i;
	}

	void add(int x) {
		str.pb(x);
		last = ext(last);

		if (!to[last][x]) {
			len.pb(len[last]+2);
			suf.pb(to[ext(suf[last])][x]);
			to[last][x] = sz(to);
			to.emplace_back();
		}
		last = to[last][x];
	}
};
