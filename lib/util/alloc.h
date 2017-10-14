#pragma once

#include "template.h"

char memPool[512*1024*1024];
int memOffset;

void* operator new(size_t n) { memOffset += n; return &memPool[memOffset-n]; }
void  operator delete(void*) {}
