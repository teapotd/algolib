// If math constants like M_PI are not found
// add this at the beginning of file
#define _USE_MATH_DEFINES

// Pragmas
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("popcnt,avx,tune=native")

// Clock
while (clock() < duration*CLOCKS_PER_SEC)

// Automatically implement operators:
// 1. != if == is defined
// 2. >, <= and >= if < is defined
using namespace rel_ops;

// Mersenne twister for randomization.
mt19937_64 rnd(chrono::steady_clock::now()
	.time_since_epoch().count());

// To shuffle randomly use:
shuffle(all(vec), rnd);

// To pick random integer from [A;B] use:
uniform_int_distribution<> dist(A, B);
int value = dist(rnd);

// To pick random real number from [A;B] use:
uniform_real_distribution<> dist(A, B);
double value = dist(rnd);
