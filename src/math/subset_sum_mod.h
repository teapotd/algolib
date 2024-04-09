#pragma once
#include "../template.h"
//!!EXCLUDE-FILE
//! Source: https://doi.org/10.4230/LIPIcs.ESA.2021.76

// Shift-tree with splitmix64 hashing.
struct ShiftTree {
	vector<uint64_t> H;
	int len, delta;

	// Init tree of size n = 2^d.
	ShiftTree(int n) : H(n*2), len(n), delta(0) {
		assert(n && !(n & (n-1)));
	}

	// Set a[i] := 1; time: O(log n)
	void set(int i) {
		H[i = (i+len-delta) % len + len] = 1;
		for (int d = delta; i > 1; d /= 2)
			update(i = parent(i, d%2), d%2);
	}

	// Cyclically shift by k to the right;
	// time: O(n / 2^j), where j max s.t. 2^j | k
	void shift(int k) {
		if (k %= len) {
			delta = (delta+len+k) % len;
			int div = k & ~(k-1), d = delta / div;
			for (int t = len/div/2; t >= 1; t /= 2) {
				rep(i, t, t*2) update(i, d%2);
				d /= 2;
			}
		}
	}

	// Find mismatches between T[a:b) and Q[a:b);
	// time: O((|D|+1) log n)
	void diff(vi& out, const ShiftTree& T,
	          int vb, int ve, int lvl = -1,
	          int b = 0, int e = -1,
	          int i = 1, int j = 1) {
		if (e < 0) lvl = __lg(e=len)-1;
		if (b >= ve || vb >= e || H[i] == T.H[j])
			return;
		if (e-b == 1) return out.push_back(b);

		int m = (b+e) / 2;
		int s1 = (delta >> lvl) & 1;
		int s2 = (T.delta >> lvl) & 1;

		diff(out, T, vb, ve, lvl-1, b, m,
			left(i, s1), left(j, s2));
		diff(out, T, vb, ve, lvl-1, m, e,
			right(i, s1), right(j, s2));
	}

	void update(int i, int s) {
		auto x = H[left(i, s)] +
			H[right(i, s)] * 0x9E37'79B9'7F4A'7C15;
		x = (x ^ (x>>30)) * 0xBF58'476D'1CE4'E5B9;
		x = (x ^ (x>>27)) * 0x94D0'49BB'1331'11EB;
		H[i] = x ^ (x >> 31);
	}

	int parent(int i, int s) {
		int k = i + s;
		return k&i ? k/2 : k/4;
	}

	int left(int i, int s) {
		int k = i*2, j = k - s;
		return k&j ? j : k|j;
	}

	int right(int i, int s) {
		return i*2 + !s;
	}
};

int bitrev(int n, int bits) {
	int ret = 0;
	rep(i, 0, bits)
		ret |= ((n >> i) & 1) << (bits-i-1);
	return ret;
}

// Find all attainable subset sums modulo m;
// time: O(m log m)
// Input elements are given by frequency array,
// i.e. counts[x] = how many times element x
// is contained in the input multiset.
// Size of `counts` is the modulus m.
// The returned array encodes solutions,
// which can be recovered using `recover`.
// ans[x] != -1 <=> subset with sum x exists
vi subsetSumMod(const vi& counts) {
	int mod = sz(counts), len = 1, k = 0;
	while (len < mod*2) len *= 2, k++;

	vi tmp, ans(mod, -1);
	ShiftTree T(len), Q(len);

	ans[0] = 0;
	T.set(0);
	Q.set(0);
	Q.set(-mod);

	rep(i, 1, len) {
		int x = bitrev(i, k);
		if (x >= mod || !counts[x]) continue;

		Q.shift(x - Q.delta);

		rep(j, 0, counts[x]) {
			tmp.clear();
			T.diff(tmp, Q, 0, mod);
			if (tmp.empty()) break;

			each(d, tmp) if (ans[d] == -1) {
				ans[d] = x;
				T.set(d);
				Q.set(d+x);
				Q.set(d+x-mod);
			}
		}
	}

	return ans;
}

vi recoverSubset(const vi& dp, int s) {
	assert(dp[s] != -1);
	vi ret;
	while (s) {
		ret.pb(dp[s]);
		s = (s - dp[s] + sz(dp)) % sz(dp);
	}
	return ret;
}
