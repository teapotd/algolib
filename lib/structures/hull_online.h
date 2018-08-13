#include "../template.h"

constexpr ll INF = 2e18;

struct Hull {
	static bool modeQ;

	struct Line {
		mutable ll a, b, begin;

		ll intersect(const Line& r) const {
			if (a==r.a) return b > r.b ? INF : -INF;
			ll u = b-r.b, d = r.a-a;
			return u/d + ((u^d) >= 0 || !(u%d));
		}
		
		bool operator<(const Line& r) const {
			return modeQ ? begin < r.begin : a < r.a;
		}
	};

	multiset<Line> S;
	Hull() { S.insert({ 0, -INF, -INF }); }

	bool update(multiset<Line>::iterator it) {
		if (it == S.end()) return false;
		it->begin = -INF;
		if (it == S.begin()) return false;
		auto cur = it--;
		cur->begin = it->intersect(*cur);
		return it->begin >= cur->begin;
	}

	void insert(ll a, ll b) {
		auto it = S.insert({ a, b, -INF });
		while (update(it)) it = S.erase(--it);
		rep(i, 0, 2)
			while (it != S.end() && update(++it))
				update(it = S.erase(--it));
	}

	ll query(ll x) {
		modeQ = 1;
		auto l = *--S.upper_bound({ 0, 0, x });
		modeQ = 0;
		return l.a*x + l.b;
	}
};

bool Hull::modeQ = false;
