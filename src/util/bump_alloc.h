#pragma once
#include "../template.h"
//!!EXCLUDE-FILE

// Allocator, which doesn't free memory.
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/various/BumpAllocator.h

char mem[400<<20]; // Set memory limit
size_t nMem;

void* operator new(size_t n) {
	nMem += n; return &mem[nMem-n];
}
void operator delete(void*) {}
