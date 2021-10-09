#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using Vi  = vector<int>;
using Pii = pair<int,int>;

#define mp make_pair
#define pb push_back
#define x  first
#define y  second

#define rep(i,b,e) for(int i=(b); i<(e); i++)
#define each(a,x)  for(auto& a : (x))
#define all(x)     (x).begin(),(x).end()
#define sz(x)      int((x).size())

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(12);

	// Don't call destructors:
	cout << flush; _Exit(0);
}

// > Debug printer

#define tem template<class t,class u,class...w>
#define pri(x,y,z)tem auto operator<<(t&o,u a)\
	->decltype(x,o) { o<<*y; z; return o<<y[1]; }

pri(a.print(), "{}", a.print())
pri(a.y, "()", o << a.x << ", " << a.y)

pri(all(a), "[]", auto d="";
	for (auto i : a) (o << d << i, d = ", "))

void DD(...) {}
tem void DD(t s, u a, w... k) {
	for (int b=1; *s && *s - b*44; cerr << *s++)
		b += 2 / (*s*2 - 81);
	cerr << ": " << a << *s++; DD(s, k...);
}

#ifdef LOC
#define deb(...) (DD("[,\b :] "#__VA_ARGS__, \
	__LINE__, __VA_ARGS__), cerr << endl)
#else
#define deb(...)
#endif

#define DBP(...) void print() { \
	DD(#__VA_ARGS__, __VA_ARGS__); }

// > Utils

// Return smallest k such that 2^k > n
// Undefined for n = 0!
int uplg(int n) { return 32-__builtin_clz(n); }
int uplg(ll n){ return 64-__builtin_clzll(n); }

// Compare with certain epsilon (branchless)
// Returns -1 if a < b; 1 if a > b; 0 if equal
// a and b are assumed equal if |a-b| <= eps
int cmp(double a, double b, double eps=1e-9) {
	return (a > b+eps) - (a+eps < b);
}
