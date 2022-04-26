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

#define tem \
	template<class t,class u,class...w> auto
#define pri(x,y,z) \
	tem operator<<(t&o,u a)->decltype(z,o) \
	{ o << *#x; y; z; return o << #x+1; }

pri({},, a.print())
pri((),, o << a.x << ", " << a.y)

pri([], auto d=""; for (auto i : a)
	(o << d << i, d = ", "), all(a))

void DD(...) {}
tem DD(t s, u a, w... k) {
	for (int b=1; cerr << *s++, *s && *s - b*44;)
		b += 2 / (*s*2 - 81);
	cerr << ": " << a; DD(s, k...);
}

#ifdef LOC
#define deb(x...) \
	DD("[,\b :] "#x, __LINE__, x), cerr << endl
#else
#define deb(...)
#endif

#define DBP(x...) void print() { DD(#x, x); }

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
