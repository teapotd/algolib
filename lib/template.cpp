#include <bits/stdc++.h>
using namespace std;

using ll  = int64_t;
using Vi  = vector<int>;
using Pii = pair<int,int>;

#define pb push_back
#define mp make_pair
#define x  first
#define y  second

#define rep(i,b,e) for(int i=(b); i<(e); i++)
#define each(a,x)  for(auto& a : (x))
#define all(x)     (x).begin(),(x).end()
#define sz(x)      int((x).size())


#define tem template<class t,class u,class...w>
#define pri(x,y)tem auto operator<<(t& o,u a) \
	->decltype(x,o) { o << y; return o; }

pri(a.print(), "{"; a.print(); o << "}")
pri(a.y, "(" << a.x << ", " << a.y << ")")

pri(all(a), "["; for (auto i : a)
	o << i << ", "; o << "]")

void DD(...) {}
tem void DD(t s, u a, w... k) {
	while (*s && *s != 44) cerr << *s++;
	cerr << ": " << a << *s++; DD(s, k...);
}

#ifdef LOC
#define deb(...) (DD("#, "#__VA_ARGS__, \
	__LINE__, __VA_ARGS__), cerr << endl)
#else
#define deb(...)
#endif

#define DBP(...) void print() { \
	DD(#__VA_ARGS__, __VA_ARGS__); }


int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
	return 0;
}

// while (clock() < time*CLOCKS_PER_SEC)
// using namespace rel_ops;

// #pragma GCC optimize("Ofast,unroll-loops,
//                       no-stack-protector")
// #pragma GCC target("avx")
