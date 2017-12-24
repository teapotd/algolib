#pragma GCC optimize("Ofast,no-stack-protector")

#include <bits/stdc++.h>
using namespace std;
using namespace rel_ops;

using ll  = int64_t;
using Vi  = vector<int>;
using Pii = pair<int, int>;

#define mp make_pair

#define rep(i, b, e)  for (int i = (b); i <  (e); i++)
#define repd(i, b, e) for (int i = (b); i >= (e); i--)
#define each(a, x)    for (auto& a : (x))
#define all(x)        (x).begin(), (x).end()
#define sz(x)         int((x).size())

// Debugging

#define TM template<class T, class U=int, class ...V>
void dbgx(...) {}

TM void dbgx(T s, U a, V... b) {
	while (*s && *s != ',') cerr << *s++;
	cerr << ": " << a << *s++; dbgx(s, b...);
}

#ifdef LOC
#define dbg(...) (cerr << "<" << __LINE__, dbgx("> " #__VA_ARGS__, __VA_ARGS__), cerr << "\n")
#else
#define dbg(...)
#endif

#define DF(t, ...) TM auto operator<<(ostream& o, __VA_ARGS__ x)->decltype(t,cout)

DF(&T::print, T)  { x.print(); return o; }
DF(0, pair<T, U>) { return o << "(" << x.first << ", " << x.second << ")"; }

DF(T().begin(), T) {
	o << "[";
	each(e, x) o << e << ", ";
	return o << "]";
}

#define DD(...) void print() { cerr << '{'; dbgx(#__VA_ARGS__, __VA_ARGS__); cerr << '}'; }

// ---

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
	return 0;
}
