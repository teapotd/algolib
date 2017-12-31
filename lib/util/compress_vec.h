#pragma once
#include "../template.h"

int compressVec(vector<int*>& vec) {
	sort(all(vec), [](int* l, int* r) {
		return *l < *r;
	});
	int last = *vec[0], i = 0;
	each(e, vec) {
		if (*e != last) i++;
		last = *e; *e = i;
	}
	return i+1;
}
