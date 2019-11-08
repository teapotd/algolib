#include "../template.h"

constexpr ll INF = 2e18;
// constexpr double INF = 1e30;
// constexpr double EPS = 1e-9;

// MAX of linear functions; space: O(n)
// Use if you add lines in increasing `a` order
// Default uncommented version is for int64
struct Hull {
	using T = ll; // Or change to double

	struct Line {
		T a, b, end;
		T intersect(const Line& r) const {
			// Version for double:
			//if (r.a-a < EPS) return b>r.b?INF:-INF;
			//return (b-r.b) / (r.a-a);
			if (a==r.a) return b > r.b ? INF : -INF;
			ll u = b-r.b, d = r.a-a;
			return u/d + ((u^d) >= 0 || !(u%d));
		}
	};

	vector<Line> S;
	Hull() { S.pb({ 0, -INF, INF }); }

	// Insert f(x) = ax+b; time: amortized O(1)
	void push(T a, T b) {
		Line l{a, b, INF};
		while (true) {
			T e = S.back().end=S.back().intersect(l);
			if (sz(S) < 2 || S[sz(S)-2].end < e)
				break;
			S.pop_back();
		}
		S.pb(l);
	}

	// Query max(f(x) for each f): time: O(lg n)
	T query(T x) {
		auto t = *upper_bound(all(S), x,
			[](int l, const Line& r) {
				return l < r.end;
			});
		return t.a*x + t.b;
	}
};
