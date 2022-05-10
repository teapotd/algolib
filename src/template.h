#pragma once
//!!EXCLUDE-FILE

#ifdef __clang__
#define private public
#define _M_p __seg_
#endif

#define main __main_defined_by_template
#include "template.cpp"
#undef main
