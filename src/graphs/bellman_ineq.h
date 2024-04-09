#pragma once
#include "../template.h"
//!!EXCLUDE-FILE

struct Ineq {
	ll a, b, c; // a - b >= c
};

// Solve system of inequalities of form a-b>=c
// using Bellman-Ford; time: O(n*m)
bool solveIneq(vector<Ineq>& edges,
	             vector<ll>& vars) {
	rep(i, 0, sz(vars)) each(e, edges)
		vars[e.b] = min(vars[e.b], vars[e.a]-e.c);
	each(e, edges)
		if (vars[e.a]-e.c < vars[e.b]) return 0;
	return 1;
}
