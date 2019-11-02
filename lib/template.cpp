#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using Vi  = vector<int>;
using Pii = pair<int,int>;

#define pb push_back
#define x  first
#define y  second

#define rep(i,b,e) for(int i=(b); i<(e); i++)
#define each(a,x)  for(auto& a : (x))
#define all(x)     (x).begin(),(x).end()
#define sz(x)      int((x).size())

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(18);
	return 0;
}

// > Debug printer

#define tem template<class t,class u,class...w>
#define pri(x,y)tem auto operator<<(t& o,u a) \
	->decltype(x,o) { o << y; return o; }

pri(a.print(), "{"; a.print(); o << "}")
pri(a.y, "(" << a.x << ", " << a.y << ")")

pri(all(a), "["; auto d=""; for (auto i : a)
	(o << d << i, d = ", "); o << "]")

void DD(...) {}
tem void DD(t s, u a, w... k) {
	int b = 44;
	while (*s && *s != b) {
		b += (*s == 40 ? 50 : *s == 41 ? -50 : 0);
		cerr << *s++;
	}
	cerr << ": " << a << *s++; DD(s, k...);
}

tem vector<t> span(const t* a, u n) {
	return {a, a+n};
}

#ifdef LOC
#define deb(...) (DD("#, "#__VA_ARGS__, \
	__LINE__, __VA_ARGS__), cerr << endl)
#else
#define deb(...)
#endif

#define DBP(...) void print() { \
	DD(#__VA_ARGS__, __VA_ARGS__); }

// > Utils

// #define _USE_MATH_DEFINES

// #pragma GCC optimize("Ofast,unroll-loops,
//                       no-stack-protector")
// #pragma GCC target("avx")

// while (clock() < time*CLOCKS_PER_SEC)
// using namespace rel_ops;

// Return smallest k such that 2^k > n
// Undefined for n = 0!
int uplg(int n) { return 32-__builtin_clz(n); }
int uplg(ll n){ return 64-__builtin_clzll(n); }

// Compare with certain epsilon (branchless)
// Returns -1 if a < b; 1 if a > b; 0 if equal
// a and b are assumed equal if |a-b| <= eps
int cmp(double a, double b, double eps=1e-10) {
	return (a > b+eps) - (a+eps < b);
}
