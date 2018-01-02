#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using Vi  = vector<int>;
using Pii = pair<int, int>;

#define pb push_back
#define mp make_pair
#define x  first
#define y  second

#define rep(i, b, e) for(int i=(b); i<(e); i++)
#define each(a, x)   for (auto& a : (x))
#define all(x)       (x).begin(), (x).end()
#define sz(x)        int((x).size())


template<class t, class u>
auto operator<<(t& o, u& a)->decltype(a.print(),cerr) {
	a.print(); return o;
}

template<class t, class u>
auto operator<<(t& o, u& a)->decltype(get<1>(a),cerr) {
	return o << "(" << a.x << ", " << a.y << ")";
}

template<class t, class u>
auto operator<<(t& o, u& a)->decltype(all(a),cerr) {
	o << "[";
	for (auto i : a) o << i << ", ";
	return o << "]";
}

void D(...) {}

template<class t, class u, class...v>
void D(t s, u a, v... k) {
	while (*s && *s != ',') cerr << *s++;
	cerr << ": " << a << *s++; D(s, k...);
}


#ifdef LOC
#define deb(...) (cerr << "<" << __LINE__, D("> " #__VA_ARGS__, __VA_ARGS__), cerr << "\n")
#else
#define deb(...)
#endif

#define DBP(...) void print() { D("{" #__VA_ARGS__, __VA_ARGS__); cerr << "}"; }


int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
	return 0;
}

// while (clock() < time*CLOCKS_PER_SEC)
// using namespace rel_ops;

// GCC optimize("Ofast,no-stack-protector")
