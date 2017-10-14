#pragma once

#include <bits/stdc++.h>
using namespace std;

using ll    = int64_t;
using ull   = uint64_t;
using ld    = long double;
using cmpl  = complex<double>;

#define IT iterator

#define rep(i, b, e)  for (int i = int(b); i < int(e); i++)
#define repd(i, b, e) for (int i = int(b); i >= int(e); i--)
#define each(a, x)    for (auto& a : x)
#define all(x)        (x).begin(), (x).end()
#define sz(x)         int((x).size())

#define gcd           __gcd
#define popcount      __builtin_popcount


// unique_ptr without deallocation
template<typename T>
struct single_ptr {
	T* elem{0};

	single_ptr()                              {}
	single_ptr(nullptr_t)                     {}
	single_ptr(T* v)           : elem(v)      {}
	single_ptr(single_ptr&& r) : elem(r.elem) { r.elem = 0; }

	single_ptr& operator=(nullptr_t)      { elem = 0; return *this; }
	single_ptr& operator=(single_ptr&& r) { elem = r.elem; r.elem = 0; return *this; }

	T* operator->() { return elem; }
	T& operator*()  { return *elem; }
	operator bool() { return elem; }
};
