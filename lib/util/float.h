#pragma once
#include "../template.h"

// Compare with certain epsilon, branchless
int cmp(double a, double b, double eps=1e-10) {
	return (a > b+eps) - (a+eps < b);
}
