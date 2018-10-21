#pragma once
#include "../template.h"

//!!IGNORE
// Allocator, which doesn't free memory.

char mem[512<<20]; // Set memory limit
size_t nMem;

void* operator new(size_t n) {
	nMem += n; return &mem[nMem-n];
}
void operator delete(void*) {}
