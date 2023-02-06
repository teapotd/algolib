#include "../template.h"

constexpr ll INF = 2e18;

// MAX of linear functions online; space: O(n)
struct Hull {
	static bool modeQ; // Toggles operator< mode

	struct Line {
		mutable ll a, b, end;

		ll intersect(const Line& r) const {
			if (a==r.a) return b > r.b ? INF : -INF;
			ll u = b-r.b, d = r.a-a;
			return u/d + ((u^d) >= 0 || !(u%d));
		}

		bool operator<(const Line& r) const {
			return modeQ ? end < r.end : a < r.a;
		}
	};

	multiset<Line> S;
	Hull() { S.insert({ 0, -INF, INF }); }

	// Updates segment end
	bool update(multiset<Line>::iterator it) {
		auto cur = it++; cur->end = INF;
		if (it == S.end()) return false;
		cur->end = cur->intersect(*it);
		return cur->end >= it->end;
	}

	// Insert f(x) = ax+b; time: O(lg n)
	void insert(ll a, ll b) {
		auto it = S.insert({ a, b, INF });
		while (update(it)) it = --S.erase(++it);
		rep(i, 0, 2)
			while (it != S.begin() && update(--it))
				update(it = --S.erase(++it));
	}

	// Query max(f(x) for each f): time: O(lg n)
	ll query(ll x) {
		modeQ = 1;
		auto l = *S.upper_bound({ 0, 0, x });
		modeQ = 0;
		return l.a*x + l.b;
	}
};

bool Hull::modeQ = false;
