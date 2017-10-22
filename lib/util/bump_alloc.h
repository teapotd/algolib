#pragma once
#include "../template.h"

// Special fast allocator without freeing memory - use with care

char mem[512*1024*1024];
int nMem;

void* operator new(size_t n) { nMem += n; return &mem[nMem-n]; }
void  operator delete(void*) {}
