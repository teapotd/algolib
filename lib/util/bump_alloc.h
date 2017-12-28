#pragma once
#include "../template.h"

// Special fast allocator - not releasing memory - use with care

char mem[512<<20];
size_t nMem;

void* operator new(size_t n) { nMem += n; return &mem[nMem-n]; }
void  operator delete(void*) {}
