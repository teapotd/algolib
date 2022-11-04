#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using vi  = vector<int>;
using pii = pair<int,int>;

#define pb push_back
#define x  first
#define y  second

#define rep(i,b,e) for(int i=(b); i<(e); i++)
#define each(a,x)  for(auto& a : (x))
#define all(x)     (x).begin(),(x).end()
#define sz(x)      int((x).size())

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed << setprecision(10);

	// Don't call destructors:
	cout << flush; _Exit(0);
}

// > Debug printer

#define PP(x,y) \
	auto operator<<(auto& o, auto a) \
	->decltype(y,o) \
	{ o << '('; x; return o << ')'; }

PP(a.print(), a.print());
PP(o << a.x << ", " << a.y, a.y);
PP(for (auto i : a) o << i << ", ", all(a));

void DD(auto s, auto... k) {
	([&] {
		while (cerr << *s++, 45 % ~*s);
		cerr << ": " << k;
	}(), ...);
}

#ifdef LOC
#define deb(x...) \
	DD(":, "#x, __LINE__, x), cerr << endl
#else
#define deb(...)
#endif

#define DBP(x...) void print() { DD(#x, x); }

// > Stack trace on STL assert

class SS { int x[0]; };
extern "C" SS __sanitizer_print_stack_trace();
#define __last_state \
	}; SS x { __sanitizer_print_stack_trace()

// > Utils

// Compare with certain epsilon (branchless)
// Returns -1 if a < b; 1 if a > b; 0 if equal
// a and b are assumed equal if |a-b| <= eps
int cmp(double a, double b, double eps=1e-9) {
	return (a > b+eps) - (a+eps < b);
}
