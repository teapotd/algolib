#pragma once
//!!IGNORE

#ifdef __clang__
#define private public
#define _M_p __seg_
#endif

#define main __not_main
#include "template.cpp"
#undef main
