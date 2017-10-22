#pragma once

#include <bits/stdc++.h>
using namespace std;
using namespace rel_ops;

using ll   = int64_t;
using ull  = uint64_t;
using ld   = long double;
using cmpl = complex<double>;
using Vi   = vector<int>;
using Pii  = pair<int, int>;

#define IT iterator
#define mp make_pair

#define rep(i, b, e)  for (int i = (b); i < (e); i++)
#define repd(i, b, e) for (int i = (b); i >= (e); i--)
#define each(a, x)    for (auto& a : x)
#define all(x)        (x).begin(), (x).end()
#define sz(x)         int((x).size())

#define gcd      __gcd
#define popcount __builtin_popcount

int main() {
	cin.sync_with_stdio(false); cin.tie(0);
}
