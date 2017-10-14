#pragma once

#include "../template.h"

struct Constraint {
	ll a, b, limit; // a - b >= limit
};

bool solveIneq(vector<Constraint>& edges, vector<ll>& vars) {
	rep(i, 0, sz(vars)) each(e, edges) vars[e.b] = min(vars[e.b], vars[e.a] - e.limit);
	each(e, edges) if (vars[e.a] - e.limit < vars[e.b]) return false;
	return true;
}
