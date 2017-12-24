#pragma GCC optimize("Ofast,no-stack-protector")

#include <bits/stdc++.h>
using namespace std;
using namespace rel_ops;

using ll  = int64_t;
using ull = uint64_t;
using ld  = long double;

#define ref auto&
#define IT  iterator
#define mp  make_pair

#define rep(i, b, e)  for (int i = (b); i <  (e); i++)
#define repd(i, b, e) for (int i = (b); i >= (e); i--)
#define each(a, x)    for (ref a : (x))
#define all(x)        (x).begin(), (x).end()
#define sz(x)         int((x).size())

// ---

void dbgx(ostream&, ...) {}

template<class T, class ...V> void dbgx(ostream& o, const char* s, T a, V... b) {
	while (*s && *s != ',') o << *s++;
	o << ": " << a << *s++; dbgx(o, s, b...);
}

#ifdef LOC
#define dbg(...) (dbgx(cerr << "<" << __LINE__, "> " #__VA_ARGS__, __VA_ARGS__), cerr << "\n")
#else
#define dbg(...)
#endif

// ---

template<class T, class U> ostream& operator<<(ostream& o, pair<T, U> x) {
	return o << "(" << x.first << ", " << x.second << ")";
}

template<class T> auto operator<<(ostream& o, T x) -> decltype(T().begin(),cout) {
	int f = 1; o << "[";
	each(e, x) o << (f ? f=0, "" : ", ") << e;
	return o << "]";
}

template<class T> auto operator<<(ostream& o, T x) -> decltype(&T::print,cout) {
	return x.print(o);
}

#define DPR(...) ostream& print(ostream& o) \
	{ dbgx(o << '{', #__VA_ARGS__, __VA_ARGS__); return o << '}'; }

// ---

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
	return 0;
}
