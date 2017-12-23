#include <bits/stdc++.h>
using namespace std;
using namespace rel_ops;

using ll  = long long;
using ull = uint64_t;
using ld  = long double;

#define IT iterator
#define mp make_pair

#define rep(i, b, e)  for (int i = (b); i < (e); i++)
#define repd(i, b, e) for (int i = (b); i >= (e); i--)
#define each(a, x)    for (auto& a : (x))
#define all(x)        (x).begin(), (x).end()
#define sz(x)         int((x).size())

// ---

ostream& _dbg(ostream& o, const char*) { return o; }

template<class T, class ...U> ostream& _dbg(ostream& o, const char* s, T a, U... b) {
	while (*s && *s != ',') o << *s++;
	o << ": " << a << *s; return _dbg(o, s+1, b...);
}

#ifdef LOC
#define dbg(...) (_dbg(cerr << "<" << __LINE__, "> " #__VA_ARGS__, __VA_ARGS__) << "\n")
#else
#define dbg(...)
#define cerr if(0)cerr
#endif

// ---

template<class T, class U> ostream& operator<<(ostream& o, pair<T, U> x) {
	return o << "(" << x.first << ", " << x.second << ")";
}

template<class T> ostream& operator<<(ostream& o, vector<T> x) {
	int f = 1; o << "[";
	each(e, x) o << (f ? f=0, "" : ", ") << e;
	return o << "]";
}

template<class T> auto operator<<(ostream& o, T x) -> decltype(&T::print,*(ostream*)0) {
	return x.print(o);
}

#define DD(...) ostream& print(ostream& o) \
	{ return _dbg(o << '{', #__VA_ARGS__, __VA_ARGS__) << '}'; }

#define IND(t, v) ostream& operator<<(ostream& o, t x) { return o << int(x - v.data()); }

// ---

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	return 0;
}
