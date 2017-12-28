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

#define tem template<class t, class...g>
#define D DD()

#define pri(k) tem auto p(t a, ll)->decltype(a.k, z()) { D

struct DD {
	using z = void;
	z x(...) {}

	tem DD& operator,(t a) { p(a, 0); return *this; }
	tem z p(t a, ...) { cerr << a; }

	pri(print()); a.print(); }

	pri(first), "(", a.first, ", ", a.second, ")"; }

	pri(begin()), "[";
		each(k, a) D, k, ", ";
		D, "]";
	}

	tem z x(const char* s, t a, g... k) {
		while (*s && *s != ',') D, *s++;
		D, ": ", a, *s++; x(s, k...);
	}
};

#ifdef LOC
#define deb(...) ((D, "<", __LINE__, "> ").x(#__VA_ARGS__, __VA_ARGS__), D, "\n")
#else
#define deb(...)
#endif

#define DBP(...) void print() { D.x("{" #__VA_ARGS__, __VA_ARGS__); D, "}"; }

// ------------------------------------------------------------------------------------------ //

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
	return 0;
}
