#pragma GCC optimize("Ofast,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
using namespace rel_ops;

using ll  = long long;
using Vi  = vector<int>;
using Pii = pair<int, int>;

#define mp make_pair
#define mt make_tuple
#define pb push_back

#define rep(i, b, e)  for (int i = (b); i <  (e); i++)
#define repd(i, b, e) for (int i = (b); i >= (e); i--)
#define each(a, x)    for (auto& a : (x))
#define all(x)        (x).begin(), (x).end()
#define sz(x)         int((x).size())

// > Debugging

#define tem template<class t, class...v>
#define pri(c) tem auto p(t x, int)->decltype(c,z()) { DD()

struct DD {
	using z = void;

	tem DD& operator,(t x) { p(x, 0); return *this; }

	tem z p(t x, ...) { cerr << x; }
	pri(&t::print); x.print(); }

	pri(t().first), "(", x.first, ", ", x.second, ")"; }

	pri(t().begin()), "[";
		each(e, x) DD(), e, ", ";
		DD(), "]";
	}

	z d(...) {}

	tem z d(const char* s, t a, v... b) {
		while (*s && *s != ',') DD(), *s++;
		DD(), ": ", a, *s++; d(s, b...);
	}
};

#ifdef LOC
#define deb(...) ((DD(), "<", __LINE__, "> ").d(#__VA_ARGS__, __VA_ARGS__), DD(), "\n")
#else
#define deb(...)
#endif

#define DBP(...) void print() { (DD(), '{').d(#__VA_ARGS__, __VA_ARGS__); DD(), '}'; }

// ------------------------------------------------------------------------------------------ //

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
	return 0;
}
