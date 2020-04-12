#pragma once
#include "../template.h"

using ull = uint64_t;

// Matrix over Z_2 (bits and xor)
// TODO: arithmetic operations
struct BitMatrix {
	vector<ull> M;
	int rows, cols, stride;

	// Create matrix with n rows and m columns
	BitMatrix(int n = 0, int m = 0) {
		rows = n; cols = m;
		stride = (m+63)/64;
		M.resize(n*stride);
	}

	// Get pointer to bit-packed data of i-th row
	ull* row(int i) { return &M[i*stride]; }

	// Get value in i-th row and j-th column
	bool operator()(int i, int j) {
		return (row(i)[j/64] >> (j%64)) & 1;
	}

	// Set value in i-th row and j-th column
	void set(int i, int j, bool val) {
		ull &w = row(i)[j/64], m = 1ull << (j%64);
		if (val) w |= m;
		else w &= ~m;
	}
};
