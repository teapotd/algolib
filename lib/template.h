#include <bits/stdc++.h>
using namespace std;

using ll    = int64_t;
using ull   = uint64_t;
using ld    = long double;
using cmpl  = complex<double>;

#define IT iterator

#define rep(i, b, e)  for (int i = b; i < (e); i++)
#define repd(i, b, e) for (int i = int(b); i >= (e); i--)
#define each(a, x)    for (auto& a : x)
#define all(x)        (x).begin(), (x).end()
#define sz(x)         int((x).size())


// #!/bin/bash
// set -e


// Normal build:
// g++ -O2 -Wall -Wextra -std=c++11 -o $1.e $1.cpp


// Debug build:
// g++-6 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -std=c++11 -o $1.e $1.cpp
// -fvisibility=hidden (chyba tylko mac)


// Stack limit:
// -Wl,-stack_size -Wl,16000000 -Wl,-no_pie


// Compare:
// ./build.sh $1; ./build.sh $2; ./build.sh $3
//
// while :; do
// 	 $3.e > cmp.in; echo -n 0
// 	 $1.e < cmp.in > prog1.out; echo -n 1
// 	 $2.e < cmp.in > prog2.out; echo -n 2
// 	 diff prog1.out prog2.out
// 	 echo -n Y
// done
