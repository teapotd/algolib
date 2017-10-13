#pragma once

#include "template.h"

static char memPool[512*1024*1024];
static int memOffset;

void* operator new(size_t n) { memOffset += n; return &memPool[memOffset-n]; }
void  operator delete(void*) {}

template<typename T> using a_ptr = T*; // unsafe af, because std::move doesn't work properly
#define unique_ptr a_ptr
